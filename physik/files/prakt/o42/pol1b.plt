
# mit
plot "pol.data" using 1:3
# anschauen

# theoretischen Verlauf angeben
f(x)=A*exp(B*x)+C


# mit ``` fit f(x) "pol.data" using 1:3 via A,B,C``` erh"alt man:
A = 220.844892015368
B = -0.00646129087668416
C = -92.9216212528526
plot f(x), "pol.data" using 1:3


set terminal postscript enhanced color

set output "asdf.eps"

replot
