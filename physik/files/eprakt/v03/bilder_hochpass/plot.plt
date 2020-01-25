set style data lines
set xlabel "Zeit (willk. Einh)"
set ylabel "Spannung (willk. Einh)"

unset xtics
unset ytics

unset key

set terminal postscript enhanced color portrait
set output 'XXX.eps'

plot 'XXX' u 1:3, '' u 1:4
