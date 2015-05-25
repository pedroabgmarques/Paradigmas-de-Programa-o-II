#include<stdio.h>
#include<conio.h>


typedef struct equipa
{
	int codigo;
	char nome[50];
	int pontos;
	int jogos;
	int golosMarcados;
	int golosSofridos;
	struct equipa *next;


}*equipa;

typedef struct jogo
{
	int codigoEquipa1;
	int codigoEquipa2;
	char data[20];
	int golosEquipa1;
	int golosEquipa2;

}*jogo;

equipa inserirEquipa(equipa eq, int codigo, char nome[50])
{
	equipa aux;

	aux = malloc(sizeof(struct equipa));
	aux->codigo = codigo;
	strcpy(aux->nome, nome);
	aux->pontos = 0;
	aux->jogos = 0;
	aux->golosMarcados = 0;
	aux->golosSofridos = 0;
	aux->next = eq;
	return aux;
}

void listarEquipas(equipa eq)
{
	while (eq != NULL)
	{
		printf("\nCodigo: %d", eq->codigo);
		printf("\nEquipa: %s", eq->nome);
		printf("\nPontos: %d", eq->pontos);
		printf("\nJogos: %d", eq->jogos);
		printf("\nGolos Marcados: %d", eq->golosMarcados);
		printf("\nGolos Sofridos: %d", eq->golosSofridos);
		printf("\n--------------------------\n");
		eq = eq->next;
	}
}

void actualizarEquipa(equipa eq, int codigo, int pontos, int jogos, int GS, int GM)
{
	while (eq != NULL)
	{
		if (eq->codigo == codigo)
		{
			eq->pontos = pontos;
			eq->jogos += jogos;
			eq->golosSofridos += GS;
			eq->golosMarcados += GM;
		}
		eq = eq->next;
	}
}


int getPontos(equipa eq, int codigoEquipa)
{
	while (eq != NULL)
	{
		if (eq->codigo == codigoEquipa)
		{
			return(eq->pontos);
		}
		eq = eq->next;
	}
}


jogo inserirJogo(equipa equipas, jogo jg, int codEquipa1, int codEquipa2, char data[20], int golosEquipa1,
	int golosEquipa2)
{
	jogo aux;
	int pontosEquipa1 = getPontos(equipas, codEquipa1);
	int pontosEquipa2 = getPontos(equipas, codEquipa2);

	//insere jogo
	aux = malloc(sizeof(struct jogo));
	aux->codigoEquipa1 = codEquipa1;
	aux->codigoEquipa2 = codEquipa2;
	strcpy(aux->data, data);
	aux->golosEquipa1 = golosEquipa1;
	aux->golosEquipa2 = golosEquipa2;
	//calcula pontos
	if (golosEquipa1 > golosEquipa2)
	{
		pontosEquipa1 += 3;
	}
	else if (golosEquipa2 > golosEquipa1)
	{
		pontosEquipa2 += 3;
	}
	else if (pontosEquipa1 == pontosEquipa2)
	{
		pontosEquipa1 += 1;
		pontosEquipa2 += 1;
	}

	//actualiza equipas apos o jogo
	actualizarEquipa(equipas, codEquipa1, pontosEquipa1, 1,
		golosEquipa2, golosEquipa1);
	actualizarEquipa(equipas, codEquipa2, pontosEquipa2, 1,
		golosEquipa1, golosEquipa2);
	return aux;
}

equipa OrdenarPorPontos(equipa equipas)
{

	if (equipas == NULL || equipas->next == NULL)
		return equipas; // lista está ordenada

	//troca maior com o primeiro : 

	//1- encontra maior : 
	equipa curr, largest, largestPrev;
	curr = equipas;
	largest = equipas;
	equipa prev = equipas;
	largestPrev = equipas;
	while (curr != NULL) {
		if (curr->pontos > largest->pontos) {
			largestPrev = prev;
			largest = curr;
		}
		prev = curr;
		curr = curr->next;

	}
	//maior gaurdado em largest. 

	//2- troca primeiro com maior : 
	equipa tmp;
	if (largest != equipas)
	{
		largestPrev->next = equipas;
		tmp = equipas->next;
		equipas->next = largest->next;
		largest->next = tmp;
	}

	// maior ja está em primeiro.

	//percorre toda a lista recursivamente :
	largest->next = OrdenarPorPontos(largest->next);


	return largest;

}

void main()
{
	equipa equipas = NULL;
	jogo jogos = NULL;
	equipas = inserirEquipa(equipas, 001, "Morkians FC");
	equipas = inserirEquipa(equipas, 002, "Marmotas FC");
	equipas = inserirEquipa(equipas, 003, "TeamJC++ FC");
	equipas = inserirEquipa(equipas, 004, "EDJD FC");

	listarEquipas(equipas);

	jogos = inserirJogo(equipas, jogos, 001, 002, "10/6/2015", 2, 3);
	jogos = inserirJogo(equipas, jogos, 001, 002, "12/6/2015", 2, 3);
	jogos = inserirJogo(equipas, jogos, 001, 003, "18/06/2015", 1, 3);
	jogos = inserirJogo(equipas, jogos, 004, 003, "18/06/2015", 4, 3);
	printf("\nApos jogos\n");
	listarEquipas(equipas);
	equipas = OrdenarPorPontos(equipas);
	printf("\n Apos ordenar\n");
	listarEquipas(equipas);
	/*actualizarEquipa(equipas, 001, 3, 1, 1, 2);
	listarEquipas(equipas);*/

	system("pause");
}