#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#define espaco 5
struct Node
{
    int contents;
    struct Node *left;
    struct Node *right;
    int height;
};
 
int max(int a, int b);
 
int calcHeight(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int max(int a, int b)
{
    return (a > b)? a : b;
}

struct Node* newNode(int value)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->contents   = value;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(calcHeight(y->left), calcHeight(y->right))+1;
    x->height = max(calcHeight(x->left), calcHeight(x->right))+1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(calcHeight(x->left), calcHeight(x->right))+1;
    y->height = max(calcHeight(y->left), calcHeight(y->right))+1;
 
    return y;
}
 
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return calcHeight(N->left) - calcHeight(N->right);
}
 
struct Node* insert(struct Node* node, int value)
{
    if (node == NULL)
        return(newNode(value));
 
    if (value < node->contents)
        node->left  = insert(node->left, value);
    else if (value > node->contents)
        node->right = insert(node->right, value);
    else
        return node;
 
    node->height = 1+max(calcHeight(node->left), calcHeight(node->right));
 
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && value < node->left->contents)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && value > node->right->contents)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && value > node->left->contents)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && value < node->right->contents)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
struct Node* deleteNode(struct Node* root, int deleteValue)
{
    if (root == NULL)
        return root;

    if ( deleteValue < root->contents )
        root->left = deleteNode(root->left, deleteValue);

    else if( deleteValue > root->contents )
        root->right = deleteNode(root->right, deleteValue);
 
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;
 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp; 
                            
            free(temp);
        }
        else
        {
            struct Node* temp = minValueNode(root->right);

            root->contents = temp->contents;
 
            root->right = deleteNode(root->right, temp->contents);
        }
    }
 
    if (root == NULL)
      return root;
 
    root->height = 1 + max(calcHeight(root->left),
                           calcHeight(root->right));
 
    int balance = getBalance(root);

 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

int treePrinter(struct Node * root)
{
    if(root!=NULL)
    {
        
        printf("%d ", root->contents);
        treePrinter(root->left);
        treePrinter(root->right);
    }
}

int verifyAVLTree(struct Node* root)
{
    int fb;
    if (root == NULL)
        return 1;
    if (!verifyAVLTree(root->left))
        return 0;
    if(!verifyAVLTree(root->right))
        return 0;
    fb = getBalance(root);

    if((fb>1) || (fb < -1))
        return 0;
    else
        return 1;
}

int findAndPrint(struct Node *root, int value)
{
    if(root != NULL)
    {
        do
        {
        if(value < root->contents)
        {
            root=root->left;
        }
        if(value > root->contents)
        {
            root=root->right;
        }
        } while (value != root->contents);

        treePrinter(root);
    }
    else
        return 0;
}

void desenha_arvore_horiz(struct Node *root, int depth, char *path, int direita)
{
    // stopping condition
    if (root== NULL)
        return;

    // increase spacing
    depth++;

    // start with direita no
    desenha_arvore_horiz(root->right, depth, path, 1);

    // set | draw map
    path[depth-2] = 0;

    if(direita)
        path[depth-2] = 1;

    if(root->left)
        path[depth-1] = 1;

    // print root after spacing
    printf("\n");

    for(int i=0; i<depth-1; i++)
    {
      if(i == depth-2)
          printf("+");
      else if(path[i])
          printf("|");
      else
          printf(" ");

      for(int j=1; j<espaco; j++)
      if(i < depth-2)
          printf(" ");
      else
          printf("-");
    }

    printf("%d\n", root->contents);

    // vertical espacors below
    for(int i=0; i<depth; i++)
    {
      if(path[i])
          printf("|");
      else
          printf(" ");

      for(int j=1; j<espaco; j++)
          printf(" ");
    }

    // go to esquerda no
    desenha_arvore_horiz(root->left, depth, path, 0);
}

void treePrinter2(struct Node *arvore)
{
    // should check if we don't exceed this somehow..
    char path[255] = {};

    //initial depth is 0
    desenha_arvore_horiz(arvore, 0, path, 0);
}
int main ()
{
    
    int op, opmax, value, i, test;
    struct Node *root = NULL;
    srand(time(0));
    do
    {
        printf("\nEscolha uma opcao!\n-----------------");
        printf("\n0-Sair\n");
        printf("1-Inserir elemento\n");
        printf("2-Imprimir arvore\n");
        printf("3-Deletar um elemento\n");
        printf("4-Executar primeiro cenario\n");
        printf("5-Procurar um nodo de imprimir os subsequentes\n");
        scanf("%d", &op);

        switch (op)
        {
        case 0:
            break;

        case 1:
            printf("\nDigite o elemento que deseja adicionar: ");
            scanf("%d", &value);
            root = insert(root, value);
            break;
        
        case 2:
            treePrinter(root);
            printf("\n\n\n");
            treePrinter2(root);
            break; 
        
        case 3:
            printf("\nDigite o elemento que deseja remover: ");
            scanf ("%d", &value);
            root = deleteNode(root, value);
            break;

        case 4:
            printf("\nQuantos elementos deseja adicionar?\n");
            scanf("%d", &opmax);
            

            for (i=0; i<opmax; i++)
            {
                value=rand()%10000;
                root = insert(root, value);
            }

            test = verifyAVLTree(root);
            if(test =  1)
                printf("A arvore eh AVL");
            else
                printf("A arvore nao eh AVL");
            break;

        case 5:
            printf("\nQual o nodo que deseja procurar?\n");
            scanf("%d", &value);
            
            findAndPrint(root, value);
            break;

        default:
            break;
        }
    } while (op != 0);
}