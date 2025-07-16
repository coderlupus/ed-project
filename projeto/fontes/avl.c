#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 10000
#define STEP 100
#define REPETICOES 100

#define MEDIR_BUSCA 0
#define MEDIR_INSERCAO 1

typedef struct node
{
    int value;
    struct node *left, *right, *parent;
    int height;
} Node;

Node *initialize_node(int node)
{
    Node *w = (Node *)malloc(sizeof(Node));
    w->value = node;
    w->left = NULL;
    w->right = NULL;
    w->height = 0;
    return w;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void rLeft(Node **A)
{
    Node *x = (*A);
    Node *y = (*A)->right;

    x->right = y->left;
    if (x->right != NULL)
        x->right->parent = x;

    y->left = x;
    y->parent = x->parent;
    x->parent = y;

    int x_leftH = (x->left) ? x->left->height : -1;
    int x_rightH = (x->right) ? x->right->height : -1;
    x->height = max(x_leftH, x_rightH) + 1;

    int y_leftH = (y->left) ? y->left->height : -1;
    int y_rightH = (y->right) ? y->right->height : -1;
    y->height = max(y_leftH, y_rightH) + 1;

    if (y->parent == NULL)
        (*A) = y;
}

void rRight(Node **A)
{
    Node *x = (*A);
    Node *y = x->left;

    x->left = y->right;
    if (x->left != NULL)
        x->left->parent = x;

    y->right = x;
    y->parent = x->parent;
    x->parent = y;

    int x_leftH = (x->left) ? x->left->height : -1;
    int x_rightH = (x->right) ? x->right->height : -1;
    x->height = max(x_leftH, x_rightH) + 1;

    int y_leftH = (y->left) ? y->left->height : -1;
    int y_rightH = (y->right) ? y->right->height : -1;
    y->height = max(y_leftH, y_rightH) + 1;

    if (y->parent == NULL)
        (*A) = y;
}

void update(Node **A)
{
    int leftH = ((*A)->left) ? (*A)->left->height : -1;
    int rightH = ((*A)->right) ? (*A)->right->height : -1;
    int fatorB = leftH - rightH;

    (*A)->height = max(leftH, rightH) + 1;

    if (fatorB > 1)
    {
        int childFB = ((*A)->left)
                          ? (((*A)->left->left ? (*A)->left->left->height : -1) -
                             ((*A)->left->right ? (*A)->left->right->height : -1))
                          : 0;

        if (childFB >= 0)
        {
            rRight(A);
        }
        else
        {
            rLeft(&(*A)->left);
            rRight(A);
        }
    }
    else if (fatorB < -1)
    {
        int childFB = ((*A)->right)
                          ? (((*A)->right->left ? (*A)->right->left->height : -1) -
                             ((*A)->right->right ? (*A)->right->right->height : -1))
                          : 0;

        if (childFB <= 0)
        {
            rLeft(A);
        }
        else
        {
            rRight(&(*A)->right);
            rLeft(A);
        }
    }
}

void insert(Node **A, Node *w, Node *parent)
{
    if ((*A) != NULL)
    {
        if ((*A)->value >= w->value)
            insert(&((*A)->left), w, (*A));
        else
            insert(&((*A)->right), w, (*A));
        update(A);
    }
    else
    {
        w->parent = parent;
        (*A) = w;
    }
}

Node *search(Node *A, int target)
{
    if (A == NULL)
        return NULL;
    if (A->value == target)
        return A;
    if (target < A->value)
        return search(A->left, target);
    else
        return search(A->right, target);
}

void free_tree(Node *root)
{
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main()
{
    srand(42);

    const int BUSCAS_POR_REPETICAO = 1000;

#if MEDIR_BUSCA
    FILE *fp_search = fopen("search_avl.txt", "w");
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
            Node *head = NULL;

            for (int i = 0; i < n; i++)
            {
                int numberInsert = rand() % (n * 10);
                Node *node = initialize_node(numberInsert);
                insert(&head, node, NULL);
            }

            clock_t t_start = clock();

            for (int k = 0; k < BUSCAS_POR_REPETICAO; k++)
            {
                int numberSearch = rand() % (n * 10);
                search(head, numberSearch);
            }

            clock_t t_end = clock();

            total_search_time += ((double)(t_end - t_start) / CLOCKS_PER_SEC) * 1e9 / BUSCAS_POR_REPETICAO;

            free_tree(head);
        }

        long avg_search_time = (long)(total_search_time / REPETICOES);
        fprintf(fp_search, "%d,%ld\n", n, avg_search_time);
        fflush(fp_search);
        printf("n=%d busca=%ld ns\n", n, avg_search_time);
    }

    fclose(fp_search);
#endif

#if MEDIR_INSERCAO
    FILE *fp_insert = fopen("insert_avl.txt", "w");
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
            Node *head = NULL;

            clock_t t_start = clock();

            for (int i = 0; i < n; i++)
            {
                int numberInsert = rand() % (n * 10);
                Node *node = initialize_node(numberInsert);
                insert(&head, node, NULL);
            }

            clock_t t_end = clock();

            total_insert_time += ((double)(t_end - t_start) / CLOCKS_PER_SEC) * 1e9;

            free_tree(head);
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
