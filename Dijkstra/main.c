#include <stdio.h>
#include <stdlib.h>

#define N 10

void inicializaMatriz(int grafo[N][N])
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			grafo[i][j] = -1;
		}
	}
}

void imprime(int grafo[N][N])
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		printf("\t");
		for (j = 0; j < N; j++)
		{
			printf("%d ", grafo[i][j]);
		}
		printf("\n");
	}
}

void criaAresta(int grafo[N][N], int origem, int destino, int peso)
{
	grafo[origem][destino] = peso;
}


int haCaminho(int grafo[N][N], int origem, int destino,
	int visitados[N])
{
	int j = 0;
	int res = 0;

	while (j < N && !res)
	{
		if (grafo[origem][j] != -1 && !visitados[j])
		{
			visitados[j] = 1;
			if (j == destino) { res = 1; }
			else
			{
				res = haCaminho(grafo, j, destino,
					visitados);
			}
		}
		j++;
	}
	return res;
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
				printf("%d Peso=%d\n", destino, peso + grafo[origem][j]);
			}
			else caminhos(grafo, j, destino, trajecto, pos,
				peso + grafo[origem][j]
				);
		}
		j++;
	}
}

void visitaProfundidade(int grafo[N][N], int visitados[N], int origem)
{
	int d;
	printf("%d ", origem);

	for (d = 0; d < N; d++)
	{
		if (grafo[origem][d] == 1 && !visitados[d])
		{
			visitados[d] = 1;
			visitaProfundidade(grafo, visitados, d);
		}
	}
}

void inicializaArray(int A[N])
{
	int i;
	for (i = 0; i < N; i++) A[i] = 0;
}

int main()
{
	// cria matriz com N vértices
	int grafo[N][N];
	int visitados[N];
	int trajecto[N];

	// inicializa matriz
	inicializaMatriz(grafo);
	criaAresta(grafo, 0, 1, 10);
	criaAresta(grafo, 1, 2, 5);
	criaAresta(grafo, 2, 0, 3);
	criaAresta(grafo, 0, 3, 7);
	criaAresta(grafo, 2, 3, 20);
	criaAresta(grafo, 3, 4, 12);
	criaAresta(grafo, 1, 5, 3);
	criaAresta(grafo, 3, 5, 0);
	criaAresta(grafo, 5, 4, 1);
	criaAresta(grafo, 3, 1, 5);
	criaAresta(grafo, 1, 0, 6);

	//imprime(grafo);
	inicializaArray(visitados);
	visitaProfundidade(grafo, visitados, 0);
	printf("\n");

	inicializaArray(visitados);
	if (haCaminho(grafo, 0, 4, visitados))
		printf("Ha caminho de %d para %d\n", 0, 4);
	else printf("Nao ha caminho de %d para %d\n", 0, 4);

	caminhos(grafo, 0, 5, trajecto, 0, 0);
}