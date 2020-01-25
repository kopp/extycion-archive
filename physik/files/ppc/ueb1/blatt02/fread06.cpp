/**************************



Version-history
03 : Parameter werden ueber Kommandozeile uebergeben:
	$ ./a.out <anzahl> <quelldatei>
	test der parameter, ob zahl /  dateinamen.
	standard: 250, "data"
04 : findet groesste Zahl
05 : tauscht zwei zahlen sodass eine grosse zahl nach `unten'
	in der liste wandert und gibt die Liste aus
06 : sortiert alle Zahlen via bubblesort und gibt sie in einer 
	Datei aus, die man als drittes Argument angeben muss
	$ ./a.out <anzahl> <quelldatei> <zieldatei>
                                            **********************/


#include <fstream> 
#include <iostream>
#include<cstdlib>
using namespace std;




 
int main(int argc, char** argv){


  //// Daten aus Liste einlesen
  // Errorhandling
  int foo;
  if ( argv[1] == NULL )
  {
	  foo = 250;
	  // Bei meinem gcc scheint es so zu sein, dass atoi NULL
	  // zurueckgibt, wenn nichts eingegeben wird...
  }
  else
  {
	  foo = atoi(argv[1]);
  }
  const int anzahl =  (foo==0 ? 250 : foo) ;

  ifstream  input(argv[2]);  // opens the file given in 2. argument
  if ( ! input.good() ) {
  	input.close();
	input.open("data"); 
	cout << "Datei ist data \n";
  }
  else {
	  cout << "Datei ist " << argv[2] << "\n";
  }
		       
  //// Declaration
  double zahlen[anzahl];


  //// from file to array
  int i = 0;
  while ( i < anzahl )
  {
  	input >> zahlen[i++];
  }
  input.close();
  // Test if everyting went well
  cout << anzahl << " Werte eingelesen ... hier eine Kostprobe:\n";
  cout << zahlen[0] << "\t" << zahlen[anzahl/2] << "\t" << zahlen[anzahl-1] << "\n";



  //// SORT

  // switch numbers: the bigger the later
  // 1. run: go throug (1..n), 2. run: go through (1..n-1), ... (1,2)
  double temp;
  for ( int j = anzahl; j > 1; j--)
  {
	  cout << "Durchlauf durch die ersten " << j << " Eintraege gestartet... \n";
	  for ( int i = 0; i < j ; i++)
	  {
		  if ( ( zahlen[i] > zahlen[i+1] ) && ( (i+1) < anzahl ) )
		  {
			  cout << zahlen[i] << " (i = " << i << ") ist groesser als " << zahlen[i+1] << "( i = " << i+1 << ") \n";
			  temp = zahlen[i];
			  zahlen[i] = zahlen[i+1];
			  zahlen[i+1] = temp;

		  }
	  }
	  cout << "Durchlauf durch die ersten " << j << " Eintraege beendet... \n";
  }

  cout << anzahl << " sortiert ... hier die letzten 3 Zahlen (letzte ist groesste):\n";
  cout << zahlen[anzahl-3] << "\t" << zahlen[anzahl-2] << "\t" << zahlen[anzahl-1] << "\n";

  //// OUTPUT
  // console
  cout << "Und hier alle Zahlen: \n";
  for (int i = 0; i < anzahl; i++) cout << zahlen[i] << "\n";

  //file
  ofstream ausgabedatei;
  ausgabedatei.open(argv[3]);
  if ( ! ausgabedatei.good() )
  {
	  ausgabedatei.close();
	  ausgabedatei.open("fread06_ausgabe");
	  cout << "Ausgabedatei ist ''fread06_ausgabe'' \n" ;
  }
  else
  {
	  cout << "Ausgabedatei ist ''" << argv[3] << "'' \n" ;
  }

  for (int i = 0; i < anzahl; i++)
  {
	  ausgabedatei << zahlen[i] << "\n";
  }
  ausgabedatei.close();






  return 0;
}  
