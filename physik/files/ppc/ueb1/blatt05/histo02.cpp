#include<iostream>
#include<cstdlib>
/*
 * histo02.cpp
 *
 * erstellt histogramm aus INT-zufallszahlen von stdin
 *
 * Parameter 
 *   <anzahl> <max> <min> [<anz. bins>]
 *
 *                                                         *******************/


const bool verbose =true;



int main(int argc, char* argv[])
{
	unsigned long anzahl; //anz. zufallszahlen
	anzahl = std::atol( argv[1] );

	unsigned long max; //Groesste Zufallszahl
	max = std::atol( argv[2] );

	unsigned long min; //Kleinste Zufallszahl
	min = std::atol( argv[3] );

	unsigned long unterteilungen = 100; //Bins fuer Histogramm
	if( argc >= 5 ) unterteilungen = std::atol( argv[4] );

	int histo[unterteilungen]; //count in bins
	for( int i = 0; i < unterteilungen; i++)
		histo[i] = 0;

	unsigned long x[anzahl]; //zufallszahlen
	for( unsigned int i = 0; i < anzahl; i++ )
		std::cin >> x[i];

	/*
	std::cout << "# Eingelesen \n";
	for( int i = 0; i < anzahl; i+= 10000 )
		std::cout << x[i] << "\n";
	*/



	//zahlen auf bins verteilen
	for( int i = 0; i < anzahl; i++ )
	{
		//histo[ ( unterteilungen * ((x[i]-min) / (max-min)) ) ] ++; //zufallszahl dem bin zuordnen
		//histo[ (unsigned long) ( ((double)x[i]-(double)min)/(double(max-min)) ) * unterteilungen ]++;
		histo[ ( (x[i]-min) * unterteilungen )/(max-min)  ]++;
		if( verbose ) std::cout << "# " << i << " von " << anzahl << " : " << x[i] << " kommt in Bin " << (x[i]-min)/(max-min) * unterteilungen  <<"\n";
	}


	// Ausgabe
	std::cout << "# " << anzahl << " Zahlen wurden auf " << unterteilungen << " Bins verteilt; \n";
	std::cout << "# Maximum: " << max << "\n";
	std::cout << "# Minimum: " << min << "\n";
	std::cout << "#Bin Nr" << "\t" << "Anzahl" << "\n";
	for( unsigned int i = 0; i < unterteilungen; i++ )
		std::cout << i << "\t" << histo[i] << "\n";

}


	
