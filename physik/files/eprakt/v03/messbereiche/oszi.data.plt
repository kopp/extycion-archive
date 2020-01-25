set title "Anzeigen der Messgeraete bei verschiedenen Frequenzen"

set xlabel "Frequenz in kHz"
set ylabel "Abweichung in Prozent"

set logscale y
set yrange [0.02:110]

set key below

set style data linespoints


plot \
'oszi.data' u 1:(abs($2-5)/5*100) 	title "Handmultimeter", \
'' u 1:(abs($3-5)/5*100)	title "Labormultimeter", \
'' u 1:(abs($4-5)/5*100) 	title "Oszilloskop", \
2 title "Grenze: 2%"
