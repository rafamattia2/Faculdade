//Nome: Rafael de Mattia
//Matrícula: 20200744
//Graduação em ciência da computação, terceiro semeste, cadeira de algoritmos e estruturas de dados I

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int imprimeVetor (int *vetor, int tam)
{
    int i=0;
    printf("\n");
    for (i=0; i<tam; i++)
    {
        printf("%i, ", vetor[i]);
    }
    return 0;
}  

int mainMenu()
{
    int i=0;
    
    while (i<=0 || i>5)
    {
        printf("\n##Escolha qual algoritmo de ordenacao deseja utilizar: \n");
        printf("##1 - Insertion sort\n");
        printf("##2 - Selection sort\n");
        printf("##3 - Quik sort\n");
        printf("##4 - Merge sort\n");
        printf("##5 - Bateria de testes\n");
        printf("Escolha: ");
        scanf("%i", &i);
        fflush(stdin);
    }

    return i;
}

int test(int *vetor, int tam)
{
    int i;
    for(i=0; i < tam; i++)
    {
        if(vetor[i] > vetor[i + 1])
        {
            printf("\n O vetor nao esta ordenado \n");
            return -1;
        }
    }
    return 0;
}

int insertionSort (int *vetor, int tam)
{
    int i, j, temp;

    for(i = 1; i < tam; i++)
    {
        temp = vetor[i];
        for(j = i; (j > 0) && (temp < vetor[j-1]); j--)
        {
            vetor[j] = vetor[j-1];
        }
        vetor[j] = temp;
    }
    return 0;
}

int selectionSort(int *vetor, int tam)
{
    int i, j, temp, min, min_id = 0;

    for(i = 0; i < tam - 1; i++)
    {
        min = vetor[i];

        for(j = i + 1; j < tam; j++)
        {
            if(vetor[j] < min)
            {
                min = vetor[j];
                min_id = j;
            }
        }


        if (i != min_id)
        {
            temp = vetor[i];
            vetor[i] = vetor[min_id];
            vetor[min_id] = temp;
            min_id = i + 1;
        }
    }
    return 0;
}

int quickSort(int *vetor, int esquerda, int direita)
{
    int meio, temp, i, j;
    i = esquerda;
    j = direita;
    meio = vetor[(esquerda + direita)/2];

    do
    {
        while(vetor[i] < meio)
        {
            i++;
        }

        while(meio < vetor[j])
        {
            j--;
        }
        
        if(i <= j)
        {
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
        }

    } while (i <= j);
    if (esquerda < j)
    {
        quickSort(vetor, esquerda,j);
    }
    if(i < direita)
    {
        quickSort(vetor, i, direita);
    }
    return 0;
}

int merge (int * vetor, int esquerda, int meio, int direita) 
{
    int i, j, k, tam, *temp, p1, p2;
    int fim1=0, fim2=0;

    tam = direita - esquerda + 1;

    p1 = esquerda;
    p2 = meio + 1;
    temp = (int *)malloc(sizeof(int) * tam);
    if(temp != NULL) 
    {
    
        for(i = 0; i < tam; i++) // testa qual o maior elemento para cada posição de cada vetor
        {
            if(!fim1 && !fim2) 
            {
                if(vetor[p1] < vetor[p2]) 
                {
                    temp[i] = vetor[p1++];
                }
                
                else 
                {
                    temp[i] = vetor[p2++];
                }

                if(p1 > meio) //se chegou no fim de algum dos vetores
                {
                    fim1 = 1;
                }
                if(p2 > direita) 
                {
                    fim2 = 1;
                }
            } else 
            { 
                
                if(!fim1) //coloca o resto no fim do vetor
                {
                    temp[i] = vetor[p1++];
                } 
                
                else 
                {
                    temp[i] = vetor[p2++];
                }
            }
        }
        
        for(j = 0, k = esquerda; j < tam; j++, k++) //passa o vetor temporario para o principal, já ordenado
        {
            vetor[k] = temp[j];
        }
    }
    free(temp);
    return 0;
}
int mergeSort (int *vetor, int esquerda, int direita) 
{
    int meio;
    if (esquerda < direita) 
    {
        meio = (esquerda + direita) / 2;
        mergeSort(vetor, esquerda, meio);
        mergeSort(vetor, meio + 1, direita);
        merge(vetor, esquerda, meio, direita);
    }
    
    return 0;
}

