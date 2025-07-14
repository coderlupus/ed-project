#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int valor, altura;
    struct Node *esq, *dir;
} Node;

int altura(Node *n)
{
    return n ? n->altura : 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

Node *rot_dir(Node *y)
{
    Node *x = y->esq;
    Node *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    return x;
}

Node *rot_esq(Node *x)
{
    Node *y = x->dir;
    Node *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

int get_balance(Node *n)
{
    return n ? altura(n->esq) - altura(n->dir) : 0;
}

Node *inserir(Node *node, int valor)
{
    if (!node)
    {
        Node *novo = malloc(sizeof(Node));
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    if (valor < node->valor)
        node->esq = inserir(node->esq, valor);
    else if (valor > node->valor)
        node->dir = inserir(node->dir, valor);
    else
        return node;

    node->altura = 1 + max(altura(node->esq), altura(node->dir));
    int balance = get_balance(node);

    if (balance > 1 && valor < node->esq->valor)
        return rot_dir(node);

    if (balance < -1 && valor > node->dir->valor)
        return rot_esq(node);

    if (balance > 1 && valor > node->esq->valor)
    {
        node->esq = rot_esq(node->esq);
        return rot_dir(node);
    }

    if (balance < -1 && valor < node->dir->valor)
    {
        node->dir = rot_dir(node->dir);
        return rot_esq(node);
    }

    return node;
}

int buscar(Node *raiz, int valor)
{
    if (raiz == NULL)
        return 0;
    if (raiz->valor == valor)
        return 1;
    if (valor < raiz->valor)
        return buscar(raiz->esq, valor);
    else
        return buscar(raiz->dir, valor);
}

int main()
{
    Node *raiz = NULL;
    int N[] = {10000, 50000, 100000};
    FILE *f = fopen("graficos/tempos_avl.dat", "w");

    for (int i = 0; i < 3; i++)
    {
        srand(42);
        raiz = NULL;

        for (int j = 0; j < N[i]; j++)
            raiz = inserir(raiz, rand());

        srand(time(NULL));
        int chave = rand();

        int repeticoes = 10000000; 

        clock_t ini = clock();
        for (int k = 0; k < repeticoes; k++)
        {
            buscar(raiz, chave);
        }
        clock_t fim = clock();

        double tempo = (double)(fim - ini) / CLOCKS_PER_SEC; // tempo total

        fprintf(f, "%d\t%lf\n", N[i], tempo);
        printf("AVL: N=%d Tempo=%lf\n", N[i], tempo);
    }
    fclose(f);
    return 0;
}
