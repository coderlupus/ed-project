#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int valor;
    struct Node *esq, *dir;
} Node;

Node *inserir(Node *raiz, int valor)
{
    if (raiz == NULL)
    {
        Node *novo = malloc(sizeof(Node));
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

// Gera vetor crescente
void gerar_crescente(int *vet, int n) {
    for (int i = 0; i < n; i++) vet[i] = i;
}

// Gera vetor decrescente
void gerar_decrescente(int *vet, int n) {
    for (int i = 0; i < n; i++) vet[i] = n - i;
}

// Gera vetor aleatório
void gerar_aleatorio(int *vet, int n) {
    for (int i = 0; i < n; i++) vet[i] = rand();
}

// Busca melhor caso (raiz)
int buscar_melhor(Node *raiz) {
    return buscar(raiz, raiz->valor);
}

// Busca pior caso (valor inexistente)
int buscar_pior(Node *raiz) {
    return buscar(raiz, -1);
}

// Busca médio caso (valor aleatório)
int buscar_medio(Node *raiz, int *vet, int n) {
    int idx = rand() % n;
    return buscar(raiz, vet[idx]);
}

int main()
{
    Node *raiz = NULL;
    int N[] = {10000, 50000, 100000};
    FILE *f = fopen("graficos/tempos_binaria.dat", "w");

    for (int i = 0; i < 3; i++)
    {
        int *vet = malloc(N[i] * sizeof(int));
        // Escolha o cenário de inserção:
        // gerar_crescente(vet, N[i]);
        // gerar_decrescente(vet, N[i]);
        gerar_aleatorio(vet, N[i]);

        raiz = NULL;
        for (int j = 0; j < N[i]; j++)
            raiz = inserir(raiz, vet[j]);

        int repeticoes = 100000;

        // Escolha o cenário de busca:
        clock_t ini = clock();
        for (int k = 0; k < repeticoes; k++)
        {
            // buscar_melhor(raiz);
            // buscar_pior(raiz);
            buscar_medio(raiz, vet, N[i]);
        }
        clock_t fim = clock();

        double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
        fprintf(f, "%d\t%lf\n", N[i], tempo);
        printf("BST: N=%d Tempo=%lf\n", N[i], tempo);

        free(vet);
    }
    fclose(f);
    return 0;
}
