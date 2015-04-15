#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct elem2
{
	int coef;
	int grau;
	struct elem2 * seguinte;
	struct elem2 * anterior;
} *Monomio;

typedef struct elem1
{
	char id[20];
	struct elem1 * seguinte;
	struct elem1 * anterior;
	Monomio monomios;
} *Polinomio;

Polinomio inserirMonomio(Polinomio apt, char* id, int cf, int gr);
Monomio inserirOrdenado(Monomio apt, int cf, int gr);


// Inserir um novo monomio no polinomio 'id'
Polinomio inserirMonomio(Polinomio apt, char* id, int cf, int gr)
{
	Monomio novo;
	Polinomio poli;
	if ((cf != 0) && (gr >= 0))
	{
		if (apt == NULL)
		{
			novo = (Monomio)malloc(sizeof(struct elem2));
			novo->coef = cf;
			novo->grau = gr;
			novo->seguinte = NULL;
			novo->anterior = NULL;
			poli = (Polinomio)malloc(sizeof(struct elem1));
			strcpy(poli->id, id);
			poli->anterior = NULL;
			poli->seguinte = NULL;
			poli->monomios = novo;
			return(poli);
		}
		else if (!strcmp(apt->id, id))
		{
			apt->monomios = inserirOrdenado(apt->monomios, cf, gr);
			return(apt);
		}
		else {
			apt->seguinte = inserirMonomio(apt->seguinte, id, cf, gr);
			apt->seguinte->anterior = apt;
			return(apt);
		}
	}
	else return(apt);
}

// Inser��o ordenada de novo mon�mio
Monomio inserirOrdenado(Monomio apt, int cf, int gr)
{
	Monomio novo;
	if (apt == NULL)
	{
		novo = (Monomio)malloc(sizeof(struct elem2));
		novo->seguinte = NULL;
		novo->anterior = NULL;
		novo->coef = cf;
		novo->grau = gr;
		return(novo);
	}
	else if (apt->grau < gr)
	{
		novo = (Monomio)malloc(sizeof(struct elem2));
		novo->coef = cf;
		novo->grau = gr;
		novo->seguinte = apt;
		if (apt->anterior != NULL) apt->anterior->seguinte = novo;
		novo->anterior = apt->anterior;
		apt->anterior = novo;
		return(novo);
	}
	else if (apt->grau == gr)
	{
		apt->coef += cf;
		return(apt);
	}
	else {
		apt->seguinte = inserirOrdenado(apt->seguinte, cf, gr);
		apt->seguinte->anterior = apt;
		return(apt);
	}
}

void listar(Polinomio apt, char* id)
{
	Monomio aux;
	if ((apt != NULL) && (strcmp(apt->id, id))) listar(apt->seguinte, id);
	else if ((apt != NULL) && (!strcmp(apt->id, id)))
	{
		aux = apt->monomios;
		printf("%s=", id);
		while (aux != NULL)
		{
			if (aux->anterior == NULL) printf("%dx^%d ", aux->coef, aux->grau);
			else if ((aux->grau == 0) && (aux->coef>0)) printf("+%d ", aux->coef);
			else if ((aux->grau == 0) && (aux->coef<0)) printf("%d ", aux->coef);
			else if ((aux->grau == 1) && (aux->coef<0)) printf(" %dx ", aux->coef);
			else if ((aux->grau == 1) && (aux->coef>0)) printf(" +%dx ", aux->coef);
			else if (aux->coef>0) printf("+%dx^%d ", aux->coef, aux->grau);
			else printf("%dx^%d ", aux->coef, aux->grau);
			aux = aux->seguinte;
		}
		printf("\n");
	}

}

// Soma de dois polin�mios
// id3 = id1 + id2;
Polinomio somar(Polinomio apt, char* id1, char* id2, char* id3)
{
	Polinomio aux = apt;
	Monomio listaMonomios1 = NULL, listaMonomios2 = NULL;
	int encontrado = 0;
	while ((aux != NULL) && (encontrado<2))
	{// Determinar lista de mon�mios dos polinomios 'id1' e 'id2'
		if (!strcmp(aux->id, id1))
		{
			encontrado++;
			listaMonomios1 = aux->monomios;
		}
		else if (!strcmp(aux->id, id2))
		{
			encontrado++;
			listaMonomios2 = aux->monomios;
		}
		aux = aux->seguinte;
	}
	if (encontrado == 2)
	{
		while (listaMonomios1 != NULL)
		{
			apt = inserirMonomio(apt, id3, listaMonomios1->coef, listaMonomios1->grau);
			listaMonomios1 = listaMonomios1->seguinte;
		}
		while (listaMonomios2 != NULL)
		{
			apt = inserirMonomio(apt, id3, listaMonomios2->coef, listaMonomios2->grau);
			listaMonomios2 = listaMonomios2->seguinte;
		}
	}
	return(apt);
}

void main()
{
	Polinomio lista = NULL;

	lista = inserirMonomio(lista, "p1", 2, 5);
	lista = inserirMonomio(lista, "p1", 7, 3);
	lista = inserirMonomio(lista, "p1", 8, 15);
	listar(lista, "p1");

	lista = inserirMonomio(lista, "p2", 2, 3);
	lista = inserirMonomio(lista, "p2", 5, 3);
	lista = inserirMonomio(lista, "p2", 7, 2);
	listar(lista, "p2");
	lista = somar(lista, "p1", "p2", "p3");
	listar(lista, "p3");
	system("pause");


}

