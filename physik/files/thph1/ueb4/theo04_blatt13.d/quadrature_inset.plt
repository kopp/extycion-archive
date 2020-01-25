#!/usr/bin/gnuplot -persist

set term post eps enh 
set outp 'quadrature.eps'

set size 1,1
set origin 0,0

set multiplot # this will be followed by two plots

# 1.
set size 1,1
set origin 0,0

set title "Integral der Gauss Glocke von -x bis x" 
set xlabel "Integrationsgrenzen" 
set ylabel "Wert des Integrals (berechnet mit octave's 'quad'" 

plot 'quadrature.oct' title "Berechnet mit octave" w lp, 0.9

# 2.

set size 0.6,0.4
set origin 0.35,0.1

set grid

set key left

set xlabel ""
set ylabel ""
set title "Interessant"
plot [1.61:1.68] 'quadrature.oct' title "Berechnet mit octave" w lp, 0.9
#    EOF
