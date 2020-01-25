#!/usr/bin/gnuplot

set title "Vergleich der Energie des Gesamtsystems fuer verschiedene Integratoren"
set xlabel "Simulationdauer [Erdjahre]"
set ylabel "Gesamtenergie des Systems [Willk. Einh.]"
set y2label "Gesamtenergie des Systems [Willk. Einh.]"

set y2tics

set style data lines

set xrange [*:*]
set yrange [*:*]

set key left
set key box

plot \
	'traj.euler' u 1:20 title 'Euler (Y2-axe!)' axis x1y2, \
	'traj.velverl' u 1:20 title 'Velocity Verlet', \
	'traj.leapfrog' u 1:20 title 'Leapfrog', \
	'traj.verlet' u 1:20 title 'Verlet', \
	'traj.runge' u 1:20 title 'Runge-Kutta', \
	'traj.precor' u 1:20 title 'Predictor-Corrector'
