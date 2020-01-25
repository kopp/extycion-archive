#ifndef SPIELFELD_H
#define SPIELFELD_H

#include<cstdlib>
#include<iostream>


const bool liniezeichnen = true;
const bool SPIELFELD_Hverbose = false;


static double zufall()
//gibt eine zufallszahl zwischen 0 und 1 zurueck
{
	// rand()
	return double(rand())/RAND_MAX;
}


class Spielfeld {
	private:
		int breite, hoehe;
		bool *felder;
		char ausgabedevice;
	public:
		// const/destructor
		Spielfeld(int, int, char);
		Spielfeld(int, int, double, char);
		/*
		~Spielfeld() 
		{ 
			delete[] felder ;
		}
		*/
		// getter
		bool operator() (int, int);
		// setter
		void set(int, int, bool);
		// nachtraeglich besetzen
		void zufaellig_besetzen(double);
		// output
		void ausgeben(); // nur ein Spielfeld ausgeben
		void diff_ausgeben(Spielfeld &); // verknuepfung von zwei ausgeben
		void setausgabedevice(char);
};


Spielfeld::Spielfeld(int breiteP, int hoeheP, char device = 'c' ) 
: breite(breiteP), hoehe(hoeheP), felder( new bool[ breiteP*hoeheP ] )
{  
	for( int i = 0; i < breite; i++ )
		for( int j = 0; j < hoehe; j++ )
			felder[j*hoehe + i] = false;
	if( SPIELFELD_Hverbose ) std::cout << "adresse von `felder`: " << felder <<"\n";
	ausgabedevice = device;
}
Spielfeld::Spielfeld(int breiteP, int hoeheP, double besetzungswahrscheinlichkeit, char device = 'c') 
: breite(breiteP), hoehe(hoeheP), felder( new bool[ breiteP*hoeheP ] )
{
       	
	for( int i = 0; i < breite; i++ )
		for( int j = 0; j < hoehe; j++ )
			felder[j*hoehe + i] = ( besetzungswahrscheinlichkeit > zufall() );
					//besetzungswahrscheinlichkeit*besetzungswahrscheinlichkeit*besetzungswahrscheinlichkeit > 
					//( double(rand()*rand()*rand()) / double(RAND_MAX*RAND_MAX*RAND_MAX) ) 
					//double(rand()) * double(rand()) * double(rand()) / double(RAND_MAX) /double(RAND_MAX) /double(RAND_MAX) 
	if( SPIELFELD_Hverbose ) std::cout << "adresse von `felder`: " << felder <<"\n";
	ausgabedevice = device;
}




bool Spielfeld::operator() (int x, int y)
{
	// abfrage ob felder sinnvoll sind
	if( ( 0 <= x) && (x < breite) && ( 0 <= y ) && ( y < hoehe ) )
		return felder[y*hoehe + x];
	// wenn nicht: false ausgeben [felder ausserhalb des spielfelds sind nicht besetzt...]
	//else return false;
	else
	{
		if ( SPIELFELD_Hverbose ) std::cout << "Es wurde eine Koordinate aufgerufen, die keinen Sinn macht: ( " << x << " , " << y << " ) \n";
		return false;
	}
}


void Spielfeld::set(int x, int y, bool foo)
{
	// abfrage ob felder sinnvoll sind
	if( ( 0 <= x) && (x < breite) && ( 0 <= y ) && ( y < hoehe ) )
		felder[y*hoehe + x] = foo;
	// wenn nicht: stirb
	else 
	{
		std::cout << "FEHLER: Es wurde eine Koordinate aufgerufen, die keinen Sinn macht: ( " << x << " , " << y << " ) \n";
		std::exit(1);
	}
}




void Spielfeld::zufaellig_besetzen(double besetzungswahrscheinlichkeit)
{
	for( int i = 0; i < breite; i++ )
		for( int j = 0; j < hoehe; j++ )
			felder[j*hoehe+i] = ( besetzungswahrscheinlichkeit > zufall() );
}




void Spielfeld::ausgeben()
{
	//kindof bestimmt art des outputs:
	//c fuer commandline (default)
	//t fuer tcl-script
	//n fuer keinen
	// linie ---
	switch( ausgabedevice )
	{
		case 'c':
			if( liniezeichnen )
			{
				for( int a = 0; a < breite; a++ )
					std::cout << "-";
				std::cout << "\n";
			}
			// ---

			for( int j = 0; j < hoehe; j++ )
			{
				for( int i = 0; i < breite; i++ )
				{
					if( felder[j*hoehe+i] ) std::cout << "#" ;
					else std::cout << " ";
				}
				std::cout << "\n";
			}

			// linie ---
			if( liniezeichnen )
			{
				for( int a = 0; a < breite; a++ )
					std::cout << "-";
				std::cout << "\n";
			}
			// ---
			break;

		case( 't' ):
			std::cout << "f 0 0" << std::endl;
			for( int j = 0; j < hoehe; j++ )
			{
				for( int i = 0; i < breite; i++ )
				{
					if( felder[j*hoehe+i] ) std::cout << "o " << i << " " << j << std::endl;
				}
			}
			break;

		case 'n':
			//don't output anything
			break;
	}
}


void Spielfeld::diff_ausgeben(Spielfeld &foo)
{
	switch(ausgabedevice)
	{
		case 'c':
			{
				if( liniezeichnen )
				{
					for( int a = 0; a < breite; a++ )
						std::cout << "-";
					std::cout << "\n";
				}
				for( int j = 0; j < hoehe; j++ )
				{
					for( int i = 0; i < breite; i++ )
					{
						if( felder[j*hoehe+i] && foo(i,j) ) std::cout << "@" ;
						else
						{
							if( felder[j*hoehe+i] && ( ! foo(i,j) ) ) std::cout << "#" ;
							else std::cout << " ";
						}
					}
					std::cout << "\n";
				}
				if( liniezeichnen )
				{
					for( int a = 0; a < breite; a++ )
						std::cout << "-";
					std::cout << "\n";
				}
			}
			break;

		case 't':

			break;

		case 'n':
			break;
	}


	// FIXME: abfrage nach gleicher breite und hoehe
}


void Spielfeld::setausgabedevice(char foo)
{
	switch(foo)
	{
		case 'c':
		case 't':
		case 'n':
			ausgabedevice = foo;
			break;
		default:
			std::cout << "Falscher ausgabeparameter! nur 'c', 't' oder 'n' verwenden! \n";
			std::exit(3);
	}
}



#endif
