#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 10000
#define STEP 100
#define REPETICOES 100

#define MEDIR_BUSCA 0
#define MEDIR_INSERCAO 1

#define HASH_SIZE 20011  // Um número primo grande pra evitar colisões

typedef struct node
{
    int value;
    struct node *next;
} Node;

int hash_function(int key)
{
    return key % HASH_SIZE;
}

void insert(Node **table, int value)
{
    int index = hash_function(value);
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = table[index];
    table[index] = new_node;
}

Node *search(Node **table, int target)
{
    int index = hash_function(target);
    Node *current = table[index];
    while (current)
    {
        if (current->value == target)
            return current;
        current = current->next;
    }
    return NULL;
}

void free_table(Node **table)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        Node *current = table[i];
        while (current)
        {
            Node *tmp = current;
            current = current->next;
            free(tmp);
        }
    }
}

int main()
{
    srand(42);

    const int BUSCAS_POR_REPETICAO = 1000;

#if MEDIR_BUSCA
    FILE *fp_search = fopen("search_hash.txt", "w");
    if (!fp_search)
    {
        perror("Erro ao abrir arquivo de busca");
        return 1;
    }

    for (int n = STEP; n <= MAX_N; n += STEP)
    {
        double total_search_time = 0;

        for (int rep = 0; rep < REPETICOES; rep++)
        {
            Node *table[HASH_SIZE] = {0};

            for (int i = 0; i < n; i++)
            {
                int numberInsert = rand() % (n * 10);
                insert(table, numberInsert);
            }

            clock_t t_start = clock();

            for (int k = 0; k < BUSCAS_POR_REPETICAO; k++)
            {
                int numberSearch = rand() % (n * 10);
                search(table, numberSearch);
            }

            clock_t t_end = clock();

            total_search_time += ((double)(t_end - t_start) / CLOCKS_PER_SEC) * 1e9 / BUSCAS_POR_REPETICAO;

            free_table(table);
        }

        long avg_search_time = (long)(total_search_time / REPETICOES);
        fprintf(fp_search, "%d,%ld\n", n, avg_search_time);
        fflush(fp_search);
        printf("n=%d busca=%ld ns\n", n, avg_search_time);
    }

    fclose(fp_search);
#endif

#if MEDIR_INSERCAO
    FILE *fp_insert = fopen("insert_hash.txt", "w");
    if (!fp_insert)
    {
        perror("Erro ao abrir arquivo de insercao");
        return 1;
    }

    for (int n = STEP; n <= MAX_N; n += STEP)
    {
        double total_insert_time = 0;

        for (int rep = 0; rep < REPETICOES; rep++)
        {
            Node *table[HASH_SIZE] = {0};

            clock_t t_start = clock();

            for (int i = 0; i < n; i++)
            {
                int numberInsert = rand() % (n * 10);
                insert(table, numberInsert);
            }

            clock_t t_end = clock();

            total_insert_time += ((double)(t_end - t_start) / CLOCKS_PER_SEC) * 1e9;

            free_table(table);
        }

        long avg_insert_time = (long)(total_insert_time / REPETICOES);
        fprintf(fp_insert, "%d,%ld\n", n, avg_insert_time);
        fflush(fp_insert);
        printf("n=%d insercao=%ld ns\n", n, avg_insert_time);
    }

    fclose(fp_insert);
#endif

    return 0;
}
