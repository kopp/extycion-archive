#include<iostream>
#include<cstdlib>
/*
 * histo01.cpp
 *
 * erstellt histogramm aus kongruentiell erzeugten zufallszahenl
 *
 *                                                         *******************/

//// general
bool verbose = false;



//// ZUFALLSZAHLEN GENERIEREN ////
// basiert auf konrg01.cpp
// parameter:
// 	<liste> <anz> <max> 
// 	<liste> <anz> <max> <m> <a>
// m und a sind nicht wichtig
void kong(int kongr[], int anz, int r = 243000, int m = 4561,int a = 51349)
{
	int seed = 1;

	//int kongr[anz];
	kongr[0] = seed;

	for( int i = 0; i < anz-2; i++ )
		kongr[i+1] = (m * kongr[i] + a) % r;

	//Ausgabe
	/*
	for( int i = 0; i < anz - (anz % 3) -3;  )
		std::cout << kongr[i++] << "\t" << kongr[i++] << "\t" << kongr[i++] << "\n";
	*/


}

int main(int argc, char* argv[])
{
	int anzahl = 1000000; //anz. zufallszahlen
	//anzahl = std::atoi( argv[1] );

	int max = 243000; //Groesste Zufallszahl
	//max = std::atoi( argv[2] );

	int unterteilungen = 100; //Bins fuer Histogramm

	int histo[unterteilungen]; //cont in bins
	for( int i = 0; i < unterteilungen; i++)
		histo[i] = 0;

	int x[anzahl]; //zufallszahlen
	kong( x , sizeof(x)/sizeof(int) , max );
	if( verbose ) std::cout << "zufallszazhlen erzeugt\n";


	//zahlen auf bins verteilen
	for( int i = 0; i < anzahl; i++ )
	{
		histo[ ( unterteilungen * x[i] / max ) ] ++; //zufallszahl dem bin zuordnen
		if( verbose ) std::cout << i << " von " << anzahl << " : " << x[i] << " kommt in Bin " << unterteilungen*x[i]/max <<"\n";
	}


	// Ausgabe
	std::cout << "#Bin Nr" << "\t" << "Anzahl" << "\n";
	for( int i = 0; i < unterteilungen; i++ )
		std::cout << i << "\t" << histo[i] << "\n";

}


	