int main ()
{
    srand(time(NULL));
    struct timeval begin, end;
    float tempExec, mediaInsert=0, mediaSelection=0, mediaQuick=0, mediaMerge=0;
    int tam=0, i=0, j=0, opmenu=1;
    int *vetor = malloc(sizeof(int));

    while(opmenu != 0)
    {
        opmenu=mainMenu();

        printf("\n##Digite o tamanho do vetor: ");
        scanf("%i", &tam);
        vetor = realloc(vetor, sizeof(int)*tam);
        
        for(i=0; i<tam; i++)
        {
            vetor[i] = rand()%1000;
        } 
        printf("\n##Vetor a ser ordenado:\n");
        imprimeVetor(vetor, tam);
            
        switch(opmenu)
        {
            case 1:
                gettimeofday(&begin, 0);
                insertionSort(vetor, tam);
                gettimeofday(&end, 0);

                tempExec=(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6;

                test(vetor, tam - 1);

                printf("\nInsertion sort aplicado! Tempo de execucao: %.10f", tempExec);
                imprimeVetor(vetor, tam);
                break;

            case 2:
                gettimeofday(&begin, 0);
                selectionSort(vetor, tam);
                gettimeofday(&end, 0);

                tempExec=(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6;

                test(vetor, tam - 1);

                printf("\nSelection sort aplicado! Tempo de execucao: %.10f", tempExec);
                imprimeVetor(vetor, tam);
                break;
            case 3:

                gettimeofday(&begin, 0);
                quickSort(vetor, 0, tam - 1);
                gettimeofday(&end, 0);

                tempExec=(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6;

                test(vetor, tam - 1);

                printf("\nQuick sort aplicado! Tempo de execucao: %.10f", tempExec);
                imprimeVetor(vetor, tam);

                break;
            case 4:
                gettimeofday(&begin, 0);
                mergeSort(vetor, 0,  tam -1);
                gettimeofday(&end, 0);

                tempExec=(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6;

                test(vetor, tam - 1);

                printf("\nMerge sort aplicado! Tempo de execucao: %.10f", tempExec);
                imprimeVetor(vetor, tam);
            
                break;

            case 5:
                //BATERIA DE TESTES
                for(i=0; i<3; i++)
                {
                   for(j=0; j<tam; j++)
                    {
                        vetor[j] = rand()%1000;
                    }  
                    gettimeofday(&begin, 0);
                    insertionSort(vetor, tam);
                    gettimeofday(&end, 0);

                    tempExec=(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6;

                    test(vetor, tam - 1);

                    printf("\nInsertion sort aplicado! Tempo de execucao: %.10f", tempExec);
                    imprimeVetor(vetor, tam);
                    mediaInsert+=tempExec;
                }
                mediaInsert=mediaInsert/3;

                for(i=0; i<3; i++)
                {
                    for(j=0; j<tam; j++)
                    {
                        vetor[j] = rand()%1000;
                    } 
                    gettimeofday(&begin, 0);
                    selectionSort(vetor, tam);
                    gettimeofday(&end, 0);

                    tempExec=(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6;

                    test(vetor, tam - 1);

                    printf("\nSelection sort aplicado! Tempo de execucao: %.10f", tempExec);
                    imprimeVetor(vetor, tam);
                    mediaSelection+=tempExec;
                }

                mediaSelection=mediaSelection/3;
                
                for(i=0; i<3; i++)
                {
                    for(j=0; j<tam; j++)
                    {
                        vetor[j] = rand()%1000;
                    } 
                    gettimeofday(&begin, 0);
                    quickSort(vetor, 0, tam - 1);
                    gettimeofday(&end, 0);

                    tempExec=(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6;

                    test(vetor, tam - 1);

                    printf("\nQuick sort aplicado! Tempo de execucao: %.20f", tempExec);
                    imprimeVetor(vetor, tam);
                    mediaQuick+=tempExec;
                }
                mediaQuick=mediaQuick/3;


                for(i=0; i<3; i++)
                {
                    for(j=0; j<tam; j++)
                    {
                        vetor[j] = rand()%1000;
                    } 
                    gettimeofday(&begin, 0);
                    mergeSort(vetor, 0,  tam -1);
                    gettimeofday(&end, 0);

                    tempExec=(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6;

                    test(vetor, tam - 1);

                    printf("\nMerge sort aplicado! Tempo de execucao: %.10f", tempExec);
                    imprimeVetor(vetor, tam);
                    mediaMerge+=tempExec;
                }
                mediaMerge=mediaMerge/3;

                printf("\n\nMedia Insertion sort: %.10f\nMedia Selection sort: %.10f\nMedia Quick sort: %.10f\nMedia Merge sort: %.10f\n", mediaInsert, mediaSelection, mediaQuick, mediaMerge);
                
                break;
                
            default:
                printf("\n Número inválido");
                opmenu = 0;
                break;
        }

        do
        {
            printf("\n##Deseja reiniciar o programa?\n");
            printf("## 1 - Sim\n");
            printf("## 0 - Nao\n");
            scanf("%i", &opmenu);
        } while (opmenu != 0 && opmenu != 1);
    }
    free(vetor);
    return 0;
}