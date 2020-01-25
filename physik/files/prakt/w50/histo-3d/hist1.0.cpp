/*************************8
 * xy-Histogramme
 *
 * Michael Kopp
 *
 * Erstellt aus einer Liste, in der einzelne (2-dim) Punkte angegeben sind,
 * Daten fuer ein Dreidimensionales Histogramm: Die xy-Ebene wrid in Quadrate
 * aufgeteilt und in diesen wird jeweils gezaehlt, wie viele Punkte im Quadrat
 * liegen. Ausgegeben wird eine Datei, die zu jedem Quadrat (x-y-Koord) die
 * Anzahl von Datenpunkten angibt.
 *
 * Eingabetyp;
 * <x> <tab> <y> <newline>
 *
 * Ausgabetyp:
 * <x> <tab> <y> <tab> <anzahl> <newline>
 *
 * Verwendung: 
 * . Im Quelltext passt man Anzahl und grenzen der Quadrate an
 * . Kompilieren
 * . Das Programm nimmt die Eingabe von stdin entgegen; man kann sie unter
 * Linux/Apple mit 
 * 	cat input | a.out > output
 * verarbeiten. Unter Windows geht (vermutlich)
 * 	a.out < input
 * wobei man dann den output vom Bildschirm in eine textdatei kopieren muss.
 * . den output kann man mit gnuplot verarbeiten.
 *
 *
 *                                                          **************/

#include<iostream>
using namespace std;



int main()
{

	// so viele bins fuer zeile und spalte
	const int n = 15;
	const int m = 15;

	// intervallgrenzen
	// a untere, b obere
	const float xa = 178;
	const float xb = 192;
	const float xba = xb - xa;
	const float ya = 448;
	const float yb = 456;
	const float yba = yb - ya;

	// tabelle
	int counts[n][m];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			counts[i][j]=0;
		}
	}

	// temp
	float xf,yf;
	int xi, yi;

	//verarbeitung
	while ( cin >> xf >> yf )
	{
		xi = ((xf - xa)/xba * n);
		yi = ((yf - ya)/yba * m);

		counts[xi][yi]++;

		//cout << xi << "\t" << yi << "\t" << counts[xi][yi] << "\n";
	}

	// output
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
		cout << i << "\t" << j << "\t" << counts[i][j] << "\n";
		}
	}
	
}
