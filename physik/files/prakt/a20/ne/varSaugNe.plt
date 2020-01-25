set title "Variation der Saugspannung\nU_2 = 7V"
set key left box

plot \
'001.data' title "U3 = 0.0V" with lines, \
'002.data' title "U3 = 0.5V" with lines, \
'003.data' title "U3 = 1.0V" with lines, \
'004.data' title "U3 = 1.5V" with lines, \
'005.data' title "U3 = 2.0V" with lines, \
'006.data' title "U3 = 2.5V" with lines, \
'007.data' title "U3 = 3.0V" with lines
