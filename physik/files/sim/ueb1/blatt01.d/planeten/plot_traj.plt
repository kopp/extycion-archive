#!/usr/bin/gnuplot


set style data lines
set key box
set terminal x11
set xrange [*:*]
set yrange [*:*]

set xlabel "X-Koordinate [Astron. Einh]"
set ylabel "Y-Koordinate [Astron. Einh]"
set title "Simulation des Sonnensystem"

set size square

plot \
	'traj' u 2:3:1 title "Sonne", \
	'traj' u 5:6:1 title "Erde", \
	'traj' u 8:9:1 title "Mond", \
	'traj' u 11:12:1 title "Mars", \
	'traj' u 14:15:1 title "Venus", \
	'traj' u 17:18:1 title "Jupiter"

