#include <stdio.h>

int main(){

	//Defini��o de vari�vel normal
	int a = 10;

	//Defini��o de apontador (vari�vel que cont�m endere�o de mem�ria)
	int *b;

	//Atribuir ao apontador b o endere�o de mem�ria de a
	b = &a;

	//Atribuir � vari�vel c o valor apontado pelo endere�o de mem�ria b
	int c = *b;

	printf("%d %d %d\n", a, b, c);

	(*b)++;

	printf("%d\n", a);

	printf("\n\n\n");

	return 1;
}