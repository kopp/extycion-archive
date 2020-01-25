#include<iostream>
#include<cstdlib>
#include "Vector2D.h"

int main(int argc , char *argv[] )
{
	if( argc < 2 )
	{
		std::cout << "Fehler: Mindestens einen Parameter angeben: Laenge \n";
	}
	int moves = std::atoi( argv[1] ); //anzahl bewegungen
	Vector2D brown[moves];
	brown[0] = Vector2D(0,0);

	int seed = 0;
	if( argc >= 3 )
		seed = std::atoi( argv[2] );
	srand(seed);

	Vector2D richtungen[4];
	richtungen[0] = Vector2D(1,0);
	richtungen[1] = Vector2D(0,1);
	richtungen[2] = Vector2D(-1,0);
	richtungen[3] = Vector2D(0,-1);
	for( int i = 1; i < moves; i++ )
	{
		brown[i] = brown[i-1] + richtungen[ int( (4.*rand())/RAND_MAX ) ];
		
		//Alternativweg:
		/*
		//zahl in {-1,0,1}
		int zufall1 =  ( (rand() % 2==0)?(-1):(1) ) * rand() % 2;
		int zufall2 =  ( (rand() % 2==0)?(-1):(1) ) * rand() % 2;
		brown[i] = brown[i-1] + Vector2D( zufall1 , zufall2 );
		*/

	}

	//Ausgabe
	for( int i = 1; i < moves; i++ )
		std::cout << i << "\t" << brown[i][0] << "\t" << brown[i][1] << "\n";


}


