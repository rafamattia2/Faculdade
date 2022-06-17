//Nome: Rafael de Mattia
//Matrícula: 20200744
//Graduação em ciência da computação, terceiro semeste, cadeira de algoritmos e estruturas de dados I
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definições para utilizar no lugar da struct
#define NOME (sizeof(char)*10)
#define IDADE (sizeof(int))
#define TELEFONE (sizeof(int))

//Definições para utilizar a dupla ligação
#define LINK_ANTERIOR (sizeof(char) * 10) + sizeof(int) + sizeof(int) 
#define LINK_PROXIMO (sizeof(char) *10) + sizeof(int) + sizeof(int) + sizeof(void **)
#define INICIO *(void **)gerenciador
#define FINAL *(void **)(gerenciador + sizeof(void **))

//Definições para menu e lista
#define MENU_OP (int *)(pBuffer+sizeof(int)) 
#define TAMANHO_LISTA *(int *)pBuffer
 
int adicionaCadastro(void *pBuffer, void *gerenciador);
int removeCadastro(void *pBuffer, void *gerenciador);
int procuraCadastro(void *pBuffer,void *gerenciador);
int imprimeTodos(void *pBuffer, void *gerenciador);
void menu(int *op);

int main()
{
    void *gerenciador = malloc(sizeof(void *) + sizeof(void *));
    if (!gerenciador)
    {
      printf("\nerro\n");
      return -1;
    }
  
    INICIO = NULL;
    FINAL = NULL;
    void *pBuffer = malloc(sizeof(int) + sizeof(int));

    if (!pBuffer)
    {
        printf("\n##Erro de alocacao##\n");
        return -1; // -1 para codigo de erro de alocacao
    }
    TAMANHO_LISTA = 0;

    do 
    {
        *MENU_OP = 0;
        menu(MENU_OP);
        switch (*MENU_OP)
        {
            case 1:
                adicionaCadastro(pBuffer, gerenciador);
                break;

            case 2:
                removeCadastro(pBuffer, gerenciador);
                break;

            case 3:
                procuraCadastro(pBuffer, gerenciador);
                break;

            case 4:
                imprimeTodos(pBuffer, gerenciador);
                break;

            case 5:
                liberaMemoria(pBuffer, gerenciador);
                break;
        }

    }while (*MENU_OP != 5);
    free(gerenciador);
    free(pBuffer);
    return 0;
}

int adicionaCadastro(void *pBuffer, void *gerenciador)
{
    void *pessoa = malloc(NOME + IDADE + TELEFONE + sizeof(void **) + sizeof( void **));
    if (!pessoa)
    {
        printf("\n##Erro de alocacao##\n");
        return -1; // -1 para codigo de erro de alocacao
    }
  
    *(void **)(pessoa + LINK_ANTERIOR) = NULL; // IRÃO INICIALMENTE APONTAR PARA NULL
    *(void **)(pessoa + LINK_PROXIMO) = NULL;  // GARANTIAS DE QUE OS PONTEIROS DE LIGAÇÃO
    

    void *sentinela = NULL;
   
    printf("\nAdicione os dados a seguir: \n");
    printf("Nome(Max 10 letras): ");  
    scanf("%s", (char *)pessoa);            
    fflush(stdin);                            

    printf("\n-------------------: \n");
    printf("Idade: ");
    scanf("%d", (int *)(pessoa + NOME));

    printf("\n-------------------: \n");
    printf("Telefone: ");
    scanf("%d", (int *)(pessoa + NOME + IDADE));

    if (TAMANHO_LISTA == 0) //Se não tiver nenhum usuário cadastrado
    {
        INICIO = pessoa;
        FINAL = pessoa;
        TAMANHO_LISTA +=1;
        return 0;
    }
    else
    {
        sentinela = INICIO;

        while(sentinela != NULL) //Repete até chegar no final
        {
            if(strcmp((char *)pessoa, (char *)sentinela) > 0) //Entrará neste IF se o nome adicionado vier depois na ordem alfabética. 
            {
                if (*(void **)(sentinela + LINK_PROXIMO) == NULL) //Entrará neste IF se o próximo nome não estiver preenchido
                {
                    *(void **)(pessoa + LINK_ANTERIOR) = sentinela;
                    *(void **)(sentinela + LINK_PROXIMO) = pessoa;
                    FINAL = pessoa;
                    TAMANHO_LISTA += 1;
                    return 0;
                }
                
                if (strcmp((char *)(*(void **)(sentinela + LINK_PROXIMO)), (char *)pessoa) > 0)
                {
                    *(void **)(pessoa + LINK_ANTERIOR) = sentinela;
                    *(void **)(pessoa + LINK_PROXIMO) = *(void **)(sentinela + LINK_PROXIMO);
                    *(void **)(sentinela + LINK_PROXIMO) = pessoa;
                    *(void **)(*(void **)(sentinela + LINK_PROXIMO) + LINK_ANTERIOR) = pessoa;
                    TAMANHO_LISTA += 1;
                    return 0;
                }
                
            }
            else
            {
                *(void **)(pessoa + LINK_ANTERIOR) = NULL;
                *(void **)(pessoa + LINK_PROXIMO) = sentinela;
                *(void **)(sentinela + LINK_ANTERIOR) = pessoa;
                INICIO = pessoa;
                TAMANHO_LISTA += 1;
                return 0;
            }
            sentinela = *(void **)(sentinela + LINK_PROXIMO); //Coloca o sentinela no próximo da lista. 
        }
    return 0;
    }
}

