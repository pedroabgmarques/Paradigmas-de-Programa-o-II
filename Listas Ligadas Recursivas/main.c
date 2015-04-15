#include <stdio.h>

typedef struct registo{
	int numero;
	int nota;
	struct registo *seguinte;
} *Aluno;

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

//Listagem recursiva
int escreverTurma(Aluno endereco){
	if (endereco == NULL){
		return 0;
	}
	else{
		printf("%d: %d\n", endereco->numero, endereco->nota);
		escreverTurma(endereco->seguinte);
	}
}

//Nota maior recursiva
int notaMaior(Aluno endereco){
	int maiorNota;
	if (endereco == NULL){
		return 0;
	}
	else{
		maiorNota = notaMaior(endereco->seguinte);
		if (endereco->nota > maiorNota){
			return endereco->nota;
		}
		else{
			return maiorNota;
		}
	}
}

//Nota maior recursiva, outra forma
void maior3(Aluno endereco, int* v){
	if (endereco != NULL){
		if (endereco->nota > *v){
			*v = endereco->nota;
		}
		maior3(endereco->seguinte, v);
	}
}

//Média da turma recursiva
float somaNotasTurma(Aluno endereco, float* v){
	if (endereco != NULL){
		*v += endereco->nota;
		somaNotasTurma(endereco->seguinte, v);
	}
}

//Contagem de alunos recursiva
int quantidade(Aluno endereco){
	if (endereco == NULL){
		return 0;
	}
	else{
		//A função invoca-se a ela própria
		return (1 + quantidade(endereco->seguinte));
	}
}

//Remover um item da lista ligada - iterativamente
Aluno remover(Aluno endereco, int numero)
{
	Aluno anterior = endereco, actual = endereco, aux;
	if (actual == NULL) return(NULL);
	else if (actual->numero == numero)
	{
		aux = actual->seguinte;
		free(actual);
		return(aux);
	}
	else
		while (actual != NULL)
		{
			if (actual->numero == numero)
			{
				anterior->seguinte = actual->seguinte;
				free(actual);
				return(endereco);
			}
			else
			{
				anterior = actual;
				actual = actual->seguinte;
			}
		}
	return (endereco);
}

//Remover elemento da lista ligada - recursivamente
Aluno removerRecursivo(Aluno enderecoInicioLista, int numeroAlunoRemover){
	Aluno aux;
	if (enderecoInicioLista != NULL){
		//Lista não está vazia
		if (enderecoInicioLista->numero == numeroAlunoRemover){
			//encontramos o elemento a eliminar
			aux = enderecoInicioLista->seguinte;
			free(enderecoInicioLista);
			return aux;
		}
		else{
			//não é este o elemento e eliminar, continuar a recursão
			enderecoInicioLista->seguinte = removerRecursivo(enderecoInicioLista->seguinte, numeroAlunoRemover);
			return enderecoInicioLista;
		}
	}
	else{
		//Lista vazia
		return enderecoInicioLista;
	}
}

//Inserir novo registo passando a posição por parâmetro - iterativa
Aluno inserirPos(Aluno apt, int num, int nt, int pos){
	Aluno aux, ant = apt, act = apt;
	while ((act != NULL) && (pos > 1)){
		ant = act;
		act = act->seguinte;
		pos--;
	}
	if ((pos == 1) && (act == apt)){
		return insereAluno(apt, num, nt);
	}
	else if(pos == 1){
		ant->seguinte = insereAluno(act, num, nt);
		return apt;
	}
	else{
		return apt;
	}
}

//Inserir novo registo passando a posição por parâmetro - recursivamente
Aluno inserirPosR(Aluno apt, int num, int nt, int pos){
	if (pos == 1){
		return insereAluno(apt, num, nt);
	}
	else if(apt != NULL){
		apt->seguinte = inserirPosR(apt->seguinte, num, nt, pos - 1);
		return apt;
	}
	else{
		return apt;
	}
}

int main(){

	Aluno turma = NULL; //lista ligada vazia

	turma = insereAluno(turma, 3000, 17);
	turma = insereAluno(turma, 4000, 15);
	turma = insereAluno(turma, 5000, 18);
	turma = insereAluno(turma, 6000, 14);
	turma = insereAluno(turma, 7000, 8);
	turma = insereAluno(turma, 8000, 12);
	turma = insereAluno(turma, 9000, 11);
	turma = insereAluno(turma, 10000, 16);
	turma = inserirPosR(turma, 12000, 13, 3);

	printf("%d alunos na turma:\n", quantidade(turma));
	escreverTurma(turma);
	printf("Nota maior: %d\n", notaMaior(turma));

	int nota = 0;
	maior3(turma, &nota);
	printf("Maior nota: %d\n", nota);

	float media = 0;
	somaNotasTurma(turma, &media);
	printf("Media de notas da turma:: %f\n", media / quantidade(turma));

	turma = removerRecursivo(turma, 5000);

	printf("\n%d alunos na turma:\n", quantidade(turma));
	escreverTurma(turma);

	return 1;
}