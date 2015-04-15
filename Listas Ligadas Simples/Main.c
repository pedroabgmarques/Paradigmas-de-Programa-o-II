#include <stdio.h>

typedef struct registo{
	int numero;
	int nota;
	struct registo *seguinte;
} * Aluno;

Aluno insereAluno(Aluno endereco, int numero, int nota){
	//Aloca o espaço necessário na memória
	//devolve o endereço de memória do espaço alocado
	Aluno aluno = (Aluno)malloc(sizeof(struct registo));
	//Dar os valores ao aluno
	aluno->numero = numero;
	aluno->nota = nota;
	aluno->seguinte = endereco;
	return aluno;
}

void escreverTurma(Aluno endereco){
	while (endereco != NULL){
		printf("%d: %d\n", endereco->numero, endereco->nota);
		endereco = endereco->seguinte;
	}
}

int quantidade(Aluno endereco){
	int contador = 0;
	while (endereco != NULL){
		contador++;
		endereco = endereco->seguinte;
	}
	return contador;
}

int main(){

	Aluno turma = NULL; //lista ligada vazia
	turma = insereAluno(turma, 3000, 17);
	turma = insereAluno(turma, 4000, 15);

	printf("%d alunos na turma:\n", quantidade(turma));
	escreverTurma(turma);

	return 1;
}