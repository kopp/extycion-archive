set title "Variation der Bremsspannung\nU_H = 5.8V, Temp = 175^oC"
set key left box

plot '003.data' title "U2 = 1.5V" with lines, \
'004.data' title "U2 = 2.0V" with lines, \
'001.data' title "U2 = 2.5V" with lines
