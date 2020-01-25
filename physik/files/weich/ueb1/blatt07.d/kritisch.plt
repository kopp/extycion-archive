#!/usr/bin/gnuplot

set title "Ising Model: Verhalten bei der kritischen Temperatur\n{/Symbol D}T = 0.001, 60 Mittelungen je Temperatur"

set xlabel "Temperatur"
set ylabel "Magnetisierung"

set xrange [1.9:2.5]
set yrange [-.1:1]

set key default
set key left bottom


set sample 10000

# fit
m(T) = (Tc - T)**beta ;
Tc = 2.2691853 ;
beta = 1./8 ;
# fit m(x) 'cool02.data' u ($1<2.27 ? $1 : 1/0):4 via Tc,beta

# kurven
m_param(T,Tc,beta) = (Tc - T)**beta ;
plot \
'cool02.data' u 1:4 title "Abuehlen" lw 3 , \
m_param(x,2.2691853,1./8.) title "Theorie" lw 5  , \
m_param(x,2.21558,0.0629068) title "Fit T_c,{/Symbol b} fuer T < 2.2" , \
m_param(x,2.42055,1./8.) title "Fit T_c fuer T < 2.2" , \
m_param(x,2.21558,0.078897) title "Fit {/Symbol b} fuer T < 2.2"  , \
m_param(x,2.26603,0.0905313) title "Fit T_c,{/Symbol b} fuer T < 2.27"  lw 5
 
# m_param(x,2.21558,0.0629068) title "Fit T_c,{/Symbol b}: T < 2.2" , \
# m_param(x,2.42055,1./8.) title "Fit T_c: T < 2.2" , \
# m_param(x,2.21558,0.078897) title "Fit {/Symbol b}: T < 2.2"  , \
