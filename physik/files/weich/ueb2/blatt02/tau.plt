#!/usr/bin/gnuplot


# mittlere Geschwindigkeit fuer verschiedene Tau


set title "Mittlere Geschwindigkeit <v> fuer verschiedene {/Symbol t}"
set xlabel "{/Symbol t}"
set ylabel "<v>"


set style data linespoints

set key box
set key right bottom

plot \
  "loop_tau_gedaempft/loop_tau.data" title "gedaempft" \
, "loop_tau_ueberdaempft/loop_tau.data" title "ueberdaempft" lw 2
