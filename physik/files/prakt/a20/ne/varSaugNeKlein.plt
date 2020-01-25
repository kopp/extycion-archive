set title "Variation der Saugspannung\nU_2 = 7V"
set key left box

set y2tics

plot \
'001.data' title "U3 = 0.0V Y2-Achse" with lines axis x1y2, \
'002.data' title "U3 = 0.5V Y2-Achse" with lines axis x1y2, \
'003.data' title "U3 = 1.0V Y2-Achse" with lines axis x1y2, \
'004.data' title "U3 = 1.5V Y2-Achse" with lines axis x1y2, \
'005.data' title "U3 = 2.0V" with lines, \
'006.data' title "U3 = 2.5V" with lines, \
'007.data' title "U3 = 3.0V" with lines
