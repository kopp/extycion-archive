#!/bin/bash

echo "# fibon-rek01c.cpp yields:" >> data
for i in `seq 1 45`
	## es macht nur sinn, bis 45 zu z"ahlen, weil f"ur 46 die Integrer schon "uberschritten sind.
do
	./a.out $i v >> data
	echo -n "$i   "
done
echo "# fibon-rek01c.cpp done:" >> data
echo "--- done ---"
