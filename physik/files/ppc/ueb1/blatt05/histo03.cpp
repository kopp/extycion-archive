#include<iostream>
#include<cstdlib>
/*
 * histo03.cpp
 *
 * erstellt histogramm aus INT-zufallszahlen von stdin
 *
 * Parameter 
 *   <anzahl> [<anz. bins>]
 *
 *                                                         *******************/


const bool verbose = false;



int main(int argc, char* argv[])
{
	int anzahl; //anz. zufallszahlen
	anzahl = std::atol( argv[1] );

	int unterteilungen = 100; //Bins fuer Histogramm
	if( argc >= 3 ) unterteilungen = std::atol( argv[2] );

	int histo[unterteilungen+1]; //count in bins
	for( int i = 0; i <= unterteilungen; i++)
		histo[i] = 0;

	int x[anzahl]; //zufallszahlen
	for( unsigned int i = 0; i < anzahl; i++ )
		std::cin >> x[i];
	/*
	std::cout << "# Eingelesen \n";
	for( int i = 0; i < anzahl; i+= 10000 )
		std::cout << x[i] << "\n";
	*/

	//min max finden
	int max=0; //Groesste Zufallszahl
	int min=0; //Kleinste Zufallszahl
	for( int i = 0; i < anzahl; i++ )
	{
		if( x[i] < min ) min = x[i];
		if( x[i] > max ) max = x[i];
	}

	//zahlen auf bins verteilen
	for( int i = 0; i < anzahl; i++ )
	{
		//histo[ ( unterteilungen * ((x[i]-min) / (max-min)) ) ] ++; //zufallszahl dem bin zuordnen
		//histo[ (int) ( ((double)x[i]-(double)min)/(double(max-min)) ) * unterteilungen ]++;
		histo[ ( (x[i]-min) * unterteilungen )/(max-min)  ]++;
		if( verbose ) std::cout << "# " << i << " von " << anzahl << " : " << x[i] << " kommt in Bin " <<( (x[i]-min) * unterteilungen )/(max-min) <<"\n";
	}


	// Ausgabe
	std::cout << "# " << anzahl << " Zahlen wurden auf " << unterteilungen << " Bins verteilt; \n";
	std::cout << "# Maximum: " << max << "\n";
	std::cout << "# Minimum: " << min << "\n";
	std::cout << "#Bin Nr" << "\t" << "Anzahl" << "\n";
	for( unsigned int i = 0; i <= unterteilungen; i++ )
		std::cout << i << "\t" << histo[i] << "\n";

}


	
