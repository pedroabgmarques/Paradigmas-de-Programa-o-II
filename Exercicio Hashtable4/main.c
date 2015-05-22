#include <stdio.h>
#include <conio.h>

#define N 50
int nElementos = 0;

typedef struct livro
{
	char codigo[50];
	char titulo[100];
	int anoEdicao;
	struct livro * proximo;
} * livro;

//Alínea a)
int fHash(char codigo[]){
	int sum, i;
	for (i = 0; i < strlen(codigo); i++){
		sum += codigo[i];
	}
	return sum % N;
}

//Alínea b)
livro Biblioteca[N];

void InserirLivro(char codigo[], char titulo[], int anoEdicao){

	//Calcula a chave para este livro
	int ch;
	ch = fHash(codigo);
	//Aloca um novo livro em memória
	livro aux;
	aux = malloc(sizeof(struct livro));

	//Guardar dados do livro
	strcpy(aux->codigo, codigo);
	strcpy(aux->titulo, titulo);
	aux->anoEdicao = anoEdicao;
	aux->proximo = Biblioteca[ch];

	Biblioteca[ch] = aux;

	printf("Registo inserido!\n");

	nElementos++;
	
}

void ImprimirHashtable(){
	printf("---------\n");
	printf("IMPRIMIR\n");
	int i;
	livro aux;
	printf("\n");
	for (i = 0; i < N; i++){
		aux = Biblioteca[i];
		while (aux != NULL){
			printf("aux: %d\n", aux);
			printf("Titulo: %s\n", aux->titulo);
			printf("Codigo: %s\n", aux->codigo);
			printf("Ano Edicao: %d\n", aux->anoEdicao);
			aux = aux->proximo;
			printf("\n");
		}
	}
	printf("---------\n");
}

void PesquisarLivro(char codigo[]){

	printf("\n---------\n");
	printf("PESQUISA\n\n");
	//Calcular a chave do livro
	int ch;
	ch = fHash(codigo);

	//Primeiro endereço da lista ligada nesta posicao do array
	livro aux;
	aux = Biblioteca[ch];
	printf("aux: %d\n", aux);

	//Percorrer a lista e procurar o codigo pedido
	int encontrado = 0;
	while (aux != NULL && !encontrado){
		printf("%s / %s\n", aux->codigo, codigo);
		if (!strcmp(aux->codigo, codigo)){
			printf("Titulo: %s\n", aux->titulo);
			printf("Codigo: %s\n", aux->codigo);
			printf("Ano Edicao: %d\n", aux->anoEdicao);
			encontrado = 1;
		}
		else{
			aux = aux->proximo;
		}
	}
	if (!encontrado){
		printf("Livro nao encontrado!\n");
	}
	printf("---------\n");

}

float FactorCarga(){
	float tamanho = N;
	return (nElementos / tamanho);
}

int main(){

	InserirLivro("A23GHXXX", "Marmotas - Monografia da fauna do IPCA", 2015);
	InserirLivro("FGD45JJh", "Morkians - O Regresso", 2015);

	ImprimirHashtable();

	PesquisarLivro("A23GHXXX");

	printf("\n\nFactor de Carga: %f\n\n", FactorCarga());

	return 1;
}