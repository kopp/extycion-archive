/**************************



Version-history
03 : Parameter werden ueber Kommandozeile uebergeben:
	$ ./a.out <anzahl> <quelldatei>
	test der parameter, ob zahl /  dateinamen.
	standard: 250, "data"
04 : finde groesste Zahl
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

  // find biggest number
  double biggest = 0;
  i = 0;
  while ( zahlen[i++] )
  {
  	if ( biggest < zahlen[i] )
	{
		biggest = zahlen[i];
	}
  }
  cout << "Groesste Zahl ist: " << biggest << "\n";



  return 0;
}  
