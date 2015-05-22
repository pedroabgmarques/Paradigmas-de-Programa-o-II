#include <stdio.h>
#include <conio.h>

#define N 50

typedef struct ll
{
	int numero;
	float nota;
	int codDisciplina;
	struct ll * proximo;
} lista;

lista * Escola[N];


int fhash(int numero)        // Calcula a chave de um aluno
{
	return (numero % N);
}



void insere(int num, float nota, int cd)  //Funcao para inserir na tabela hash a nota de um aluno

// esta funcao insere a infornacao de um aluno sempre no inicio
// da lista ligada associada à sua chave

{
	int ch;   // Guarda a chave do aluno
	lista * aux;

	ch = fhash(num);   // Acha a chave para o aluno especificado

	aux = malloc(sizeof(struct ll));  //aloca uma nova celula na memoria

	aux->numero = num;         // Carrega o campo numero da nova celula
	aux->nota = nota;          // Carrega a nota no campo nota da nova celula
	aux->codDisciplina = cd;   // Carrega o cod disciplina na nova celula

	aux->proximo = Escola[ch];  // O campo proximo da nova celula toma o valor do endere�o da ultima celula da lista ligada

	Escola[ch] = aux;           // coloca a posicao ch do array a apontar para a nova c�lula

	printf("\n\n Registo Introduzido na Tabela de Hash \n\n");

}

float Devolve_Nota(int num, int cd)

{
	int ch, res = -1;
	lista * aux;      //cria a variavel aux do tipo lista ligada

	// 1º Acha a chave do aluno especificado
	ch = fhash(num);

	aux = Escola[ch];     //vai buscar o primeiro endereço da lista ligada ao array no indice ch

	while ((aux != NULL) && (res == -1))    //percorre toda a lista ligada ate encontrar o numero de aluno (num) e codigo da disciplina (cd)

	{
		if ((num == aux->numero) && (cd == aux->codDisciplina))
		{
			res = aux->nota;   //se verificar a condicao acima retorna o campo nota

		}
		else
		{
			aux = aux->proximo;  //vai para a celula seguinte da lista ligada
		}
	}
	return(res);
}


void main()

{
	int sentinela;
	char tecla;

	int nr_aluno;
	float nota_aluno;
	int cod_disc;

	sentinela = 0;

	while (sentinela != 1)

	{
		clrscr();

		printf("**** INSERIR REGISTOS **** \n\n");

		printf("Digite o numero de aluno : ");
		scanf("%d", &nr_aluno);

		printf("Digite a nota do aluno : ");
		scanf("%f", &nota_aluno);

		printf("Digite o codigo da disciplina : ");
		scanf("%d", &cod_disc);

		//insere na tabela de hash
		insere(nr_aluno, nota_aluno, cod_disc);

		printf("Deseja continuar [0 - Sim ; 1 - Nao] : ");
		scanf("%d", &sentinela);

	}

	// consulta a nota de um aluno a uma disciplina  //

	clrscr();

	printf("**** CONSULTA DE REGISTOS **** \n\n");

	printf("Digite o numero de aluno a consultar : ");
	scanf("%d", &nr_aluno);

	printf("Digite o codigo da disciplina a consultar : ");
	scanf("%d", &cod_disc);

	//Procura a nota do aluno / cod displina na tabela de hash usando a funcao de procura Devolve_Nota
	nota_aluno = Devolve_Nota(nr_aluno, cod_disc);

	printf("\n\n A NOTA DO ALUNO Nº %d PARA A DISCIPLINA %d - %f VALORES", nr_aluno, cod_disc, nota_aluno);

	getch();

}