int removeCadastro(void *pBuffer, void *gerenciador)
{
    if (TAMANHO_LISTA == 0)
    {
        printf("\nNenhum cadastro.\n");
        return 0;
    }

    char excluirCadastro[10];
    void *sentinela = INICIO;
    void *malloc_free = NULL;

    printf("\n Digite o nome de quem deseja remover dos cadastros: ");
    scanf ("%s", excluirCadastro);
    fflush(stdin);
    
    while(sentinela != NULL)
    {
        if ((strcmp(excluirCadastro, (char *)sentinela)) == 0) //Se for igual ao atual ele entra neste if
        {
            if(TAMANHO_LISTA == 1) //Se só tiver 1 pessoa na lista
            {
                malloc_free = INICIO;
                free(malloc_free);
                INICIO=NULL;
                FINAL=NULL;
                TAMANHO_LISTA = 0;
                return 0;
            }
            if (*(void **)(sentinela + LINK_ANTERIOR) == NULL) //Se for o primeiro da lista
            {
                malloc_free = INICIO;
                INICIO = *(void **)(malloc_free + LINK_PROXIMO);
                free(malloc_free);
                *(void **)((INICIO) + LINK_ANTERIOR) = NULL;
                TAMANHO_LISTA -= 1;
                return 0;
            }
            if(*(void **)(sentinela + LINK_PROXIMO) == NULL) //Se for o ultimo da lista
            {
                malloc_free = FINAL;
                FINAL = *(void **)(sentinela + LINK_ANTERIOR);
                free (malloc_free);
                *(void **)((FINAL) + LINK_PROXIMO) = NULL;
                TAMANHO_LISTA -= 1;
                return 0;
            }
            else //Se estiver no meio da lista;
            {
                *(void **)(malloc_free + LINK_PROXIMO) = *(void **)(sentinela + LINK_PROXIMO);
                malloc_free = sentinela;
                sentinela = *(void **)(sentinela + LINK_PROXIMO);
                *(void **)(sentinela + LINK_ANTERIOR) = *(void **)(sentinela + LINK_ANTERIOR); 
                free(malloc_free);
                TAMANHO_LISTA -= 1;
                return 0;
            }
            printf("\nNome encontrado e removido ta lista.\n");
        }
        else
        {
           malloc_free = sentinela; //Sera utilizado quando o cadastro a ser excluido estar no meio da lista
           sentinela = *(void **)(sentinela + LINK_PROXIMO); 
        }
    }
    return 0;
}

int procuraCadastro(void *pBuffer, void *gerenciador)
{
    if (TAMANHO_LISTA == 0)
    {
        printf("\nAgenda vazia! nenhum cadastro encontrado.\n");
        return 0;
    }

    char procurarCadastro[10];
    void *sentinela = INICIO;
    printf("\n Digite o nome de quem deseja remover dos cadastros: ");
    scanf ("%s", procurarCadastro);

    while(sentinela != NULL)
    {
        if((strcmp(procurarCadastro, (char *)sentinela)) == 0)
        {
            printf("\nNome: %s\n", (char *)sentinela); 
            printf("Idade: %i\n", *(int *)(sentinela + NOME));                                                    
            printf("Telefone: %i \n", *(int *)(sentinela + NOME + IDADE));
            return 0;
        }
        else
        {
            sentinela = *(void **)(sentinela +LINK_PROXIMO);
        }
    }
    printf("\nNome não encontrado\n");
    return 0;
}

int imprimeTodos(void *pBuffer, void *gerenciador)
{
    if (TAMANHO_LISTA == 0)
    {
        printf("\nAgenda vazia! nenhum cadastro encontrado.\n");
        return 0;
    }
    
    void *sentinela = INICIO;
    printf("\n----------\nCadastros:\n----------");
    while (sentinela != NULL)
    {
        printf("\nNome: %s\n", (char *)sentinela); 
        printf("Idade: %i\n", *(int *)(sentinela + NOME));                                                    
        printf("Telefone: %i \n", *(int *)(sentinela + NOME + IDADE));
        sentinela = *(void **)(sentinela + LINK_PROXIMO);
    }
    return 0;
}

void menu(int *op)
{
	do 
    {
		printf("\nMENU\n");
		printf("1) Adicionar cadastro\n");
		printf("2) Apagar cadastro\n");
        printf("3) Buscar cadastro\n");
        printf("4) Listar todos os cadastros\n");
		printf("5) Sair\n");
		scanf("%d", op);
	} while (*op <= 0 || *op > 5);
    fflush(stdin);

}

int liberaMemoria(void *pBuffer, void *gerenciador)
{
    if (TAMANHO_LISTA == 0)
    {
        return 0;
    }
    void *malloc_free = NULL;
    while (INICIO != NULL)
    {
        malloc_free = INICIO;
        INICIO = *(void **)(malloc_free + LINK_PROXIMO);
        free(malloc_free);
    }
}