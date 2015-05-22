#include <stdio.h>
#include <stdlib.h>

#define N 5

int grafo[N][N];

void inicializarGrafo(){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			grafo[i][j] = -1;
		}
	}
}

void inserirAresta(int origem, int destino, int peso){
	if (origem >= 0 && origem < N && destino >= 0 && destino < N){
		grafo[origem][destino] = peso;
	}
}

void removerAresta(int origem, int destino){
	grafo[origem][destino] = -1;
	printf("Aresta %d -> %d removida.\n\n", origem, destino);
}

void listar(){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			if (grafo[i][j] != -1){
				printf("%d -> %d: %d\n", i, j, grafo[i][j]);
			}
		}
	}
	printf("\n");
}

void sucessores(int vertice){
	printf("\nSucessores de %d:\n", vertice);
	for (int i = 0; i < N; i++){
		if (grafo[vertice][i] != -1){
			printf("%d -> %d : %d\n", vertice, i, grafo[vertice][i]);
		}
	}
}

int nSucessores(int vertice){
	int contador = 0;
	for (int i = 0; i < N; i++){
		if (grafo[vertice][i] != -1){
			contador++;
		}
	}
	return contador;
}


int arraySucessores[10][10];
void GetArraySucessores(int vertice){

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			arraySucessores[i][j] = 0;
		}
	}

	for (int i = 0; i < N; i++){
		if (grafo[vertice][i] != -1){
			arraySucessores[vertice][i] = i;
		}
	}
}

void antecessores(int vertice){
	printf("\nAntecessores de %d:\n", vertice);
	if (vertice >= 0 && vertice < N){
		for (int i = 0; i < N; i++){
			if (grafo[i][vertice] != -1){
				printf("%d -> %d : %d\n", i, vertice, grafo[i][vertice]);
			}
		}
	}
}

int travessiaProfundidade(int vertice, int visitados[N]){
	visitados[vertice] = 1;
	printf("%d ", vertice);
	
	for (int i = 0; i < N; i++){
		if (grafo[vertice][i] != -1 && !visitados[i]){
			travessiaProfundidade(i, visitados);
		}
	}
}

int visitado(int j, int trajecto[N], int pos)
{
	int res = 0, i = 0;
	while (!res && i<pos) {
		if (trajecto[i] == j) res = 1;
		i++;
	}
	return res;
}

void caminhos(int grafo[N][N], int origem, int destino,
	int trajecto[N], int pos, int peso)
{
	int i, j = 0;

	trajecto[pos] = origem;
	pos++;

	while (j < N)
	{
		if ((grafo[origem][j] != -1) && !visitado(j, trajecto, pos))
		{
			if (j == destino)
			{
				for (i = 0; i<pos; i++) printf("%d->", trajecto[i]);
				printf("%d Peso=%d\n", destino, peso);
			}
			else caminhos(grafo, j, destino, trajecto, pos,
				peso + grafo[origem][j]
				);
		}
		j++;
	}
}


int main(){

	int visitados[N];
	for (int i = 0; i < N; i++){
		visitados[i] = 0;
	}

	int trajeto[N];
	for (int i = 0; i < N; i++){
		trajeto[i] = 0;
	}

	int previous[50];
	for (int i = 0; i < 50; i++){
		previous[i] = 0;
	}

	inicializarGrafo();

	inserirAresta(0, 1, 10);
	inserirAresta(1, 2, 5);
	inserirAresta(2, 0, 3);
	inserirAresta(1, 5, 3);
	inserirAresta(2, 3, 10);
	inserirAresta(3, 1, 5);
	inserirAresta(3, 5, 0);
	inserirAresta(3, 4, 12);
	inserirAresta(5, 4, 1);
	

	listar();

	sucessores(0);

	antecessores(4);

	printf("\nTravessia em profundidade: (Depth-First)\n");
	travessiaProfundidade(0, visitados);
	printf("\n");

	printf("\n");
	caminhos(grafo, 0, 4, trajeto, 0, 0);

	return 1;
}