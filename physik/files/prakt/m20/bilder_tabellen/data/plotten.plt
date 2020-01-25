set title "Stark gedaempfte Schwingung: Videoanalyse"
set xlabel "Zeit in s"
set ylabel "Auslenkung in cm"
set grid
set xtics 0.1
set xtics rotate by 90
set ytics 0.5
set terminal postscript enhanced color
unset key
set output "starkged-2.eps"
plot "starkged3.data" using 4:6 with linespoints
