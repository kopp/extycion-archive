#!/bin/bash

# loop over different values for anisotropie 
# identify v_mittel

echo "# tau # v_mittel (N = 30000, M = 300, anteil = 0.2, dt = 0.01, intensitaet = 2 , anisotropie = 0.8)" > loop_tau.data

for tau in `seq 1 1 10` `seq 15 5 40` `seq 50 10 100`
do
	echo -n "doing tau = $tau ... "

	octave mysim.m $tau > foo
	vm=$(cat foo | grep v_mittel | awk '{print $3}')
	echo "$tau	$vm" >> loop_tau.data

	echo "done"
done


