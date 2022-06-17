
## Trabalho 01:<p>
O código em assembly simula o seguinte código em C:<p>

```
int i;
int vetor[8];
for(i=0; i<8; i++) {
    if(i%2==0)
    vetor[i] = i * 2;
    else
    vetor[i] = vetor[i] + vetor[i-1];   
}
```

Cada posição do vetor tem 4 bytes e foi armazenado, em sequência, a
partir da posição 0x1001000 da memória.

## Trabalho 02:<p>
Este programa calcula a mediana entre três valores lidos diretamente da memória. O número adquirido através da mediana é salvo na posição 0x1001000C da memória.