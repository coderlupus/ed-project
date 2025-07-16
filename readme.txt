# Comparação de Estruturas de Dados: AVL, BST e Tabela Hash

## Descrição

Este projeto mede e compara o desempenho das operações de **inserção** e **busca** em três estruturas de dados diferentes:

- Árvore AVL (árvore binária balanceada)
- Árvore Binária de Busca (BST)
- Tabela Hash com encadeamento separado

Para cada estrutura, o código executa múltiplas repetições de inserções e buscas, medindo o tempo médio em nanosegundos.  
Os resultados são salvos em arquivos `.txt` para análise e visualização posterior.

---

## Estrutura dos arquivos

| Arquivo            | Conteúdo                             |
|--------------------|------------------------------------|
| `insert_avl.txt`   | Tempo médio de inserção na AVL      |
| `search_avl.txt`   | Tempo médio de busca na AVL         |
| `insert_bst.txt`   | Tempo médio de inserção na BST      |
| `search_bst.txt`   | Tempo médio de busca na BST         |
| `insert_hash.txt`  | Tempo médio de inserção na Hash     |
| `search_hash.txt`  | Tempo médio de busca na Hash        |

Cada arquivo contém dados no formato:

n,tempo_em_nanosegundos

onde:

- `n` = número de elementos
- `tempo_em_nanosegundos` = tempo médio da operação

---

## Como compilar e rodar

### Compilar

```bash
gcc avl.c -o avl.exe
gcc bst.c -o bst.exe
gcc hash.c -o hash.exe
