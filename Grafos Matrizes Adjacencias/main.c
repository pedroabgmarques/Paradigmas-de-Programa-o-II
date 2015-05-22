#include <stdio.h>
#include <stdlib.h>

#define N 5

void inicializaMatriz(int grafo[N][N])
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			grafo[i][j] = 0;
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

void criaArco(int grafo[N][N], int origem,
	int destino, int orientado)
{
	grafo[origem][destino] = 1;
	if (!orientado) { grafo[destino][origem] = 1; }
}

int haCaminho(int grafo[N][N], int origem, int destino)
{
	int j = 0;
	int res = 0;

	while (j < N && !res)
	{
		if (grafo[origem][j] != 0)
		{
			if (j == destino) { res = 1; }
			else
			{
				res = haCaminho(grafo, j, destino);
			}
		}
		j++;
	}
	return res;
}

int haCaminho2(int grafo[N][N], int origem, int destino,
	int visitados[N])
{
	int j = 0;
	int res = 0;

	while (j < N && !res)
	{
		if (grafo[origem][j] != 0 && !visitados[j])
		{
			visitados[j] = 1;
			if (j == destino) { res = 1; }
			else
			{
				res = haCaminho2(grafo, j, destino,
					visitados);
			}
		}
		j++;
	}
	return res;
}

void visitaProfundidade(int grafo[N][N], int visitados[N], int origem)
{
	int d;
	printf("%d ", origem + 1);

	for (d = 0; d < N; d++)
	{
		if (grafo[origem][d] == 1 && !visitados[d])
		{
			visitados[d] = 1;
			visitaProfundidade(grafo, visitados, d);
		}
	}
}

int main()
{
	int orientado;

	printf("Orientado?");
	scanf("%d", &orientado);

	// 2. cria matriz com N nodos
	int grafo[N][N];

	// 3. inicializa matriz
	inicializaMatriz(grafo);
	imprime(grafo);

	int origem, destino;
	printf("Origem: ");
	scanf("%d", &origem);
	printf("Destino: ");
	scanf("%d", &destino);
	while (origem && destino)
	{
		criaArco(grafo, origem - 1, destino - 1,
			orientado);
		printf("Origem: ");
		scanf("%d", &origem);
		printf("Destino: ");
		scanf("%d", &destino);
	}

	/*printf("\nHa caminho:\n");
	printf("Origem: ");
	scanf("%d", &origem);
	printf("Destino: ");
	scanf("%d", &destino);                       */
	imprime(grafo);
	int visitados[N], i;
	for (i = 0; i < N; i++) { visitados[i] = 0; }

	visitaProfundidade(grafo, visitados, origem - 1);

	for(i = 0; i < N; i++) { visitados[i] = 0; }
	   if (haCaminho2(grafo, origem-1, destino-1, visitados))
	{
	printf("Ha caminho de %d para %d\n",
	origem, destino);
	}
	else
	{
	printf("Nao ha caminho de %d para %d\n",
	origem, destino);
	}
	

	system("pause");

}
