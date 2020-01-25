#include <fstream> 
#include <iostream>
using namespace std;
 
int main(){
  ifstream  input("data");   // opens the file 'filename' in the
                       //   current directory 

  double    d;         // declare a floating point variable
  double zahlen[500];
  input  >> d;         // reads the first double from file, skips whitespace
  cout   << d;         // print d to the terminal 
  cout << " ist die Erste Zahl... \n";


  int i = 0;
  while ( i < 500 )
  {
  	input >> zahlen[i++];
  }

  cout << "Eingelesen ... \n";

  cout << zahlen[0] << "\t" << zahlen[100] << "\t" << zahlen[499] << "\n";
  return 0;
}  
