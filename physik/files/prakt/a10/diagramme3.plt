#!/usr/bin/gnuplot -persist

###################
# Diagramm mit Fehlerbalken aus Fehlerfortpflanzung (Fehler
# 1.5 mm fuer Radius) und gefitteten Ursprungsgeraden
# Zusaetzlich fett die Geraden, die auf das korrekte e/m
# fuehren wuerden
#                                        ##################
#
#    
#    	G N U P L O T
#    	Version 4.4 patchlevel 0
#    	last modified March 2010
#    	System: Linux 2.6.33-ARCH
#    
#    	Copyright (C) 1986-1993, 1998, 2004, 2007-2010
#    	Thomas Williams, Colin Kelley and many others
#    
#    	gnuplot home:     http://www.gnuplot.info
#    	faq, bugs, etc:   type "help seeking-assistance"
#    	immediate help:   type "help"
#    	plot window:      hit 'h'
# set terminal wxt 0
# set output
unset clip points
set clip one
unset clip two
set bar 1.000000 front
set border 31 front linetype -1 linewidth 1.000
set xdata
set ydata
set zdata
set x2data
set y2data
set timefmt x "%d/%m/%y,%H:%M"
set timefmt y "%d/%m/%y,%H:%M"
set timefmt z "%d/%m/%y,%H:%M"
set timefmt x2 "%d/%m/%y,%H:%M"
set timefmt y2 "%d/%m/%y,%H:%M"
set timefmt cb "%d/%m/%y,%H:%M"
set boxwidth
set style fill  empty border
set style rectangle back fc  lt -3 fillstyle   solid 1.00 border lt -1
set dummy x,y
set format x "% g"
set format y "% g"
set format x2 "% g"
set format y2 "% g"
set format z "% g"
set format cb "% g"
set angles radians
unset grid
set key title ""
set key bmargin center horizontal Right noreverse enhanced autotitles nobox
set key noinvert samplen 4 spacing 1 width 0 height 0 
unset label
set label 1 "Steigung bei 1.0 A : 0.195119 +/. 0.002992" at 20, 55, 0 left norotate back nopoint offset character 0, 0, 0
set label 2 "Steigung bei 1.4 A : 0.0963046 +/- 0.002154" at 20, 45, 0 left norotate back nopoint offset character 0, 0, 0
set label 3 "Steigung bei 1.8 A : 0.0474492 +/- 0.001467" at 20, 35, 0 left norotate back nopoint offset character 0, 0, 0
unset arrow
set style increment default
unset style line
unset style arrow
set style histogram clustered gap 2 title  offset character 0, 0, 0
unset logscale
set offsets 0, 0, 0, 0
set pointsize 1
set encoding default
unset polar
unset parametric
unset decimalsign
set view 60, 30, 1, 1  
set samples 100, 100
set isosamples 10, 10
set surface
unset contour
set clabel '%8.3g'
set mapping cartesian
set datafile separator whitespace
unset hidden3d
set cntrparam order 4
set cntrparam linear
set cntrparam levels auto 5
set cntrparam points 5
set size ratio 0 1,1
set origin 0,0
set style data points
set style function lines
set xzeroaxis linetype -2 linewidth 1.000
set yzeroaxis linetype -2 linewidth 1.000
set zzeroaxis linetype -2 linewidth 1.000
set x2zeroaxis linetype -2 linewidth 1.000
set y2zeroaxis linetype -2 linewidth 1.000
set ticslevel 0.5
set mxtics default
set mytics default
set mztics default
set mx2tics default
set my2tics default
set mcbtics default
set xtics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set xtics autofreq  norangelimit
set ytics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set ytics autofreq  norangelimit
set ztics border in scale 1,0.5 nomirror norotate  offset character 0, 0, 0
set ztics autofreq  norangelimit
set nox2tics
set noy2tics
set cbtics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set cbtics autofreq  norangelimit
set title "Quadrat des Kreisradius gegen Beschleunigungsspannung\nFett sind die Geraden, die auf den Literaturwert fuehren wuerden" 
set title  offset character 0, 0, 0 font "" norotate
set timestamp bottom 
set timestamp "" 
set timestamp  offset character 0, 0, 0 font "" norotate
set rrange [ * : * ] noreverse nowriteback  # (currently [8.98847e+307:-8.98847e+307] )
set trange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set urange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set vrange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set xlabel "Beschleunigungsspannung in Volt" 
set xlabel  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set x2label "" 
set x2label  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set xrange [ 0.00000 : 310.000 ] noreverse nowriteback
set x2range [ * : * ] noreverse nowriteback  # (currently [0.00000:310.000] )
set ylabel "Quadrat des Kreisradius im cm^2" 
set ylabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set y2label "" 
set y2label  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set yrange [ 0.00000 : 60.0000 ] noreverse nowriteback
set y2range [ * : * ] noreverse nowriteback  # (currently [0.00000:60.0000] )
set zlabel "" 
set zlabel  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set zrange [ * : * ] noreverse nowriteback  # (currently [8.98847e+307:-8.98847e+307] )
set cblabel "" 
set cblabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set cbrange [ * : * ] noreverse nowriteback  # (currently [8.98847e+307:-8.98847e+307] )
set zero 1e-08
set lmargin  -1
set bmargin  -1
set rmargin  -1
set tmargin  -1
set locale "C"
set pm3d explicit at s
set pm3d scansautomatic
set pm3d interpolate 1,1 flush begin noftriangles nohidden3d corners2color mean
set palette positive nops_allcF maxcolors 0 gamma 1.5 color model RGB 
set palette rgbformulae 7, 5, 15
set colorbox default
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front bdefault
set loadpath 
set fontpath 
set fit noerrorvariables
f(x) = a * x
g(x) = b * x
h(x) = c * x
i(x) = d * x
GNUTERM = "aqua"
a = 0.195118642614045
GPFUN_f = "f(x) = a * x"
b = 0.096304626702721
GPFUN_g = "g(x) = b * x"
c = 0.0474492270742915
GPFUN_h = "h(x) = c * x"
FIT_CONVERGED = 1
FIT_NDF = 12
FIT_STDFIT = 0.320905895650305
FIT_WSSR = 1.23576712635749
d = 0.0532002280908168
GPFUN_i = "i(x) = d * x"
plot \
 0.1872469196*x title "1.0 A -- Steigung berechnet" lt 4 lw 3,\
 0.09553414265*x lt 4 lw 3 title "1.4 A -- Steigung berechnet",\
 0.05779225913*x lt 4 lw 3 title "1.8 A -- Steigung berechnet",\
 '10.data' using 1:(($2/2)**2):(2*$2*0.15) with yerrorbars title "1.0 A -- Messwerte" lt 1,\
 f(x) title "1.0 A -- Fit" lt 1,\
 '14.data' using 1:(($2/2)**2):(2*$2*0.15) with yerrorbars title "1.4 A -- Messwerte" lt 2,\
 g(x) title "1.4 A -- Fit" lt 2,\
 '18.data' using 1:(($2/2)**2):(2*$2*0.15) with yerrorbars title "1.8 A -- Messwerte" lt 3,\
 i(x) title "1.8 A -- Fit" lt 3
## fit i(x) '18.data' using 1:(($2/2)**2) via d
#    EOF
