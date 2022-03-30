//Nome: Rafael de Mattia
//Matrícula: 20200744
//Graduação em ciência da computação, terceiro semeste, cadeira de algoritmos e estruturas de dados I
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char nome[30];
    int idade;
    int altura;
}Pessoa;

Pessoa *adicionaPessoa(Pessoa *buffer, int tamanho);
int imprimeDados(Pessoa *buffer, int tamanho);
int menu();

int main(){
    int tamanho = 0, m=0;
    char enter = 0;
    Pessoa *buffer = malloc(sizeof(int));
    
    if (buffer == NULL) 
    {
        printf("\n##Erro de alocacao##");
        return 0;
    }

    do 
    {

        m = menu();
		switch (m) 
        {
		    case 1:
                tamanho++;
			    buffer = adicionaPessoa(buffer, tamanho);
			break;
		
        case 2:
			imprimeDados(buffer, tamanho);
            printf("\nPressione enter para sair\n");
            while (enter != '\r' && enter != '\n') { enter = getchar(); } //codigo para pressionar enter e abortar o programa.
			break;
        }
	} while(m != 2);

    free(buffer);
	return 0;
}

Pessoa *adicionaPessoa(Pessoa *buffer, int tamanho)
{
    int tamanhoAntigo = tamanho-1; //
    Pessoa pessoa;
    buffer = realloc(buffer, sizeof(Pessoa) * tamanho);

    if (buffer == NULL)
    {
        printf("\n##Erro de alocacao##");
        return NULL;
    }

    printf("\nAdicione os dados a seguir: \n");
	printf("Nome: ");
    scanf("%s", pessoa.nome);
    getc(stdin);

    printf("\n-------------------: \n");
	printf("\nIdade: ");
    scanf("%d", &pessoa.idade);

    printf("\n-------------------: \n");
	printf("\nAltura: ");
    scanf("%d", &pessoa.altura);

    if(tamanho > 1)
    {
        *(buffer + (sizeof(Pessoa) * tamanhoAntigo)) = pessoa;
    } else {
        *(buffer) = pessoa;
    }

    return buffer;
}

int imprimeDados(Pessoa *buffer, int tamanho){
    int i;
    Pessoa pessoa;

    if (tamanho != 0)
    {
        for(i = 0; i < tamanho; i++)
        {
            pessoa = *(buffer + (sizeof(Pessoa) * i));
            printf("\n%i:", i + 1);
            printf("\nNome: %s | Idade: %d | Altura: %d", pessoa.nome, pessoa.idade, pessoa.altura);
        }
    } else {
        printf("\nNao foram cadastrados dados");
        return 0;
    }
    return 0;
}

int menu()
{
	int m = 0;
	do 
    {
        printf("\nDeseja cadastrar uma pessoa?\n");
        printf("1) Sim\n2) Nao\n");
		scanf("%d", &m);
	} while (m < 1 || m > 2);
	getc(stdin);
	return m;
}