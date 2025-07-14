# Makefile para compilar todos os arquivos C

# Compilador
CC = gcc

# Flags de compilação (pode adicionar -O2 se quiser otimizar)
CFLAGS = 

# Executáveis
EXE_BINARIA = arvore_binaria.exe
EXE_AVL = arvore_avl.exe
EXE_HASH = tabela_hash.exe

# Fontes
SRC_BINARIA = fontes/arvore_binaria.c
SRC_AVL = fontes/arvore_avl.c
SRC_HASH = fontes/tabela_hash.c

all: $(EXE_BINARIA) $(EXE_AVL) $(EXE_HASH)

$(EXE_BINARIA): $(SRC_BINARIA)
	$(CC) $(CFLAGS) $(SRC_BINARIA) -o $(EXE_BINARIA)

$(EXE_AVL): $(SRC_AVL)
	$(CC) $(CFLAGS) $(SRC_AVL) -o $(EXE_AVL)

$(EXE_HASH): $(SRC_HASH)
	$(CC) $(CFLAGS) $(SRC_HASH) -o $(EXE_HASH)

clean:
	del /Q *.exe
