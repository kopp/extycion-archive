#!/usr/bin/gnuplot

# parabolische Form des Gauss-Strahls -- Aufg. 1 (c)

# Eine konstante Phase wurde angenommen ( k D ) und nach r aufgeloest:


# Parameter:
# wellenzahl
k = 1;

# Funktion
# r^2 (z in Einheiten von z0)

r_sq( z , D ) = ( D + atan(z)/k - z)*2.*( 1 + (1./z)**2 );

unset key

set xrange [-5:5]
set yrange [0:0.2]
set zrange [0:7]

set xlabel "z-Koordinate (Ausbreitungsrichtung) in Einheiten von z_0"
set ylabel "Konstante Phase in Radiant/k"
set zlabel "Radius" rotate by 90
set title "Radius des Strahlbuendels eines Gausstrahls senkrecht zur Ausbreitungsrichtung\n in Einheiten von  sqrt( {/Sybmol (k/z_0) } )" 

set encoding utf8

set isosample 20,50

splot sqrt( abs( r_sq( x, y ) ) ) ;
