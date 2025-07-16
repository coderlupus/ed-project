# script.gnuplot
set terminal png size 800,600
set output 'graficos/grafico_busca.png'

set title 'Tempo de Busca - Comparação'
set xlabel 'Número de Elementos'
set ylabel 'Tempo de Busca (s)'

set grid
set key outside

plot 'graficos/tempos_binaria.dat' using 1:2 with linespoints lt rgb "red" title 'BST', \
     'graficos/tempos_avl.dat' using 1:2 with linespoints lt rgb "blue" title 'AVL', \
     'graficos/tempos_hash.dat' using 1:2 with linespoints lt rgb "green" title 'Hash'
