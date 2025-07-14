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

int main()
{
    int N[] = {10000, 50000, 100000};
    FILE *f = fopen("graficos/tempos_hash.dat", "w");

    for (int i = 0; i < 3; i++)
    {
        srand(42);
        for (int j = 0; j < TAM; j++)
            tabela[j] = NULL;

        for (int j = 0; j < N[i]; j++)
            inserir(rand());

        srand(time(NULL));
        int chave = rand();

        int repeticoes = 10000000; 

        clock_t ini = clock();
        for (int k = 0; k < repeticoes; k++)
        {
            buscar(chave);
        }
        clock_t fim = clock();

        double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;

        fprintf(f, "%d\t%lf\n", N[i], tempo);
        printf("HASH: N=%d Tempo=%lf\n", N[i], tempo);
    }
    fclose(f);
    return 0;
}
