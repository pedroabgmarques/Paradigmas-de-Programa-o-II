#include<stdio.h>
#include<conio.h>

#define N 4
int Grafo[N][N];
int GrafoVisitados[N][N];
int visitado[N];
int sucesrs[10];

void init()
{
	int i, j;
	for (int i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			Grafo[i][j] = -1;
		}
	}
}

void initArray(int visitado[N])
{
	int i, j;
	for (int i = 0; i < N; i++)
	{
		visitado[i] = 0;
	}
}

int insereAresta(int v1, int v2, int peso)
{
	if ((v1 >= 0) && (v1 < N) && (v2 >= 0) && (v2 < N))
	{
		Grafo[v1][v2] = peso;
		return(1);
	}
	else return(0);
}

void listarGrafo()
{
	int linha = 0, coluna = 0;
	for (linha = 0; linha < N; linha++)
	{
		for (coluna = 0; coluna < N; coluna++)
		{
			printf("%d ", Grafo[linha][coluna]);
		}
		printf("\n");
	}
}


void verificarCircuito(int grafo[N][N], int vertice, int visitados[N])
{
	if (visitados[vertice] == 1){
		//Já aqui tinhamos estado! Existe um circuito.
		printf("Existe circuito");
		return 1;
	}

	visitados[vertice] = 1;
	printf("%d ", vertice);

	for (int i = 0; i < N; i++){
		if (grafo[vertice][i] == 1){
			verificarCircuito(grafo, i, visitados);
		}
	}
}

void main()
{
	init(GrafoVisitados);
	initArray(visitado);
	insereAresta(0, 1, 1);
	insereAresta(1, 2, 1);
	insereAresta(2, 0, 1);
	listarGrafo();
	verificarCircuito(Grafo, 0, visitado);
	system("pause");
}