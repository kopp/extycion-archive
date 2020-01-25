set title "Variation der Temperatur\nU_2 = 2.5V, U_H = 5.8V"
set key left box

plot \
'008.data' title "Temp - 165C" with lines, \
'007.data' title "Temp - 170C" with lines, \
'001.data' title "Temp - 175C" with lines, \
'009.data' title "Temp - 180C" with lines, \
'010.data' title "Temp - 185C" with lines
