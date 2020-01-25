
set xrange [2.5:12.5]
set yrange [1400:1775]
set ylabel "Phasengeschwindigkeit Ultraschall"
set xlabel "Frequenz Ultraschall in MHz"
set title "Messwerte mit Standardabweichungen und Mittelwert"
set key below
plot \
"werte.data" using ($1-0.1):2:(30.3) with yerrorbars title "Dest., rot" lt 2, \
1480.68 title "" lt 2 , \
"werte.data" using ($1+0.1):3:(21.86) with yerrorbars title "Dest., gruen" lt 3, \
1492.15 title "" lt 3, \
"werte.data" using ($1 - 0.1):4:(37.66) with yerrorbars title "NaCl., rot" lt 4, \
1671.49 title "" lt 4, \
"werte.data" using ($1 + 0.1):5:(17.87) with yerrorbars title "NaCl., gruen" lt 5, \
1674.83 title "" lt 5# , \
# 1486.42 title "Dest, ges." lt 6, \
# 1673.16 title "NaCl, ges." lt 7
