
# Comparação de Estruturas de Dados: AVL, BST e Tabela Hash

## 📌 Descrição

Este projeto tem como objetivo **comparar o desempenho das operações de inserção e busca** em três estruturas de dados:

- 🔵 **Árvore AVL** (balanceada automaticamente)
- 🔴 **Árvore Binária de Busca (BST)** (não balanceada)
- 🟢 **Tabela Hash** com **encadeamento separado**

Cada estrutura foi implementada em **linguagem C** e submetida a testes com diferentes tamanhos de entrada (de 100 até 10.000 elementos).  
As operações foram repetidas 100 vezes por configuração para suavizar variações no tempo de execução.

---

## 📂 Estrutura dos Arquivos

Os tempos foram salvos em arquivos `.txt`, organizados da seguinte forma:

| Arquivo             | Descrição                                 |
|---------------------|--------------------------------------------|
| `insert_avl.txt`    | Tempo médio de inserção na AVL             |
| `search_avl.txt`    | Tempo médio de busca na AVL                |
| `insert_bst.txt`    | Tempo médio de inserção na BST             |
| `search_bst.txt`    | Tempo médio de busca na BST                |
| `insert_hash.txt`   | Tempo médio de inserção na Tabela Hash     |
| `search_hash.txt`   | Tempo médio de busca na Tabela Hash        |

Cada linha dos arquivos segue o formato:

```csv
n,tempo_em_nanosegundos
```

- `n`: número de elementos inseridos  
- `tempo_em_nanosegundos`: tempo médio por operação (inserção ou busca)

---

## ⚙️ Como compilar e executar

### Pré-requisitos

- GCC (compilador C)
- Sistema operacional compatível com `clock()` (Linux, Windows, etc.)

### Executar

Para **medir inserção**, defina no código:

```c
#define MEDIR_INSERCAO 1
#define MEDIR_BUSCA 0
```

Para **medir busca**, altere para:

```c
#define MEDIR_INSERCAO 0
#define MEDIR_BUSCA 1
```

### Compilar

```bash
gcc avl.c -o avl.exe
gcc bst.c -o bst.exe
gcc hash.c -o hash.exe
```

Em seguida, execute os programas:

```bash
./avl.exe
./bst.exe
./hash.exe
```

---

## 📊 Visualização dos Resultados

Os arquivos `.txt` gerados podem ser visualizados usando:

- **Gnuplot** (script incluso)
- **Excel** ou **Google Sheets**
- Scripts em **Python** ou **R**

### Exemplo com Gnuplot

```bash
gnuplot script.gnuplot
```

O script irá gerar gráficos `.png` com comparações de desempenho entre as estruturas.

---

## 📈 Resultados Esperados

- 🟢 **Tabela Hash**: desempenho praticamente constante `O(1)`
- 🔵 **AVL**: desempenho estável e eficiente `O(log n)`
- 🔴 **BST**: eficiente apenas com dados aleatórios; degrada para `O(n)` com dados ordenados

---

## 🧪 Observações

> ⚠️ Os testes **não foram realizados em ambiente controlado**.  
> Eles foram executados em um sistema operacional comum (Windows), sujeito a variações de carga e interferências de processos paralelos.  
> Portanto, os tempos médios devem ser analisados como tendências, não como valores absolutos.
