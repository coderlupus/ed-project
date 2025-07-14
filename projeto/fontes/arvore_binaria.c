#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int valor;
    struct Node *esq, *dir;
} Node;

Node* inserir(Node* raiz, int valor) {
    if (raiz == NULL) {
        Node* novo = malloc(sizeof(Node));
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

int buscar(Node* raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;
    if (valor < raiz->valor)
        return buscar(raiz->esq, valor);
    else
        return buscar(raiz->dir, valor);
}

int main() {
    Node* raiz = NULL;
    int N[] = {10000, 50000, 100000};
    FILE* f = fopen("graficos/tempos_binaria.dat", "w");

    for (int i = 0; i < 3; i++) {
        srand(42);
        raiz = NULL;

        for (int j = 0; j < N[i]; j++)
            raiz = inserir(raiz, rand());

        srand(time(NULL));
        int chave = rand();

        clock_t ini = clock();
        buscar(raiz, chave);
        clock_t fim = clock();

        double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
        fprintf(f, "%d\t%lf\n", N[i], tempo);
        printf("BST: N=%d Tempo=%lf\n", N[i], tempo);
    }
    fclose(f);
    return 0;
}
