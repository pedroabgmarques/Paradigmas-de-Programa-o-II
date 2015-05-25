#include <stdio.h>
#include <stdbool.h>

#define N 5

int grafo[N][N];

void inserirAresta(int origem, int destino){
	if (origem >= 0 && origem < N && destino >= 0 && destino < N){
		grafo[origem][destino] = 1;
	}
}

void listar(){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			if (grafo[i][j] == 1){
				printf("%d -> %d\n", i, j);
			}
		}
	}
	printf("\n");
}

int nSucessores(int vertice){
	int contador = 0;
	for (int i = 0; i < N; i++){
		if (grafo[vertice][i] == 1){
			contador++;
		}
	}
	return contador;
}

int ContarVerticesUmSucessor(){
	int contador = 0;
	for (int i = 0; i < N; i++){
		if (nSucessores(i) == 1){
			contador++;
		}
	}
	return contador;
}

bool VerificarCircuito3Vertices(int vertice1, int vertice2, int vertice3){

}

int main(){

	inserirAresta(0, 1);
	inserirAresta(0, 2);
	inserirAresta(1, 2);
	inserirAresta(2, 0);

	listar();
	
	printf("Numero de vertices com apenas 1 sucessor: %d\n", ContarVerticesUmSucessor());

	return 1;
}