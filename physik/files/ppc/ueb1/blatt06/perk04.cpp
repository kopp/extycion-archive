/*
 * perk04.cpp
 *
 * simuliert perkulation 
 *
 * parameter:
 * 	<besetzungswahrscheinlichkeit> [ seed  [ <breite> <hoehe> [ <asugabe> ] ] ]
 * bes: double in [0,1]
 * seed: int;
 * breite, hoehe: int
 * ausgabe: c fuer konsole (default), t fuer tcl-script und n fuer keine  (t NOT IMPLEMENTED YET!)
 *
 */

#include<iostream>
#include<cstdio>
#include<cstdlib> // for atoi
#include "Spielfeld.h"



// globales
const bool verbose = false;



// prototypen
void hilfsfunktion(int , int , Spielfeld &, Spielfeld & );
void nachbarn_anzuenden(int , int , Spielfeld &, Spielfeld & );



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
	//
	// diese Funktion ermittelt nachbarn und fuehrt obiges mit allen aus
	hilfsfunktion( x-1, y, bes , burn );
	hilfsfunktion( x+1, y, bes , burn );
	hilfsfunktion( x, y-1, bes , burn );
	hilfsfunktion( x, y+1, bes , burn );

	//bes.ausgeben();
	//burn.ausgeben();
	bes.diff_ausgeben(burn);

}




int main(int argc, char * argv[] )
{

	double besetungswahrscheinlichkeit = .5;
	int breiteM = 10;
	int hoeheM = 10;
	int seed = 1;
	char ausgabedevice = 'c';

	switch( argc )
	{
		case 6:
			ausgabedevice = *argv[5];
		case 5:
			breiteM = std::atoi(argv[3]);
			hoeheM = std::atoi(argv[4]);
		case 3:
			seed = std::atoi(argv[2]);
		case 2:
			besetungswahrscheinlichkeit = std::atof(argv[1]);
		case 1:
			break;
		default:
			std::cout << "Fehler: Parameter falsch angegeben!\n";
			std::exit(2);
	}


	if( verbose ) std::cout <<" Ausgabedevice: " << ausgabedevice << std::endl;
	std::srand( seed ); //zufallsgenerator anwerfen


	// besetze felder zufaellig
	Spielfeld besetzt(breiteM, hoeheM, besetungswahrscheinlichkeit , ausgabedevice);
	besetzt.ausgeben();
	if( verbose ) {std::cout << "Besetzt:\n"; besetzt.ausgeben(); }
	// leeres Spielfeld
	Spielfeld burning(breiteM, hoeheM, ausgabedevice);
	if( verbose ) {std::cout << "Besetzt:\n"; besetzt.ausgeben(); }
	/*
	 * die daten in besetzt werden komisch sobald burning initialisiert wird.
	 * -> constructor von Spielfeld anschauen...
	 */

	if( verbose ) {std::cout << "Burning:\n"; burning.ausgeben(); }


	// starte feuer an der oberen Kante
	for( int x = 0; x < breiteM; x++ )
	{
		if( besetzt( x, 0 ) )
		{
			burning.set( x , 0 , true );
		}
	}
	if( verbose ) {std::cout << "Burning:\n"; burning.ausgeben(); }
	if( verbose ) {std::cout << "Besetzt:\n"; besetzt.ausgeben(); }


	// eigentliche ausbreitung des feuers
	for( int x = 0; x < breiteM; x++ )
	{
		if( besetzt( x, 0 ) && burning( x, 0 ) )
		{
			if( verbose ) {std::cout << "Besetzt:\n"; besetzt.ausgeben(); }
			nachbarn_anzuenden( x, 0, besetzt , burning );
		}
	}


	// abfrage ob perkulation erfolgt ist
	bool perkulation = false;
	for( int x = 0; x < breiteM; x++ )
		if( burning( x , hoeheM - 1 ) ) perkulation = true;


	switch( ausgabedevice )
	{
		case 't':
		case 'c':
			if( perkulation ) std::cerr << "Es fand eine Perkulation statt\n";
			else std::cerr << "Es fand KEINE Perkulation statt.\n";
			break;
		case 'n':
			if( perkulation ) std::cout << 1 << "\n";
			else std::cout << 0 << "\n";
			break;
	}


}

