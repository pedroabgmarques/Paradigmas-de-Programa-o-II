#include <stdio.h>
#include <stdlib.h>

typedef struct registo{
	int num;
	int nota;
	struct registo *esq;
	struct registo *dir;
}* ABP;

//Lista ligada para representar um FIFO
typedef struct cel
{
	//N� da �rvore bin�ria
	ABP elemento;
	//Endere�o de mem�ria do pr�ximo elemento da lista FIFO
	struct cel *seguinte;
} * lista;

//Insere um elemento no FIFO
lista enqueue(lista l, ABP elemento)
{
	lista aux;
	aux = malloc(sizeof(struct cel));
	aux->elemento = elemento;
	aux->seguinte = l;
	return(aux);
}

//Retira um elemento do FIFO
lista dequeue(lista l, ABP * end)
{
	lista ant, act;
	if (l != NULL)
	{
		//O FIFO n�o est� vazio..
		if (l->seguinte == NULL)
		{
			//O FIFO s� tem um elemento
			
			//printf("\n\n\t\tELEMENTO REMOVIDO: %d", l->elemento);

			/* 
			Alteramos o endere�o de mem�ria passado por parametro para apontar para
			o n� da �rvore bin�ria (precisamos dele para adicionar os filhos ao FIFO)
			*/
			*end = l->elemento;
			//Devolvemos o FIFO vazio
			return(NULL);
			
		}
		else
		{
			//O FIFO tem v�rios elementos

			//Temos que guardar o elemento anterior para cortar a liga��o ao elemento que ser� eliminado
			ant = l;
			act = l->seguinte;

			while (act->seguinte != NULL)
			{
				//Percorremos o FIFO at� chegar ao �ltimo elemento
				ant = act;
				act = act->seguinte;
			}
			//printf("\n\n\t\tELEMENTO REMOVIDO: %d", act->elemento);

			//Cheg�mos ao �ltimo elemento do FIFO, alteramos o endere�o de mem�ria passado por parametro para apontar para
			//o n� da �rvore bin�ria que vamos remover (precisamos dele para adicionar os filhos ao FIFO)
			*end = act->elemento;
			//Eliminar este elemento do FIFO da mem�ria
			free(act);
			//Cortar a liga��o do elemento anterior ao elemento eliminado
			ant->seguinte = NULL;
		}
	}
	else
	{
		printf("\n\n\t\tERRO: Fila vazia.");
	}
	return(l);
}

