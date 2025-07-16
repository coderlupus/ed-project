# Saída com boa qualidade
set datafile separator ","
set terminal pngcairo size 1200,800 enhanced font 'Verdana,12'
set grid
set xlabel "Número de elementos (n)"
set ylabel "Tempo médio (ns)"
set key outside

# 1️⃣ GERAL - TODOS JUNTOS (inserção e busca misturados)
set output "comparacao_geral.png"
set title "Inserção e Busca - AVL, BST, Hash (Tudo Junto)"
plot \
    "insert_avl.txt" using 1:2 with linespoints lt 1 lc rgb "blue" title "AVL Insert", \
    "search_avl.txt" using 1:2 with linespoints lt 1 lc rgb "blue" dt 2 title "AVL Search", \
    "insert_bst.txt" using 1:2 with linespoints lt 1 lc rgb "red" title "BST Insert", \
    "search_bst.txt" using 1:2 with linespoints lt 1 lc rgb "red" dt 2 title "BST Search", \
    "insert_hash.txt" using 1:2 with linespoints lt 1 lc rgb "green" title "Hash Insert", \
    "search_hash.txt" using 1:2 with linespoints lt 1 lc rgb "green" dt 2 title "Hash Search"

# 2️⃣ INSERÇÃO - COMPARANDO ESTRUTURAS
set output "insercao_todas.png"
set title "Comparação de Inserção - AVL, BST, Hash"
plot \
    "insert_avl.txt" using 1:2 with linespoints lt 1 lc rgb "blue" title "AVL Insert", \
    "insert_bst.txt" using 1:2 with linespoints lt 1 lc rgb "red" title "BST Insert", \
    "insert_hash.txt" using 1:2 with linespoints lt 1 lc rgb "green" title "Hash Insert"

# 3️⃣ BUSCA - COMPARANDO ESTRUTURAS
set output "busca_todas.png"
set title "Comparação de Busca - AVL, BST, Hash"
plot \
    "search_avl.txt" using 1:2 with linespoints lt 1 lc rgb "blue" title "AVL Search", \
    "search_bst.txt" using 1:2 with linespoints lt 1 lc rgb "red" title "BST Search", \
    "search_hash.txt" using 1:2 with linespoints lt 1 lc rgb "green" title "Hash Search"

# 4️⃣ INSERÇÃO INDIVIDUAL
set title "Inserção AVL"
set output "insercao_avl.png"
plot "insert_avl.txt" using 1:2 with linespoints lt 1 lc rgb "blue" title "AVL Insert"

set title "Inserção BST"
set output "insercao_bst.png"
plot "insert_bst.txt" using 1:2 with linespoints lt 1 lc rgb "red" title "BST Insert"

set title "Inserção Hash"
set output "insercao_hash.png"
plot "insert_hash.txt" using 1:2 with linespoints lt 1 lc rgb "green" title "Hash Insert"

# 5️⃣ BUSCA INDIVIDUAL
set title "Busca AVL"
set output "busca_avl.png"
plot "search_avl.txt" using 1:2 with linespoints lt 1 lc rgb "blue" title "AVL Search"

set title "Busca BST"
set output "busca_bst.png"
plot "search_bst.txt" using 1:2 with linespoints lt 1 lc rgb "red" title "BST Search"

set title "Busca Hash"
set output "busca_hash.png"
plot "search_hash.txt" using 1:2 with linespoints lt 1 lc rgb "green" title "Hash Search"

# 6️⃣ INSERÇÃO E BUSCA JUNTOS - CADA UM
set title "Inserção e Busca AVL"
set output "avl_insercao_busca.png"
plot \
    "insert_avl.txt" using 1:2 with linespoints lt 1 lc rgb "blue" title "AVL Insert", \
    "search_avl.txt" using 1:2 with linespoints lt 1 lc rgb "blue" dt 2 title "AVL Search"

set title "Inserção e Busca BST"
set output "bst_insercao_busca.png"
plot \
    "insert_bst.txt" using 1:2 with linespoints lt 1 lc rgb "red" title "BST Insert", \
    "search_bst.txt" using 1:2 with linespoints lt 1 lc rgb "red" dt 2 title "BST Search"

set title "Inserção e Busca Hash"
set output "hash_insercao_busca.png"
plot \
    "insert_hash.txt" using 1:2 with linespoints lt 1 lc rgb "green" title "Hash Insert", \
    "search_hash.txt" using 1:2 with linespoints lt 1 lc rgb "green" dt 2 title "Hash Search"
