#!/bin/sh

#
# schwelle.sh
#
# runs the compiled program perk04.cpp quite often with different parameters
# for probability and seed
# a 100x100 grid is always assumed.
#

LANG=us_US
# it's necessary to do so becaus with locales such as de_DE the decimal-sign is
# a `,' and the c++-program does not interpret this right.

for wahrsch in `seq 0.5 0.001 0.7`
do
	anzahl=0
	for seed in `seq 0 1000`
	do
		i=$(./a.out $wahrsch $seed 100 100 n)
		((anzahl+=$i))
	done
	echo "$wahrsch	$anzahl"
done

