set title "Variation der Bremspannung\nU_3 = 0.5V"
set key left box

plot \
'002.data' title "U2 = 7.0V" with lines, \
'010.data' title "U2 = 4.0V" with lines
