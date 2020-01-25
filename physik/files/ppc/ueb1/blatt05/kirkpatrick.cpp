/******************
 * kirkpatrick.cpp
 *
 * erzeugt zufallszahlen nach kirpatrick
 *
 * Parameter: Anzahl der Zahlen (optional)
 *
 * Compilation via
 * 	$ g++ -o kirkpatrick kirkpatrick.cpp PTSRandom.cc 
 *                                                         *******************/
#include<iostream>
#include "PTSRandom.h"
#include<cstdlib>

int main(int argc, char *argv[] ){
	// Kirkpatrick Stoll generator with seed 2345
	PTS_KPS250RNG rng(2345);
	// get the max value of the produced unsigned integers
	// !! this value can actually occur in the sequence !!
	unsigned int max = rng.UnsignedMax();
	unsigned int rnd;
	// every call to Unsigned() produces a pseudorandom number
	int anzahl = 100000;
	if( argc >= 2 ) anzahl = std::atoi( argv[1] );
	for( int i = 0; i < anzahl; i++ )
	{
		rnd = rng.Unsigned();
		std::cout << rnd << "\n";
	}
	
}

