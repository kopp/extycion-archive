#include<iostream>
#include<cstdlib>
#include "Vector2D.h"

#define sqr(x) (x*x)

int main(int argc , char *argv[] )
{
	int moves = 1000; //anzahl bewegungen
	int walks = 500000; //anzahl versch. walks

	Vector2D endpunkt[walks];

	Vector2D richtungen[4];
	richtungen[0] = Vector2D(1,0);
	richtungen[1] = Vector2D(0,1);
	richtungen[2] = Vector2D(-1,0);
	richtungen[3] = Vector2D(0,-1);
	for( int k = 0; k < walks; k++ )
	{
		srand(k);
		Vector2D brown(0,0); //start bei (0,0)
		for( int i = 0; i < moves; i++ ) 
		{
			brown += richtungen[ int( (4.*rand())/RAND_MAX ) ];

			//Alternativweg:
			/*
			//zahl in {-1,0,1}
			int zufall1 =  ( (rand() % 2==0)?(-1):(1) ) * rand() % 2;
			int zufall2 =  ( (rand() % 2==0)?(-1):(1) ) * rand() % 2;
			brown[i] = brown[i-1] + Vector2D( zufall1 , zufall2 );
			*/

		}
		endpunkt[k] = brown;
	}

	//Momente:
	Vector2D mom1(0,0); 
	Vector2D mom2(0,0);
	for( int k = 0; k < walks; k ++ )
	{
		mom1 += endpunkt[k]; //jede komponente summiert
		mom2 += Vector2D( sqr(endpunkt[k][0]) , sqr(endpunkt[k][1]) ); //quadrat jeder komponente summiert
	}
	mom1 = (1./walks) * mom1; //normierung
	mom2 = (1./walks) * mom2; //normierung

	//// Ausgabe ////
	//Momente
	/*
	std::cout << "# Erstes Moment nach " << walks << " Randomwalks mit je " << moves << " Schritten: \n";
	std::cout << "# " << mom1 << "\n";
	std::cout << "# Zweites Moment nach " << walks << " Randomwalks mit je " << moves << " Schritten: \n";
	std::cout << "# " << mom2 << "\n";
	*/
	//Endpunkte
	for( int k = 0; k < walks; k ++ )
		std::cout << endpunkt[k][0]  << "\n";



}


