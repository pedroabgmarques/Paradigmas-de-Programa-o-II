#include <stdio.h>

#define N 5

void InicializarGrafo(int grafo[N][N]){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			grafo[i][j] = 0;
		}
	}
}

int InserirAresta(int grafo[N][N], int origem, int destino){
	if (origem >= 0 && origem < N && destino >= 0 && destino < N){
		grafo[origem][destino] = 1;
		return 1;
	}
	else{
		return 0;
	}
}

int nSucessores(int grafo[N][N], int vertice){
	int contador = 0;
	for (int i = 0; i < N; i++){
		if (grafo[vertice][i] == 1){
			contador++;
		}
	}
	return contador;
}

void VerticesSemSucessores(int grafo[N][N]){
	printf("\nVertices sem sucessores: \n");
	for (int i = 0; i < N; i++){
		if (nSucessores(grafo, i) == 0){
			//Este vértice não tem sucessores!
			printf("%d; ", i);
		}
	}
	printf("\n");
}

void EscreverGrafo(int grafo[N][N]){
	printf("\n");
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			printf("%d ", grafo[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void RecolherArestas(grafo){
	int inserirValores = 1;
	int origem, destino = 0;
	printf("Insira -1 como origem para terminar de inserir arcos.\n\n");
	while (inserirValores){
		printf("Origem: ");
		scanf("%d", &origem);
		if (origem != -1){
			printf("Destino: ");
			scanf("%d", &destino);
			if (!InserirAresta(grafo, origem, destino)){
				printf("Valores fora dos limites. N = %d\n\n", N);
			}
			else{
				EscreverGrafo(grafo);
			}
		}
		else{
			inserirValores = 0;
		}
	}
}

int TravessiaProfundidade(int grafo[N][N], int vertice, int visitados[N]){
	if (visitados[vertice] == 1){
		//Já aqui tinhamos estado! Existe um circuito.
		printf(" (CIRCUITO: %d) ", vertice);
		return 1;
	}
	visitados[vertice] = 1;
	printf("%d ", vertice);

	for (int i = 0; i < N; i++){
		if (grafo[vertice][i] == 1 ){
			TravessiaProfundidade(grafo, i, visitados);
		}
	}
}

void InicializarVisitados(int visitados[N]){
	for (int i = 0; i < N; i++){
		visitados[i] = 0;
	}
}

int main(){

	int grafo[N][N];

	InicializarGrafo(grafo);

	//Recolher arestas do utilizador, com validações
	RecolherArestas(grafo);

	//Martelar arestas, para testes
	/*InserirAresta(grafo, 0, 1);
	InserirAresta(grafo, 0, 2);
	InserirAresta(grafo, 1, 2);
	InserirAresta(grafo, 2, 3);
	InserirAresta(grafo, 3, 1);
	InserirAresta(grafo, 3, 4);*/

	VerticesSemSucessores(grafo);

	int visitados[N];
	for (int i = 0; i < N; i++){
		InicializarVisitados(visitados);
		printf("\nTravessia em profundidade a partir do vertice %d: \n", i);
		TravessiaProfundidade(grafo, i, visitados);
		printf("\n\n");
	}

	return 1;
}