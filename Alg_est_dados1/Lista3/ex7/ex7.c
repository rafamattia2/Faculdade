//Nome: Rafael de Mattia
//Matrícula: 20200744
//Graduação em ciência da computação, terceiro semeste, cadeira de algoritmos e estruturas de dados I
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char nome[10];
    int idade;
    int numeroTelefone;
} Pessoa;

Pessoa pessoa[10];

int *adicionaPessoa(void *pBuffer);
int imprimeDados(void *pBuffer);
int *menu(void *pBuffer);

int main()
{
    void *pBuffer = malloc((sizeof(int) * 2) + sizeof(char));
    char enter = 0;
    if (pBuffer == NULL) 
    {
        printf("\n##Erro de alocacao##\n");
        return 0;
    }
    *(int *)pBuffer = 0; //para guardar o tamanho
    *(char *)(pBuffer + sizeof(int)) = 's'; //separador
    *(int *)(pBuffer + sizeof(int) + sizeof(char)) = 0; // menu
    

    do 
    {
		pBuffer = menu(pBuffer);
		switch (*(int *)(pBuffer + sizeof(int) + sizeof(char))) 
        {
		    case 1:
			    pBuffer = adicionaPessoa(pBuffer);
			    break;
            case 2:
			    imprimeDados(pBuffer);
			    break;
		    case 3:
                printf("\nPressione enter para sair\n");
                while (enter != '\r' && enter != '\n') { enter = getchar(); } //codigo para pressionar enter e abortar o programa.
			    break;
		}
	} while(*(int *)(pBuffer + sizeof(int) + sizeof(char)) != 3);

    free(pBuffer);
	return 0;
}

int *adicionaPessoa(void *pBuffer)
{
    if(*(int *)pBuffer < 10) 
    {
        printf("\nAdicione os dados a seguir: \n");
        printf("Nome: ");
        scanf("%s", pessoa[*(int *)pBuffer].nome);

        printf("\n-------------------: \n");
        printf("Idade: ");
        scanf("%d", &pessoa[*(int *)pBuffer].idade);

        printf("\n-------------------: \n");
        printf("Telefone: ");
        scanf("%d", &pessoa[*(int *)pBuffer].numeroTelefone);
        *(int *)pBuffer = *(int *)pBuffer + 1;

        return pBuffer;
    } else 
    {
        printf("O numero maximo de pessoas cadastrados foi atingido.");
        return NULL;
    }
}

int imprimeDados(void *pBuffer)
{
    if (*(int *)pBuffer != 0)
    {
        printf("## Pessoas cadastradas ##\n");
        for(*(int *)(pBuffer + sizeof(int) + sizeof(char)) = 0; 
            *(int *)(pBuffer + sizeof(int) + sizeof(char)) < *(int *)pBuffer;
            *(int *)(pBuffer + sizeof(int) + sizeof(char)) = *(int *)(pBuffer + sizeof(int) + sizeof(char)) + 1) 
        {
            printf("\nCadastro %d: | Nome: %s | Idade: %d | Telefone: %d \n", *(int *)(pBuffer + sizeof(int) + sizeof(char)) + 1, 
                                                                       pessoa[*(int *)(pBuffer + sizeof(int) + sizeof(char))].nome, 
                                                                       pessoa[*(int *)(pBuffer + sizeof(int) + sizeof(char))].idade,
                                                                       pessoa[*(int *)(pBuffer + sizeof(int) + sizeof(char))].numeroTelefone);
        }
    } else 
    {
        printf("\nAgenda vazia...\n");
        return 0;
    }

    return 0;
}

int *menu(void *pBuffer)
{

	do 
    {
		printf("\nMENU\n");
		printf("1) Adicionar cadastro\n");
		printf("2) Listar registros\n");
		printf("3) Sair\n");
		scanf("%d", &*(int *)(pBuffer + sizeof(int) + sizeof(char)));
	} while (*(int *)(pBuffer + sizeof(int) + sizeof(char)) <= 0 || *(int *)(pBuffer + sizeof(int) + sizeof(char)) > 3);

	getchar();

	return pBuffer;
}