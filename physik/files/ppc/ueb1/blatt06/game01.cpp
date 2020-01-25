/*************
 *
 * game01.cpp
 *
 * simuliert game of life
 *
 *                                                         *******************/
#include<iostream>
#include<cstdlib>


int main( int argc, char * argv[] )
{

	short int ueberbev = 3;
	short int ideal = 3;
	short int bleibt = 2;
	short int verarmung = 2;

	int xsize = 74; //spielfeldgroesse
	int  ysize = 90;

	

	bool spielfeldalt[xsize][ysize];
	bool spielfeldneu[xsize][ysize];
	
	for( int x = 1; x < xsize-1; x++)
	{
		for( int y = 1; y < ysize-1; y++ )
		{
			spielfeldneu[x][y] = ( std::rand() % 2 == 1);
		}
	}


	std::srand(25); //zufallsgenerator...

	std::cout << "foo\n";
	//schattenfelder initialisieren
	for( int y = 1 ; y < ysize-1; y++ )
	{
		spielfeldneu[xsize-1][y] = spielfeldneu[1][y];
		spielfeldneu[0][y] = spielfeldneu[xsize-2][y];
	}
	for( int x = 1 ; x < xsize-1; x++ )
	{
		spielfeldneu[x][ysize-1] = spielfeldneu[x][1];
		spielfeldneu[x][0] = spielfeldneu[x][ysize-2];
	}
	spielfeldneu[0][0] = 0;
	spielfeldneu[0][ysize-1] = 0;
	spielfeldneu[xsize-1][0] = 0;
	spielfeldneu[xsize-1][ysize-1] = 0;



	int zeitdauer = 100000;


	for( int t = 0; t < zeitdauer; t++ )
	{
		for( int x = 0; x < xsize; x++ )
			for( int y = 0; y < ysize; y++ )
				spielfeldalt[x][y] = spielfeldneu[x][y];


		for( int x = 1; x < xsize-1; x++ )
		{
			for( int y = 1; y < ysize-1; y++ )
			{
				//summieren
				int summe = spielfeldalt[x-1][y-1] + 
					spielfeldalt[x][y-1] + 
					spielfeldalt[x+1][y-1] + 
					spielfeldalt[x-1][y] + 
					spielfeldalt[x+1][y] + 
					spielfeldalt[x+1][y+1] + 
					spielfeldalt[x][y+1] + 
					spielfeldalt[x-1][y+1] ;
				// propagieren
				if( summe > ueberbev )
					spielfeldneu[x][y] = false;
				if( summe == ideal )
					spielfeldneu[x][y] = true;
				if( summe == bleibt )
					spielfeldneu[x][y] = spielfeldalt[x][y];
				if( summe < verarmung )
					spielfeldneu[x][y] = false;

				//schattenfeld aktualisieren
				for( int y = 1 ; y < ysize-1; y++ )
				{
					spielfeldneu[xsize-1][y] = spielfeldneu[1][y];
					spielfeldneu[0][y] = spielfeldneu[xsize-2][y];
				}
				for( int x = 1 ; x < xsize-1; x++ )
				{
					spielfeldneu[x][ysize-1] = spielfeldneu[x][1];
					spielfeldneu[x][0] = spielfeldneu[x][ysize-2];
				}



			}
		}

		//Ausgabe
		for( int x = 1; x < xsize-1; x++ )
		{
			for( int y = 1; y < ysize-1; y++ )
			{
				if( spielfeldneu[x][y] ) std::cout << "#";
				else std::cout << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n\n t = " << t << "\n\n";
	}








}
