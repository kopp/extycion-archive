#!/bin/bash

ende=150
echo "## $(date) N = 5..$ende" > integrale.data
for i in `seq 5 $ende`
do
	echo -n "computing $i ... "
	./a.out $i >> integrale.data
	echo "done"
done
