/*********************
 *
 * Stack basierter Taschenrechner
 *
 * Michael Kopp
 *
 * Um zahlen einzugeben, stellt man ihnen ein Komma `,' voran; ausge-
 * nommen die _erste_ Zahl nach Programmstart.
 *
 * Um eine Rechenoperation einzugeben, gibt man sie ein. Der Taschenrechner 
 * rechnet stets die beiden letzten eingegebenen Zahlen zusammen und zwar 
 * 	<letzte> [operator] <vorletzte>
 * so liefert
 * 	3 ,2 - =
 * das Ergebnis -1, da 2 - 3 gerechnet wird. So darf man also _nicht_
 * 	0 ,4 / =
 * rechnen, da das eine Division durch 0 ist.
 *
 * Der Taschenrechner unterstuetzt:
 * 	+ - * / ^ (Potenz) % (Modulo)
 * Um das Ergebnis anzuzeigen = <Enter> eingeben.
 *
 * Errorhandling:
 * 	wird durch 0 geteilt wird bei der Teilung 2000000000 ausgegeben
 * 	wird eine Rechenoperation nicht erkannt, bricht der Rechner ab.
 *
 *
 * Funktionsweise:
 * 	1. Zahl wird eingelesen und auf Stack gelegt
 * 	2. Operator wird eingelesen
 * 		bei `,': weitere Zahl wird eingelesen und
 * 			auf Stack gelegt -> 2.
 * 		bei `=': Ergebnis wird aus Stack geholt und 
 * 			ausgegeben -> Programmende
 * 		bei Rechenoperatoren: Letzte beide werden aus Stack ge-
 * 			holt und verrechnet; ergebnis kommt `oben' auf Stack
 * 			-> 2.
 * 		bei unerkanntem Zeichen: Programmende.
 *
 *                                                           *************/





#include<iostream>
using namespace std;


///////////globale Variablen ///////////
int zahlen[137]; //Stack
int pointer = 0; //zeigt immer auf die naechste _freie_ Stelle im Stack


///////// Funktionen fuer Stack-Verwaltung ///////////
void drauflegen(int foo)
{
	zahlen[pointer++] = foo;
}

int holen()
{
	return zahlen[--pointer];
}


/////////// Rechenfunktionen ////////////
int power(int lhs, int rhs)
{
	int tmp = 1;
	for (int i = 0; i < rhs; i++)
	{
		tmp *= lhs;
	}
	return tmp;
}

int teilen(int lhs, int rhs)
{
	if ( lhs != 0 ) return rhs/lhs;
	else return 2000000000;
}



////////// Hauptprogramm //////////
int main()
{

	// Variablen, die fuer jeden Durchlauf gebraucht werden
	char ch;
	int nr;


	// erste Zahl darf noch ohne `,' eingegeben werden
	cin >> nr;
	drauflegen(nr);

	while (true)
	{
		cin >> ch;

		switch ( ch )
		{
			case ',' : 
				cin >> nr;
				drauflegen(nr);
				break;

			case '+' : drauflegen(holen() + holen()); break;
			case '-' : drauflegen(holen() - holen()); break;
			case '*' : drauflegen(holen() * holen()); break;
			case '%' : drauflegen(holen() % holen()); break;
			case '^' : drauflegen(power(holen(),holen())); break;
			case '/' : drauflegen(teilen(holen(),holen())); break;

			case '=' :
				cout << "\nErgebnis: " << holen() << "\n";
				return 0;
				break;

			default: 
				cout << "\nerror -- try again \n";
				return 1;
				break;
		}
	}
}
