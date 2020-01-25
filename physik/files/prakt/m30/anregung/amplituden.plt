#####
### STARK
set fit noerrorvariables
g1(x) = m / sqrt(j * (om01**2 - x**2)**2 + b * x**2)
g2(x) = m2 / sqrt(j2 * (om02**2 - x**2)**2 + b2 * x**2)
m = 0.17362666735792
j = 1.91211782658689
om01 = -0.515373699263568
b = 0.000553509323108528
FIT_CONVERGED = 1
FIT_NDF = 11
FIT_STDFIT = 0.0317091668745308
FIT_WSSR = 0.0110601839026453
m2 = 0.167812216995549
j2 = 1.91700969564276
om02 = -0.512116543072679
b2 = 0.00529873199430219
###### plot g2(x), "starkged.data"
### SCHWACH
set fit noerrorvariables
g1(x) = m / sqrt(j * (om01**2 - x**2)**2 + b * x**2)
m = 0.17362666735792
j = 1.91211782658689
om01 = -0.515373699263568
b = 0.000553509323108528
FIT_CONVERGED = 1
FIT_NDF = 9
FIT_STDFIT = 0.42363264987767
FIT_WSSR = 1.61518159838139
###
set sample 2000
set label "antreibendes Moment: 0.173" at 0.7,12
set label "Traegheitsmoment: 1.38" at 0.7,11
#set label "Daempfung, stark: 0.0235" at 0.7,10
#set label "Daempfung, schwach: 0.0728" at 0.7,9
set label "Resonanzfrequenz, stark: 0.51211" at 0.7,4
set label "Resonanzfrequenz, schwach: 0.51537" at 0.7,3
###
set xlabel "Erregerfrequenz  f  in Hz"
set ylabel "Amplitude [relative Einheit]"
set title "Angeregte Schwingung"
plot "schwachged.data" title "Messwerte schwache Daempfung", g1(x) title "Fit schwache Daempfung", "starkged.data" title "Messwerte starke Daempfung", g2(x) title "Fit starke Daempfung"
## fit g1(x) "schwachged.data" via m,j,om01,b
#    EOF
