/**************************



Version-history
03 : Parameter werden ueber Kommandozeile uebergeben:
	$ ./a.out <anzahl> <quelldatei>
	test der parameter, ob zahl /  dateinamen.
	standard: 250, "data"
                                            **********************/


#include <fstream> 
#include <iostream>
#include<cstdlib>
using namespace std;




 
int main(int argc, char** argv){
  int foo = atoi(argv[1]);
  const int anzahl =  (foo==0 ? 250 : foo) ;

  ifstream  input(argv[2]);  // opens the file 'filename' in the
                       //   current directory
  if ( ! input.good() ) {
  	input.close();
	input.open("data"); 
	cout << "Datei ist data \n";
  }
  else {
	  cout << "Datei ist " << argv[2] << "\n";
  }
		       
  double    d;         // declare a floating point variable
  double zahlen[anzahl];
  input  >> d;         // reads the first double from file, skips whitespace
  cout   << d;         // print d to the terminal 
  cout << " ist die Erste Zahl... \n";


  int i = 0;
  while ( i < anzahl )
  {
  	input >> zahlen[i++];
  }

  cout << anzahl << " Werte eingelesen ... hier eine Kostprobe:\n";

  cout << zahlen[0] << "\t" << zahlen[anzahl/2] << "\t" << zahlen[anzahl-1] << "\n";
  return 0;
}  
