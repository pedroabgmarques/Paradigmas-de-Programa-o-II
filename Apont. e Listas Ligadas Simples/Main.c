#include <stdio.h>

int main(){

	//Definição de variável normal
	int a = 10;

	//Definição de apontador (variável que contém endereço de memória)
	int *b;

	//Atribuir ao apontador b o endereço de memória de a
	b = &a;

	//Atribuir à variável c o valor apontado pelo endereço de memória b
	int c = *b;

	printf("%d %d %d\n", a, b, c);

	(*b)++;

	printf("%d\n", a);

	printf("\n\n\n");

	return 1;
}