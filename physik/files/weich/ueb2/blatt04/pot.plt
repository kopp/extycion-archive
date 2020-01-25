#!/usr/bin/gnuplot

# Potential fuer das Kramers Zeit berechnet wurde f"ur verschiedene a

V(x,a) = 5*(x-1)**2 *(x+1)**2 + a*x ;

# 1st derivative
diff1(x,a) = a - 20*x + 20*x**3 ;
# table of the zero-lines is stored in `extrema.dat'


set xrange [ -1.6 : 1.6 ]
set xlabel "Ort x"
set yrange [ 0 : 7.6 ]
set ylabel "Parameter a"
set zrange [-9:20]

# color
set cbrange [-7:10]
set pm3d
set pm3d explicit


splot \
  V(x,y) title "" with pm3d \
  , V(x,y) title "Potential" \
  , 'extrema.dat' u 1:2:(V($1,$2)) with lines title "Extrema" lw 3
