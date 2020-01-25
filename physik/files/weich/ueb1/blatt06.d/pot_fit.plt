#!/usr/bin/gnuplot -persist
set title "Potential aus Histogramm (der Offset ist willkuerlich da messtechnisch bedingt)" 
set xlabel "z - z_0" 
set ylabel "Potential {/Symbol f}(z - z_0) in Einheiten von k_B T" 
# # fit ueber alle werte
A1 = 5.01165987125051
b1 = 81.9919840906437
z01 = -0.0854517477988359
c1 = 6.1497656965827
d1 = 2.89272613473932
f1(x) = A1*exp(-b1*(x-z01))+c1*(x-z01) + d1
# # fit ueber ausgewaehlte werte
f(x) = A*exp(-b*(x-z0))+c*(x-z0) + d
A               = 5.00809      
b               = 76.3779      
z0              = -0.0846671   
c               = 7.22227      
d               = 2.66865      
# fit f(x) 'tirm_histo.data' u ($1<0.3? $1 : 1/0):(-log($3)) via A,b,z0,c,d
set key
plot 'tirm_histo.data' u 1:(-log($3)) w lp title "Messwerte" lw 3, \
f1(x) title "Fit: Doppellagenkraefte und Schwerkraft" , \
f(x) title "Fit: dito; nur Messwerte mit z-z_0 < 0.3" lw 2
## fit f(x) 'tirm_histo.data' u 1:(-log($3)) via A,b,c,d,z0
#    EOF
