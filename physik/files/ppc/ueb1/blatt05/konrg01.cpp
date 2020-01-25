/*
 * konrg01.cpp
 *
 * erzeugt (schlechte) Pseudozufallszahlen
 *
 * Parameter:
 * 	<anzahl> <max>
 * Ausgabe: 3 zufallszahlen mit <tab> getrennt pro Zeile.
 *                                                          ******************/


#include<iostream>
#include<cstdlib>


int main(int argc, char *argv[])
{
	int anz = 100000;
	int r = 243000;
	int m = 4561;
	int a = 51349;

	switch( argc )
	{
		case 3:
			r = std::atoi(argv[2]);
		case 2:
			anz = std::atoi(argv[1]);
		break;
	}

			
	int seed = 1;


	int kongr[anz];
	kongr[0] = seed;

	for( int i = 0; i < anz-2; i++ )
		kongr[i+1] = (m * kongr[i] + a) % r;

	//Ausgabe
	for( int i = 0; i < anz - (anz % 3) -3;  )
		std::cout << kongr[i++] << "\t" << kongr[i++] << "\n" ;//<< kongr[i++] << "\n";





}
	
