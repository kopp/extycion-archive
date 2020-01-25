#!/usr/bin/gnuplot

set title "Entropieverhalten zweier Festkoerper"
set xlabel "{/Symbol D}T / 2T_a^{(2)}"
set ylabel "{/Sybmol D}S / C"

# exakt
S1(x) = log( (1+x)/(1+2*x) );
S2(x) = log( 1+x );
# taylor
s1(x) = -(1.5 - 2./(1+x) + 0.5 / (1+x)**2 );
s2(x) = x - x**2/2;

set xrange [0:1.0]
set key box
set key top left


plot \
s1(x) title "Taylor s1" lt 1 lw 1 , \
s2(x) title "Taylor s2" lt 2 lw 1, \
s1(x)+s2(x) title "Taylor s1+s2" lt 3 lw 1, \
S1(x) title "exakt s1" lt 1 lw 4 , \
S2(x) title "exakt s2" lt 2 lw 4, \
S1(x)+S2(x) title "exakt s1+s2" lt 3 lw 5
