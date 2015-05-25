#include <stdio.h>

typedef struct listaLigada
{
	int n;
	struct listaLigada * next;
} * ListaLigada;

ListaLigada InserirUltimaPosicao(ListaLigada lista, int n){

	ListaLigada novo = (ListaLigada)malloc(sizeof(struct listaLigada));
	novo->n = n;
	novo->next = NULL;

	if (lista == NULL){
		lista = novo;
	}
	else{
		ListaLigada atual = lista;
		while (atual->next) {
			atual = atual->next;
		}
		atual->next = novo;
	}
	return lista;
}

ListaLigada JuntarListas(ListaLigada lista1, ListaLigada lista2){
	if (lista1 == NULL){
		//A primeira lista está vazia
		return lista2;
	}
	else if (lista2 == NULL){
		//A 2ª lista está vazia
		return lista1;
	}
	else{
		//Nenhuma das listas está vazia
		//Ligar a lista 2 ao fim da lista 1
		ListaLigada atual = lista1;
		while (atual->next) {
			atual = atual->next;
		}
		atual->next = lista2;
	}
	return lista1;
}

int Quantidade(ListaLigada lista){
	if (lista == NULL){
		return 0;
	}
	else{
		//A função invoca-se a ela própria
		return (1 + Quantidade(lista->next));
	}
}

void ImprimirListaLigada(ListaLigada lista){
	while (lista != NULL){
		printf("%d\n", lista->n);
		lista = lista->next;
	}
}

int main(){

	ListaLigada lista = NULL;
	lista = InserirUltimaPosicao(lista, 5);
	lista = InserirUltimaPosicao(lista, 10);
	lista = InserirUltimaPosicao(lista, 15);
	lista = InserirUltimaPosicao(lista, 20);

	ListaLigada lista2 = NULL;
	lista2 = InserirUltimaPosicao(lista2, 25);
	lista2 = InserirUltimaPosicao(lista2, 30);
	lista2 = InserirUltimaPosicao(lista2, 35);
	lista2 = InserirUltimaPosicao(lista2, 40);

	printf("Primeira Lista:\n");
	ImprimirListaLigada(lista);
	printf("Quantidade de elementos: %d\n\n", Quantidade(lista));

	printf("Segunda Lista:\n");
	ImprimirListaLigada(lista2);
	printf("Quantidade de elementos: %d\n\n", Quantidade(lista2));

	ListaLigada listaJunta = JuntarListas(lista, lista2);
	printf("Listas juntas:\n");
	ImprimirListaLigada(listaJunta);
	printf("\n");

	return 1;
}