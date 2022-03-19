#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main ()
{
    setlocale(LC_ALL, "Portuguese");
    
    
    char nomeadd[21], nomerm[21];       //strings de modificação
    char *str = (char*)calloc(2, sizeof(char));     //string principal
    int escolha, allocadd, buff1, buff2, i, tam;    //variáveis de modificação
    char *inicio_palavra, *fim_palavra, *teste;     //ponteiros para remover palavra
    
    INICIO:     
    printf("\n\nO que deseja fazer?\n");
    printf("\n1- Adicionar nome");
    printf("\n2- Remover nome");
    printf("\n3- Consultar lista de nomes");
    printf("\n4- Sair\n\n");
    scanf("%d", &escolha);
    fflush(stdin);

    switch(escolha)
    {
        case 1:
                printf("\nDigite o nome que quer adicionar (Max 20 letras): ");
                scanf("%s", &nomeadd);
                getc(stdin);
                allocadd=0;
                strcat(nomeadd, "|");       //concatena com o caractere divisor
                buff1=strlen(nomeadd);
                buff2=strlen(str);
                allocadd=buff1+buff2;       //Coloco o tamanho da lista + a palavra, preparando para o realloc
                str=(char*)realloc(str, allocadd*sizeof(char)+sizeof(char));        //Dois sizeof por necessidade do \0 que indica o fim da string
                strcat(str, nomeadd);
               // printf("%s", str);
            goto INICIO;
        
        case 2:
            printf("Insira o nome que deseja remover(Max 20 letras): ");
            scanf("%s", &nomerm);
            getc(stdin);
            strcat(nomerm, "|");
            teste = strstr(str, nomerm);

            if(teste !=  NULL)
            { 
                tam = strlen(nomerm);
                inicio_palavra = strstr(str, nomerm);
                fim_palavra = inicio_palavra;
                for(i=0; i<tam; i++) {fim_palavra++;};
                memcpy(inicio_palavra, fim_palavra, strlen(fim_palavra)+1);     
                tam = strlen(str);
                str = (char*)realloc(str, tam*sizeof(char)+sizeof(char));       //Dois sizeof por necessidade do \0 que indica o fim da string
            }
            else
            {
                printf("O nome não pertence a lista");
                goto INICIO;
            }
               
        case 3:
            printf("\n\n%s", str);
            goto INICIO; 

        case 4:
        free(str);
            return 0;
    }
}