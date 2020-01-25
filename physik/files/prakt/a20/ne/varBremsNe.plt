set title "Variation der Bremspannung\nU_3 = 3V"
set key left box

plot \
'007.data' title "U2 = 7.0V" with lines, \
'008.data' title "U2 = 7.5V" with lines, \
'009.data' title "U2 = 8.0V" with lines