//Solu��o recursiva
ABP insereNovo(ABP apt, int num, int nota){
	ABP novo;
	if (apt == NULL){
		//A �rvore ainda est� vazia, inicializar a �rvore
		novo = (ABP)malloc(sizeof(struct registo));
		novo->num = num;
		novo->nota = nota;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
	else{
		//J� existe �rvore
		if (apt->num == num){
			//A raiz tem o numero que procuramos
			apt->nota = nota;
			return apt;
		}
		else{
			if (apt->num > num){
				//O numero que procuramos � menor, vamos para a esquerda
				apt->esq = insereNovo(apt->esq, num, nota);
				return apt;
			}
			else{
				apt->dir = insereNovo(apt->dir, num, nota);
				return apt;
			}
		}
	}
}

//solu��o iterativa
ABP insere(ABP apt, int num, int nota){
	ABP aux = apt, novo;
	if (apt == NULL){
		novo = (ABP)malloc(sizeof(struct registo));
		novo->num = num;
		novo->nota = nota;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
	else while (1){
		if (aux->num == num){
			aux->nota = nota;
			return apt;
		}
		else if (aux->num > num){
			if (aux->esq == NULL){
				novo = (ABP)malloc(sizeof(struct registo));
				novo->num = num;
				novo->nota = nota;
				novo->esq = NULL;
				novo->dir = NULL;
				aux->esq = novo;
				return apt;
			}
			else{
				aux = aux->esq;
			}
		}
		else if (aux->num < num){
			if (aux->dir == NULL){
				novo = (ABP)malloc(sizeof(struct registo));
				novo->num = num;
				novo->nota = nota;
				novo->esq = NULL;
				novo->dir = NULL;
				aux->dir = novo;
				return apt;
			}
			else{
				aux = aux->dir;
			}
		}
	}
}

//Consultar recursivo
int consultarNota(ABP apt, int num){
	if (apt == NULL){
		//lista vazia
		return -1;
	}
	else if (apt->num == num){
		//Encontr�mos o numero de aluno, devolver a nota
		return apt->nota;
	}
	else if (apt->num > num){
		return (consultarNota(apt->esq, num));
	}
	else {
		return (consultarNota(apt->dir, num));
	}
}

//Quantidade de alunos na �rvore
int quantidade(ABP apt){
	if (apt == NULL){
		//Lista vazia
		return 0;
	}
	else{
		return 1 + (quantidade(apt->esq)) + (quantidade(apt->dir));
		
	}
}

//Conta a quantidade de folhas
int quantidadeFolhas(ABP apt){
	if (apt == NULL)
		return 0;
	if (apt->esq == NULL && apt->dir == NULL) {
		return 1;
	}
	else {
		return quantidadeFolhas(apt->esq) + quantidadeFolhas(apt->dir);
	}
}

//Calcula a altura da �rvore (Recursivo)
int altura(ABP apt){
	if (apt == NULL){
		return 0;
	}
	return 1 + max(altura(apt->esq), altura(apt->dir));
}

//Calcula a altura da �rvore (Iterativo)
int alturaIterativa(ABP apt){

	//Criar um FIFO vazio
	lista l = NULL;

	if (apt == NULL){
		//N�o existem n�s na �rvore bin�ria, n�o estamos aqui a fazer nada
		return 0;
	}

	//N� de �rvore bin�ria auxiliar
	ABP aux;
	
	//Inserir o nodo raiz na fila
	l = enqueue(l, apt);
	
	//Inicializar altura da �rvore bin�ria a 0
	int peso = 0;

	//Enquanto n�o tivermos o resultado..
	while (1){

		//Guardar o n� de elementos no FIFO
		int qtElementos = nElementosFIFO(l);
		if (qtElementos == 0){
			//O FIFO est� vazio, cheg�mos ao �ltimo n�vel da �rvore, temos o resultado
			return peso;
		}
		else{
			//A �rvore tem mais um n�vel
			peso++;
		}

		//Enquanto existirem elementos no FIFO..
		while (qtElementos > 0){
			//Retirar o elemento do FIFO
			l = dequeue(l, &aux);
			//Um elemento a menos no FIFO
			qtElementos--;
			//Adicionar os filhos deste n� ao FIFO
			if(aux->esq != NULL) l = enqueue(l, aux->esq);
			if(aux->dir != NULL) l = enqueue(l, aux->dir);
		}
	}
	
}

//N� de elementos no FIFO
int nElementosFIFO(lista l){
	if (l == NULL){
		return  0;
	}
	return 1 + nElementosFIFO(l->seguinte);
}

void listarFIFO(lista l)
{
	if (l != NULL)
	{
		while (l != NULL)
		{
			printf("\n\n\t\t%d", l->elemento);
			l = l->seguinte;
		}
	}
	else
	{
		printf("\n\n\t\tERRO: Fila vazia.");
	}
}

//Listagem de alunos por ordem crescente
void listagemCrescente(ABP apt){
	if (apt != NULL){
		listagemCrescente(apt->esq);
		printf("%d %d\n", apt->num, apt->nota);
		listagemCrescente(apt->dir);
	}
}

void listar(ABP apt){
	if (apt != NULL){
		printf("[%d, %d", apt->num, apt->nota);
		listar(apt->esq);
		printf(" , ");
		listar(apt->dir);
		printf("]");
	}
}

ABP nodoMax(ABP apt){
	if (apt != NULL){
		if (apt->dir != NULL){
			return nodoMax(apt->dir);
		}
		else {
			return apt;
		}
	}
	else{
		return NULL;
	}
}

ABP remover(ABP apt, int num){

	if (apt != NULL){

		ABP aux;

		if (apt->num > num){
			//O numero que procuramos � menor, seguir para a esquerda
			apt->esq = remover(apt->esq, num);
			return apt;
		}
		else if (apt->num < num){
			//O numero que procuramos � maior, seguir para a direita
			apt->dir = remover(apt->dir, num);
			return apt;
		}
		else if (apt->num == num){
			/*
			Encontr�mos o modo a remover!
			Verificar quais das condi��es � verdadeira:
			a) Nodo com duas sub�rvores vazias
			b) Nodo com uma sub�rvore vazia
			c) Nodo com duas sub�rvores n�o-vazias
			*/

			//a) Duas sub�rvores n�o vazias
			if (apt->esq == NULL && apt->dir == NULL){
				free(apt);
				return NULL;
			}

			//b) Nodo com uma das sub�rvore vazia
			if ((apt->esq != NULL && apt->dir == NULL)
				|| (apt->esq == NULL && apt->dir != NULL)){
				if (apt->esq != NULL && apt->dir == NULL){
					//Ramo direito vazio
					aux = apt->esq;
					free(apt);
					return aux;

				}
				else if (apt->esq == NULL && apt->dir != NULL){
					//Ramo esquerdo vazio
					aux = apt->dir;
					free(apt);
					return aux;
				}
			}

			//c) Nodo com duas sub�rvores n�o-vazias
			if (apt->esq != NULL && apt->dir != NULL){
				aux = nodoMax(apt->esq);
				apt->num = aux->num;
				apt->nota = aux->nota;
				apt->esq = remover(apt->esq, aux->num);
				return apt;
			}
		}
	}
	else{
		return NULL;
	}
}

//int balanceada(ABP apt){
//	if (apt == NULL){
//		//�rvore vazia, logo balanceada
//		return 1;
//	}
//	else{
//		int alturaEsquerda = altura(apt->esq);
//		int alturaDireita = altura(apt->dir);
//		if (abs(alturaEsquerda - alturaDireita) > 1){
//			//Econtr�mos um n� que n�o est� balanceado, podemos parar de testar
//			return 0;
//		}
//		if (abs(alturaEsquerda - alturaDireita) <= 1 &&
//			balanceada(apt->esq) == 1 &&
//			balanceada(apt->dir) == 1){
//			//Este n� est� balanceado
//			return 1;
//		}
//		//Se chegarmos aqui � porque n�o est� balanceada
//		return 0;
//	}
//		
//}

int balanceada(ABP apt){
	if (apt == NULL){
		return 1;
	}
	else if (abs(altura(apt->esq) - altura(apt->dir)) > 1){
		return 0;
	}
	else {
		return (balanceada(apt->esq) && balanceada(apt->dir));
	}
}

ABP nodoEnd(ABP apt){
	if (apt == NULL){
		return NULL;
	}
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
	apt = insereNovo(apt, 1000, 15);
	apt = insereNovo(apt, 1010, 13);
	apt = insereNovo(apt, 900, 13);
	apt = insereNovo(apt, 1020, 13);
	apt = insereNovo(apt, 1030, 13);

	listar(apt);
	printf("\n");
	
	printf("Nota do aluno 1100: %d\n", consultarNota(apt, 1100));
	printf("N de alunos: %d\n", quantidade(apt));
	listagemCrescente(apt);
	printf("Esta arvore tem %d folhas!\n", quantidadeFolhas(apt));
	
	
	printf("Altura da arvore: %d\n", alturaIterativa(apt));

	printf("\n\n");
	print_t(apt);

	/*apt = remover(apt, 800);

	printf("\n\n");
	print_t(apt);

	apt = remover(apt, 950);

	printf("\n\n");
	print_t(apt);

	apt = remover(apt, 1010);

	printf("\n\n");
	print_t(apt);*/

	printf("\n\n");
	printf("Balanceada? %d\n", balanceada(apt));

	return 1;
}