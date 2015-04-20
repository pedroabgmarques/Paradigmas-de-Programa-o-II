#include <stdio.h>
#include <stdlib.h>

#define LINHAS 4
#define COLUNAS 4

int grafo[LINHAS][COLUNAS];

void inserirAresta(int origem, int destino, int peso){
	grafo[origem][destino] = peso;
}

void removerAresta(int origem, int destino){
	grafo[origem][destino] = 0;
	printf("Aresta %d -> %d removida.\n\n", origem, destino);
}

void listar(){
	for (int i = 0; i < LINHAS; i++){
		for (int j = 0; j < COLUNAS; j++){
			if (grafo[i][j] != 0){
				printf("%d -> %d: %d\n", i, j, grafo[i][j]);
			}
		}
	}
	printf("\n");
}

void sucessores(int vertice){
	printf("Sucessores de %d:\n", vertice);
	for (int i = 0; i < COLUNAS; i++){
		if (grafo[vertice][i] != 0){
			printf("%d -> %d : %d\n", vertice, i, grafo[vertice][i]);
		}
	}
}

int main(){

	inserirAresta(0, 2, 7);
	inserirAresta(0, 3, 10);
	inserirAresta(1, 1, 9);
	inserirAresta(2, 0, 5);
	inserirAresta(2, 3, 4);
	inserirAresta(3, 3, 13);
	inserirAresta(3, 1, 13);

	listar();

	removerAresta(1, 1);

	listar();

	sucessores(2);

	return 1;
}