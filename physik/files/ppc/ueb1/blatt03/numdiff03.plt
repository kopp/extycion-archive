
# funktion:
f(x) = sin(10*x)*exp(-x)
# ableitung
g(x) = 10*cos(10*x)*exp(-x) - sin(10*x)*exp(-x)
# 2. ableitung
h(x) = -100*sin(10*x)*exp(-x) -20 * cos(10*x)*exp(-x) + sin(10*x)*exp(-x)


set terminal postscript enhanced color portrait
set output "abl-3.eps"

## funktion
plot f(x) title "Funktion", "abl.data" using 1:2 title "Funktion"

## 1. Ableitung
plot g(x) title "Ableitung", "abl.data" using 1:3 title "Linke Ableitung -- 1. Ordnung"
plot g(x) title "Ableitung", "abl.data" using 1:4 title "Rechte Ableitung -- 1. Ordnung"
plot g(x) title "Ableitung", "abl.data" using 1:5 title "Zentrale Ableitung -- 2. Ordnung"
plot g(x) title "Ableitung", "abl.data" using 1:6 title "Zentrale Ableitung -- 3. Ordnung"

set title "Vergleich der Ableitungen"
plot g(x) title "Ableitung", "abl.data" using 1:3 title "Linke Ableitung -- 1. Ordnung" \
, "abl.data" using 1:4 title "Rechte Ableitung -- 1. Ordnung" \
, "abl.data" using 1:5 title "Zentrale Ableitung -- 2. Ordnung" \
, "abl.data" using 1:6 title "Zentrale Ableitung -- 3. Ordnung"
unset title

set title "Vergleich der Ableitungen -- mit Fehler"
set logscale y2
set key below
set y2tics
plot g(x) title "Ableitung"\
, "abl.data" using 1:3 title "Linke Ableitung -- 1. Ordnung" \
, "abl.data" using 1:4 title "Rechte Ableitung -- 1. Ordnung" \
, "abl.data" using 1:5 title "Zentrale Ableitung -- 2. Ordnung" \
, "abl.data" using 1:6 title "Zentrale Ableitung -- 3. Ordnung" \
, "abl.data" using 1:(abs(g($1)-$3)) title "Fehler Linke Ableitung -- 1. Ordnung" axis x1y2 with linespoints \
, "abl.data" using 1:(abs(g($1)-$4)) title "Fehler Rechte Ableitung -- 1. Ordnung" axis x1y2 with linespoints \
, "abl.data" using 1:(abs(g($1)-$5)) title "Fehler Zentrale Ableitung -- 2. Ordnung" axis x1y2 with linespoints \
, "abl.data" using 1:(abs(g($1)-$6)) title "Fehler Zentrale Ableitung -- 3. Ordnung" axis x1y2 with linespoints
unset title
unset y2tics
set key default

## zweite ABl
plot h(x) title "2. Ableitung", "abl.data" using 1:7 title "Linke zweite Abl -- 1. Ordnung"
plot h(x) title "2. Ableitung", "abl.data" using 1:8 title "Rechte zweite Abl -- 1. Ordnung"
plot h(x) title "2. Ableitung", "abl.data" using 1:9 title "Zentrale zweite Abl -- 2. Ordnung"
plot h(x) title "2. Ableitung", "abl.data" using 1:10 title "Zentrale zweite Abl -- 3. Ordnung"

set title "Vergleich der zweiten Ableitungen"
plot h(x) title "2. Ableitung", \
"abl.data" using 1:7 title "Linke zweite Abl -- 1. Ordnung", \
"abl.data" using 1:8 title "Rechte zweite Abl -- 1. Ordnung", \
"abl.data" using 1:9 title "Zentrale zweite Abl -- 2. Ordnung", \
"abl.data" using 1:10 title "Zentrale zweite Abl -- 3. Ordnung"
unset title
