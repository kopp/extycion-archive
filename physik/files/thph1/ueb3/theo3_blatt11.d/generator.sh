#!/bin/bash
#
# generiert eine Serie von Bildern von sich ausbreitenden Kugelwellen in
# schnell bewegten Koordinatensystemen
#
#


LANG=us_US

for v in `seq 0.1 0.1 1.0`
do
	for w in `seq 0.1 0.1 1.0`
	do
echo "
set terminal postscript enhanced color
set output \"rel_kugelwelle-$v-$w.eps\"
xs(phi,v,w,ts) = (w*cos(phi) - v)*ts/(1-v*w*cos(phi))
ys(phi,v,w,ts) = w*ts/(1-v*w*cos(phi))*sin(phi)
set param
set dummy phi
set xrange [-8:6]
set yrange [-7:7]
set title \"Ausbreitung einer Kugelwelle im System mit v = $v c und Wellengeschw. w = $w c\"
set size square
set key below
v = $v
w = $w
set sample 1000
plot xs(phi,v,w,1), ys(phi,v,w,1) title \"t = 1\", \\
	xs(phi,v,w,2), ys(phi,v,w,2) title \"t = 2\", \\
	xs(phi,v,w,3), ys(phi,v,w,3) title \"t = 3\", \\
	xs(phi,v,w,4), ys(phi,v,w,4) title \"t = 4\", \\
	xs(phi,v,w,5), ys(phi,v,w,5) title \"t = 5\", \\
	xs(phi,v,w,6), ys(phi,v,w,6) title \"t = 6\", \\
	xs(phi,v,w,7), ys(phi,v,w,7) title \"t = 7\", \\
	xs(phi,v,w,8), ys(phi,v,w,8) title \"t = 8\", \\
	xs(phi,v,w,9), ys(phi,v,w,9) title \"t = 9\", \\
	xs(phi,v,w,10), ys(phi,v,w,10) title \"t = 10\", \\
	xs(phi,v,w,11), ys(phi,v,w,11) title \"t = 11\"
" > tmp.plt
		gnuplot tmp.plt

	done
done
