set title "Videoanalyse -- sehr stark gedaempft"
set xlabel "Zeit t in s"
set ylabel "Auslenkung x (relative Einheit)"
set xrange [0:*]
unset key
set grid
set terminal postscript enhanced color
set output "sehrstarkgedaempft1-2.eps"
plot "0_75A.data" using 4:5 with linespoints, 150 * exp(-0.015 * x) + 163 title "Einhuellende Exponentialfunktion"
