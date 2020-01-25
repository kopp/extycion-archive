#include<iostream>
#include<cstdio>
#include "Spielfeld.h"

// prototypen
void hilfsfunktion(int , int , Spielfeld &, Spielfeld & );
void nachbarn_anzuenden(int , int , Spielfeld &, Spielfeld & );

// eigentliches brennen
void hilfsfunktion(int x, int y, Spielfeld &besetzt, Spielfeld &burning )
{ 
	if( besetzt(x,y) && ( ! burning(x,y) ) )
	{
		burning.set(x,y,true) ;
		nachbarn_anzuenden( x , y , besetzt , burning );
	}
}

void nachbarn_anzuenden(int x, int y, Spielfeld &bes, Spielfeld &burn )
{
	// ermittele Nachbarn
	// wenn nachbarn noch nicht brennen, dann zuende sie an
	// starte rekursiv fuer alle neu angezuendeten nachbarn
	hilfsfunktion( x-1, y, bes , burn );
	hilfsfunktion( x+1, y, bes , burn );
	hilfsfunktion( x, y-1, bes , burn );
	hilfsfunktion( x, y+1, bes , burn );

	bes.diff_ausgeben(burn);

}


int main(int argc, char * argv[] )
{

	double besetungswahrscheinlichkeit = .5;
	int breiteM = 10;
	int hoeheM = 10;
	int seed = 1;

	std::srand( seed ); //zufallsgenerator anwerfen

	// besetze felder zufaellig
	Spielfeld besetzt(breiteM, hoeheM, besetungswahrscheinlichkeit);
	besetzt.ausgeben();
	// leeres Spielfeld
	Spielfeld burning(breiteM, hoeheM);


	// starte feuer an der oberen Kante
	for( int x = 0; x < breiteM; x++ )
		if( besetzt( x, 0 ) )
			burning.set( x , 0 , true );

	// eigentliche ausbreitung des feuers ab Kante
	for( int x = 0; x < breiteM; x++ )
		if( besetzt( x, 0 ) && burning( x, 0 ) )
			nachbarn_anzuenden( x, 0, besetzt , burning );

	// abfrage ob perkulation erfolgt ist
	bool perkulation = false;
	for( int x = 0; x < breiteM; x++ )
		if( burning( x , hoeheM - 1 ) ) perkulation = true;

	if( perkulation ) std::cout << "Es fand eine Perkulation statt\n";
	else std::cout << "Es fand KEINE Perkulation statt.\n";
}
