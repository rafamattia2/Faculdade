# Trabalho 1: AGENDA
Nome: Rafael de Mattia || Matrícula 20200744 || E-mail: rdmattia@inf.ufpel.edu.br
Link para repositório no GitHub: 
---
## Estrutura de arquivos: 

```
Trabalho01
| - README.md
| - trabalho01.c
| - results.txt

```

- Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte.

    1. Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.

        1. Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
        2. Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
    2. Não pode usar struct em todo o programa.
    3. Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.  
    4. Implementar a base de dados da agenda usando lista duplamente ligada
        1. Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.
- Seguir as orientações elaborados pelo monitor para código!
- Entregar um vídeo explicando o código e mostrando alguns testes e ao final o resultado do DrMemory.

----

