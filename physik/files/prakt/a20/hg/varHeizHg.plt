set title "Variation der Heizspannung\nU_2 = 2.5V, Temp = 175^oC"
set key left box

plot \
'001.data' title "UH = 5.8V" with lines, \
'005.data' title "UH = 6.3V" with lines, \
'006.data' title "UH = 6.8V" with lines
