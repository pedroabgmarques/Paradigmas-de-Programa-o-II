#include <stdio.h>
#include <stdlib.h>

#define LINHAS 4
#define COLUNAS 4

int grafo[LINHAS][COLUNAS];

int visitado[LINHAS];

void inicializarGrafo(){
	for (int i = 0; i < LINHAS; i++){
		for (int j = 0; j < COLUNAS; j++){
			grafo[i][j] = -1;
		}
	}
}

void inserirAresta(int origem, int destino, int peso){
	if (origem >= 0 && origem < LINHAS && destino >= 0 && destino < COLUNAS){
		grafo[origem][destino] = peso;
	}
}

void removerAresta(int origem, int destino){
	grafo[origem][destino] = -1;
	printf("Aresta %d -> %d removida.\n\n", origem, destino);
}

void listar(){
	for (int i = 0; i < LINHAS; i++){
		for (int j = 0; j < COLUNAS; j++){
			if (grafo[i][j] != -1){
				printf("%d -> %d: %d\n", i, j, grafo[i][j]);
			}
		}
	}
	printf("\n");
}

void sucessores(int vertice){
	printf("\nSucessores de %d:\n", vertice);
	for (int i = 0; i < COLUNAS; i++){
		if (grafo[vertice][i] != -1){
			printf("%d -> %d : %d\n", vertice, i, grafo[vertice][i]);
		}
	}
}

void antecessores(int vertice){
	printf("\nAntecessores de %d:\n", vertice);
	if (vertice >= 0 && vertice < LINHAS){
		for (int i = 0; i < LINHAS; i++){
			if (grafo[i][vertice] != -1){
				printf("%d -> %d : %d\n", i, vertice, grafo[i][vertice]);
			}
		}
	}
}

void travessiaProfundidade(int vertice, int visitados[LINHAS]){
	visitados[vertice] = 1;
	printf("%d ", vertice);
	for (int i = 0; i < LINHAS; i++){
		if (grafo[vertice][i] != -1 && !visitados[i]){
			travessiaProfundidade(i, visitados);
		}
	}
}


int main(){

	int visitados[LINHAS];
	for (int i = 0; i < LINHAS; i++){
		visitados[i] = 0;
	}

	inicializarGrafo();

	inserirAresta(0, 1, 5);
	inserirAresta(0, 2, 10);
	inserirAresta(1, 2, 7);
	inserirAresta(2, 3, 2);


	listar();

	removerAresta(1, 1);

	listar();

	sucessores(2);

	antecessores(2);

	printf("\nTravessia em profundidade: (Depth-First)\n");
	travessiaProfundidade(0, visitados);
	printf("\n");

	return 1;
}