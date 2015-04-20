#include <stdio.h>
#include <stdlib.h>

//1)
//Estrutura de dados para representar uma árvore binária de procura
typedef struct registo{
	int num;
	struct registo *esq;
	struct registo *dir;
}*ABP;

//2)

//2.1)
//Inserir um novo inteiro na árvore, recursivamente
ABP insereNovo(ABP apt, int num){
	ABP novo;
	if (apt == NULL){
		//A árvore ainda está vazia, inicializar a árvore
		novo = (ABP)malloc(sizeof(struct registo));
		novo->num = num;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
	else{
		//Já existe árvore
		if (apt->num == num){
			//A raiz tem o numero que procuramos
			return apt;
		}
		else{
			if (apt->num > num){
				//O numero que procuramos é menor, vamos para a esquerda
				apt->esq = insereNovo(apt->esq, num);
				return apt;
			}
			else{
				apt->dir = insereNovo(apt->dir, num);
				return apt;
			}
		}
	}
}


//2.2)
//Devolve o somatorio de todos os inteiros na árvore
int somatorio(ABP apt){
	if (apt == NULL){
		return 0;
	}
	return apt->num + (somatorio(apt->esq) + somatorio(apt->dir));
}

//2.3)
//Remover todos os nodos da arvore
ABP remover(ABP apt){ //get root
	if (apt == NULL)
		return NULL;
	if (apt->esq != NULL)
		remover(apt->esq);
	if (apt->dir != NULL)
		remover(apt->dir);

	free(apt);
	return NULL;
}

//2.4)
//Lista inteiros presentes no ultimo nivel da arvore
int listarInteiros(ABP apt){
	//condicao de paragem
	if (apt == NULL){
		//Chegamos ao fim da arvore, sair
		return 0;
	}
	else if (apt->dir == NULL && apt->esq == NULL){
		//estamos numa folha, listar este valor
		printf(" %d ", apt->num);
	}
	else{
		//não estamos numa folha, continuar a descer a arvore
		if (apt -> esq != NULL) listarInteiros(apt->esq);
		if (apt -> dir != NULL) listarInteiros(apt->dir);
	}

	return 0;

}

//Auxiliar para escrever um array na consola
void printArray(int caminhos[], int contadorCaminhos)
{
	int i;
	for (i = 0; i<contadorCaminhos; i++) {
		printf("%d ", caminhos[i]);
	}
	printf("\n");
}

int contadorCaminhos = 0;
int caminhos[50];

//2.5)
//Lista todos os caminhos ate ao ultimo nivel da arvore
int listarCaminhos(ABP apt, int caminhos[], int contadorCaminhos){
	//condicao de paragem
	if (apt == NULL){
		//Chegamos ao fim da arvore, sair
		return 0;
	}
	else if (apt->dir == NULL && apt->esq == NULL){
		//estamos numa folha, escrever este caminho
		caminhos[contadorCaminhos] = apt->num;
		contadorCaminhos++;
		printArray(caminhos, contadorCaminhos);
		printf("\n");
	}
	else{
		//não estamos numa folha, continuar a descer a arvore
		caminhos[contadorCaminhos] = apt->num;
		contadorCaminhos++;
		if (apt->esq != NULL) listarCaminhos(apt->esq, caminhos, contadorCaminhos);
		if (apt->dir != NULL) listarCaminhos(apt->dir, caminhos, contadorCaminhos);
	}

	return 0;

}

//desenhar na consola a estrutura da árvore binária (código auxiliar, retirado da net)
int _print_t(ABP tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 5;

	if (!tree) return 0;

	sprintf(b, "(%03d)", tree->num);

	int left = _print_t(tree->esq, 1, offset, depth + 1, s);
	int right = _print_t(tree->dir, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
	for (int i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';
	}
#else
	for (int i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}
#endif

	return left + width + right;
}
void print_t(ABP tree)
{
	char s[20][255];
	for (int i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	_print_t(tree, 0, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}

ABP criarArvore(ABP apt){
	apt = NULL;
	apt = insereNovo(apt, 10);
	apt = insereNovo(apt, 5);
	apt = insereNovo(apt, 20);
	apt = insereNovo(apt, 3);
	apt = insereNovo(apt, 8);
	apt = insereNovo(apt, 25);
	printf("Arvore criada!\n");
	return apt;
}


int main(){

	//Criar árvore vazia
	ABP apt;
	apt = criarArvore(apt);

	print_t(apt);

	printf("\n\n");
	printf("Somatorio dos inteiros na arvore: %d\n", somatorio(apt));

	apt = remover(apt);
	printf("Arvore eliminada!\n");
	print_t(apt);

	apt = criarArvore(apt);
	print_t(apt);

	printf("Inteiros nas folhas da arvore:\n");
	listarInteiros(apt);
	printf("\n");

	printf("Caminhos:\n");
	listarCaminhos(apt, caminhos, contadorCaminhos);
	printf("\n");

	return 1;
}