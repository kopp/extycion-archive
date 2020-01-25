#!/usr/bin/gnuplot -persist
unset label
set label 1 "T_c" at 2.36919, 1, 0 left norotate back nopoint offset character 0, 0, 0
unset arrow
set arrow 1 from 2.26919, 0, 0 to 2.26919, 1, 0 nohead back nofilled linetype -1 linewidth 1.000
set xlabel "Temperatur" 
set ylabel "Magnetisierung" 
set y2label "Energie" 
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front bdefault
Tc = 2.2691853

set key right center
set key box

set xzeroaxis

set style data linespoints 

set title "Ising Model.\n{/Symbol D}T = 0.1, 10 Mittelungen je Temperatur"

plot \
'heat01.data' u 1:4 title "M (y1) [heizen]", \
'cool01.data' u 1:4 title "M (y1) [kuehlen]" w p, \
'heat01.data' u 1:2 title "E (y2) [heizen]" axis x1y2 , \
'cool01.data'u 1:2 title "E (y2) [kuehlen]" axis x1y2
#    EOF
