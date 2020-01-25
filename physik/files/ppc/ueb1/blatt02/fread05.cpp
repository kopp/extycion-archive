/**************************



Version-history
03 : Parameter werden ueber Kommandozeile uebergeben:
	$ ./a.out <anzahl> <quelldatei>
	test der parameter, ob zahl /  dateinamen.
	standard: 250, "data"
04 : findet groesste Zahl
05 : tauscht zwei zahlen sodass eine grosse zahl nach `unten'
	in der liste wandert und gibt die Liste aus
                                            **********************/


#include <fstream> 
#include <iostream>
#include<cstdlib>
using namespace std;




 
int main(int argc, char** argv){


  //// Daten aus Liste einlesen
  int foo = atoi(argv[1]);
  // Errorhandling
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
		       
  double zahlen[anzahl];


  //// from file to array
  int i = 0;
  while ( i < anzahl )
  {
  	input >> zahlen[i++];
  }
  // Test if everyting went well
  cout << anzahl << " Werte eingelesen ... hier eine Kostprobe:\n";
  cout << zahlen[0] << "\t" << zahlen[anzahl/2] << "\t" << zahlen[anzahl-1] << "\n";



  //// SORT

  // switch numbers: the bigger the later
  double temp;
  for ( int i = 0; i < anzahl ; i++)
  {
  	if ( ( zahlen[i] > zahlen[i+1] ) && ( (i+1) < anzahl ) )
	{
		cout << zahlen[i] << " (i = " << i << ") ist groesser als " << zahlen[i+1] << "( i = " << i+1 << ") \n";
		temp = zahlen[i];
	        zahlen[i] = zahlen[i+1];
		zahlen[i+1] = temp;

	}
  }

  cout << anzahl << " sortiert ... hier die letzten 3 Zahlen (letzte ist groesste):\n";
  cout << zahlen[anzahl-3] << "\t" << zahlen[anzahl-2] << "\t" << zahlen[anzahl-1] << "\n";

  cout << "Und hier alle Zahlen: \n";
  for (int i = 0; i < anzahl; i++) cout << zahlen[i] << "\n";





  return 0;
}  
