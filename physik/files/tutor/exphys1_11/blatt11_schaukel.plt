#!/usr/bin/gnuplot

# parameter p ist startimpuls

# sonstige parameter
g = 9.81 ; # schwerebeschl
m = 1. ; # masse des Springers
l = 1. ; # seillaenge
h0 = 1. ; # Schaukelhoehe in Ruhelage
pmax = sqrt(4.*m*m*g*l) ; # maximal anschucken sonst ueberschlag

# geschw bei winkel phi 
v(phi,p) = sqrt( (p**2. / (2*m) - m * g * l * (1.-cos(phi)) ) / m ) ;
# flugdauer
tl(phi,p) = ( v(phi,p)*sin(phi) + sqrt( (v(phi,p)*sin(phi))**2 + 2*g*(h0 + l*(1.-cos(phi)) ) ) ) / g ;
# weite
weite(phi,p) = l*sin(phi) + tl(phi,p) * v(phi,p)*cos(phi) ;
# korrigierte weite
# weite fuer phi=0 abgezogen
weite_korr(phi,p) = weite(phi,p) - weite(0,p) ;

# maximale auslenkung
phimax(p) = acos( ( - p**2. / (2*m) + m*g*l )/(m*g*l)) ; 

# parameterdarstellung des fluts
rx(t,phi,p) = v(phi,p)*cos(phi)*t + l*sin(phi) ;
ry(t,phi,p) = -0.5*g*t**2 + v(phi,p)*sin(phi)*t + h0 + l*(1.-cos(phi)) ;

set xrange [0:pi/2] ;
set xlabel "Absprung bei winkel {/Symbol f}"
set yrange [0:6] ;
set ylabel "Startimpuls"
set zrange [0:*]
set zlabel "Flugweite bis Aufschlag" rotate by 90

unset key

# splot weite(x,y) ;
splot weite_korr(x,y) ;
# plot weite(x,1) , weite( x,10 ) ;

