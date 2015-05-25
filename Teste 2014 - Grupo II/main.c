#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

#define N 50

typedef struct aluno
{
	int numero;
	char *nome;
	char *curso;
	int notaPratica;
	int notaExame;
	struct aluno *next;
} * Aluno;

Aluno Curso1[N];
Aluno Curso2[N];

int fhash(int numero) // Calcula a chave de um aluno de acordo com o seu numero
{
	return (numero % N);
}

bool MesmaListaColisao(int numero1, int numero2){
	return (fhash(numero1) == fhash(numero2));
}

int main(){

		

	return 1;
}