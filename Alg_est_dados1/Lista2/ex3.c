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
    int telefone;
} Agenda;


int indicefunc(char *pBuffer, char *nome);
char *incluir(char *pBuffer);
char *apagar(char *pBuffer);
int buscar(char *pBuffer);
int listar(char *pBuffer);
int menu(void);

int main()
{
    int selecaomenu;

    void *pBuffer = malloc(sizeof(int));
    if (pBuffer == NULL) 
    {
        printf("\nErro de alocacao!!!\n");
        return -1;
    }
    *(int *)pBuffer = 0; //typecasting do buffer 
    

    while(selecaomenu != 5) 
    {
		selecaomenu = menu();
		switch (selecaomenu) 
        {
		    case 1:
			    pBuffer = incluir(pBuffer);
			    break;
		    case 2:
			    pBuffer = apagar(pBuffer);
			    break;
		    case 3:
                buscar(pBuffer);
                break;
            case 4:
			    listar(pBuffer);
			    break;
		    case 5:
			    break;
		}
	}

    free(pBuffer);
	return 0;
}

int indicefunc(char *pBuffer, char *nome)
{
    int indice;
    int TamLista = *(int *)pBuffer;
    Agenda pessoa;

    for(indice = 0; indice < TamLista; indice++)
    {
        pessoa = *(Agenda *)(pBuffer + sizeof(int) + (sizeof(Agenda) * indice));

        if((strcmp(pessoa.nome, nome)) == 0)
        {
            printf("\nOperacao realizada.\n");
            return indice;
        }
    }

    printf("\nEste registro não existe\n");
    return -1;
}

char *incluir(char *pBuffer)
{
    int oTamLista = *(int *)pBuffer;
    int nTamLista = oTamLista + 1;
    Agenda pessoa;

    printf("\n\tDigite as informações a seguir:\n");
	printf("\nNome: ");
    scanf("%10s^\n", pessoa.nome);
    getc(stdin);

    printf("\n-------------------: \n");
	printf("Idade: ");
    scanf("%i", &pessoa.idade);

    printf("\n-------------------: \n");
	printf("Telefone: ");
    scanf("%i", &pessoa.telefone);
    
    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(Agenda) * nTamLista));
    if (!pBuffer)
    {
        printf("Erro de alocacao!\n");
        return NULL;
    }

    *(Agenda *)(pBuffer + sizeof(int) + (sizeof(Agenda) * oTamLista)) = pessoa;
    *(int *)pBuffer = nTamLista;
    return pBuffer;
}


char *apagar(char *pBuffer)
{
    int indice = -1;
    int proximoIndice;
    int oTamLista = *(int *)pBuffer;
    int nTamLista;
    char rmNome[10];
    Agenda pessoa;

    if(oTamLista == 0)
    {
        nTamLista = 0;
    } else {
        nTamLista = oTamLista - 1;
    }

    printf("\nDigite o nome da pessoa que deseja apagar da agenda: \n");
    scanf("%10s^\n", rmNome);
    getc(stdin);
    
    indice = indicefunc(pBuffer, rmNome);
    if(indice == -1)
    {
        return NULL;
    }

    proximoIndice = indice + 1;

    while(proximoIndice < oTamLista)
    {
        pessoa = *(Agenda *)(pBuffer + sizeof(int) + (sizeof(Agenda) * proximoIndice));
        *(Agenda *)(pBuffer + sizeof(int) + (sizeof(Agenda) * indice)) = pessoa;
        indice++;
        proximoIndice++;
    }
 
    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(Agenda) * nTamLista));
    *(int *)pBuffer = nTamLista;
    
    return pBuffer;
}

int buscar(char *pBuffer)
{
    int indice = -1;
    int TamLista = *(int *)pBuffer;
    char nome[10];
    Agenda pessoa;

    printf("\nDigite o nome da pessoa que deseja buscar: ");
    scanf("%10s^\n", nome);
    getc(stdin);

    indice = indicefunc(pBuffer, nome);
    if(indice == -1)
    {
        return -1;
    } else 
    {
        pessoa = *(Agenda *)(pBuffer + sizeof(int) + (sizeof(Agenda) * indice));
        printf("\nREGISTRO %i: \n", indice + 1);
        printf("\nNome: %s", pessoa.nome);
        printf("\nIdade: %i", pessoa.idade);
        printf("\nTelefone: %i\n", pessoa.telefone);
    }

    return 0;
}

int listar(char *pBuffer)
{
    int i = 0;
    int TamLista = *(int *)pBuffer;
    Agenda pessoa;

    if (TamLista != 0)
    {
        printf("\n\tLISTA DE PESSOAS REGISTRADAS:\n");
        for(i = 0; i < TamLista; i++)
        {
            pessoa = *(Agenda *)(pBuffer + sizeof(int) + (sizeof(Agenda) * i));
            printf("\nREGISTRO %i: \n", i + 1);
            printf("\nNome: %s", pessoa.nome);
            printf("\nIdade: %i", pessoa.idade);
            printf("\nTelefone: %i\n", pessoa.telefone);
            printf("\n-------------------: \n");
        }
    } else 
    {
        printf("\nAgenda vazia! :(\n");
        return -1;
    }
    return 0;
}

int menu(void)
{
	int i = 0;

	do 
    {
		printf("\n\tAGENDA DE PESSOAS:\n\n");
		printf("1. Incluir registro\n");
		printf("2. Apagar registro\n");
		printf("3. Buscar por nome\n");
		printf("4. Listar registros\n");
		printf("5. Sair\n");
		scanf("%d", &i);
	} while (i <= 0 || i > 5);
	getchar();
	return i;
}