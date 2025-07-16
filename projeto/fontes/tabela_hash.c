#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 200003

typedef struct Node
{
    int valor;
    struct Node *prox;
} Node;

Node *tabela[TAM];

void inserir(int valor)
{
    int idx = valor % TAM;
    Node *novo = malloc(sizeof(Node));
    novo->valor = valor;
    novo->prox = tabela[idx];
    tabela[idx] = novo;
}

int buscar(int valor)
{
    int idx = valor % TAM;
    Node *atual = tabela[idx];
    while (atual)
    {
        if (atual->valor == valor)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

// Gera vetor de chaves aleatórias
void gerar_aleatorio(int *vet, int n) {
    for (int i = 0; i < n; i++) vet[i] = rand();
}

// Busca melhor caso: chave está logo no início da lista (primeira inserida)
int buscar_melhor(int *vet) {
    return buscar(vet[0]);
}

// Busca pior caso: chave que não existe
int buscar_pior() {
    return buscar(-1);
}

// Busca médio caso: chave aleatória do vetor
int buscar_medio(int *vet, int n) {
    int idx = rand() % n;
    return buscar(vet[idx]);
}

int main()
{
    int N[] = {10000, 50000, 100000};
    FILE *f = fopen("graficos/tempos_hash.dat", "w");

    for (int i = 0; i < 3; i++)
    {
        srand(42);
        for (int j = 0; j < TAM; j++)
            tabela[j] = NULL;

        int *vet = malloc(N[i] * sizeof(int));
        gerar_aleatorio(vet, N[i]);

        for (int j = 0; j < N[i]; j++)
            inserir(vet[j]);

        int repeticoes = 10000000;

        // Escolha o cenário de busca:
        clock_t ini = clock();
        for (int k = 0; k < repeticoes; k++)
        {
            // buscar_melhor(vet);
            // buscar_pior();
            buscar_medio(vet, N[i]);
        }
        clock_t fim = clock();

        double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;

        fprintf(f, "%d\t%lf\n", N[i], tempo);
        printf("HASH: N=%d Tempo=%lf\n", N[i], tempo);

        free(vet);
    }
    fclose(f);
    return 0;
}
