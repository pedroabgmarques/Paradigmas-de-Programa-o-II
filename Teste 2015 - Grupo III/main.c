#include <stdio.h>

typedef struct registo{
	int num;
	struct registo *esq;
	struct registo *dir;
}*ABP;

//Solução recursiva
ABP InserirNode(ABP apt, int num){
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
				apt->esq = InserirNode(apt->esq, num);
				return apt;
			}
			else{
				apt->dir = InserirNode(apt->dir, num);
				return apt;
			}
		}
	}
}

void ListagemDecrescente(ABP apt){
	if (apt != NULL){
		ListagemDecrescente(apt->dir);
		printf("%d\n", apt->num);
		ListagemDecrescente(apt->esq);
	}
}

int Somatorio(ABP apt){
	if (apt == NULL){
		return 0;
	}
	return apt->num + (Somatorio(apt->esq) + Somatorio(apt->dir));
}

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

int main(){

	ABP apt = NULL;
	apt = InserirNode(apt, 1000);
	apt = InserirNode(apt, 1010);
	apt = InserirNode(apt, 900);
	apt = InserirNode(apt, 1020);
	apt = InserirNode(apt, 1030);

	print_t(apt);

	ListagemDecrescente(apt);

	printf("\nSoma de todos os inteiros contidos na arvore: %d\n", Somatorio(apt));

	return 1;
}