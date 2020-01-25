#!/usr/bin/gnuplot

set xlabel "Masse m"
set ylabel "Hoehe des Zylinders (bei h = 1 ist kritische Dichte erreicht)"

set style data lines

set key left
set key title "Temperatur: T/T_c"

set title "VdW Gas in Kolben mit Piston in Hoehe h mit Masse m"

set yrange [0:20]


plot \
'hm.data' u ($3==0.5 ? $1 : 1/0):2 title "t = 0.5" , \
'hm.data' u ($3==0.7 ? $1 : 1/0):2 title "t = 0.7" , \
'hm.data' u ($3==0.9 ? $1 : 1/0):2 title "t = 0.9" , \
'hm.data' u ($3==0.95 ? $1 : 1/0):2 title "t = 0.95" , \
'hm.data' u ($3==0.99 ? $1 : 1/0):2 title "t = 0.99" , \
'hm.data' u ($3==1.0 ? $1 : 1/0):2 title "t = 1.0" w lp , \
'hm.data' u ($3==1.01 ? $1 : 1/0):2 title "t = 1.01" , \
'hm.data' u ($3==1.05 ? $1 : 1/0):2 title "t = 1.05" , \
'hm.data' u ($3==1.1 ? $1 : 1/0):2 title "t = 1.1" , \
'hm.data' u ($3==1.3 ? $1 : 1/0):2 title "t = 1.3" , \
'hm.data' u ($3==2.0 ? $1 : 1/0):2 title "t = 2.0" , \
'hm.data' u ($3==2.5 ? $1 : 1/0):2 title "t = 2.5" , \
'hm.data' u ($3==2.9 ? $1 : 1/0):2 title "t = 2.9" , \
'hm.data' u ($3==3.5 ? $1 : 1/0):2 title "t = 3.5" 

