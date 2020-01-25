/********************
 * simple implementation of the quicksort algorithm
 * Michael Kopp
 *
 * currentyl no user interaction is possible.
 * the data is read from the file to be specified at the beginning of main;
 * the first anzahl lines where anzahl can be specified under `declarations'
 * (see after #include...)
 *
 * Verbose output about the sorting-Progress is given
 *
 * the on-screen output can be used to feed gnuplot as every comment is
 * marked with a `#' at the beginning; output of the numbers is preceeded
 * by `##'.
 *
 * To visualize the sorting process, after every switch the complete
 * list is printed out: the outputs are proceeded by `=== begin output ===' 
 * and ended by `=== end   output ==='. Split the output via
 * 	$ csplit --suffix-format=%06d <outfile> /"=== end   output ==="/ {*}
 * to remove preceding `##' in front of plottable data use
 * 	$ cat foo | sed s/^##// > bar
 *
 * to plot: write a small gnuplot script like `plotten'
 *
 * 	unset key
 * 	set terminal gif
 * 	set output 'aktplot.gif'
 * 	plot 'aktplot'
 *
 * and run all files through gnuplot using a bash script like
 *
 * 	for f in xx*
 * 	do
 * 		mv $f aktplot
 * 		gnuplot plotten
 * 		mv aktplot.gif $f.gif
 * 		mv aktplot $f
 * 	done
 *
 * afterwards combine all gifs with a tool like gifsicle
 * 	$ gifsicle --delay xx*.gif > animation.gif
 *
 *                                                              
 *                                                              **************/
#include<iostream>
#include<fstream>
//using namespace std;

//// declarations
const int anzahl = 750; //750;
double zahlen[anzahl];
double unveraendert[anzahl];
double back[anzahl];


void backup()
{
	for ( int i = 0; i < anzahl; i++)
	{
		back[i] = zahlen[i];
	}
}


void print()
{
	std::cout << "#=== begin output ===\n";
	for ( int i = 0; i < anzahl; i++)
	{
		std::cout << "## " << i << "\t" << back[i] << "\t" << zahlen[i] << "\n";
	}
	std::cout << "#=== end   output ===\n";
}
	

bool quicksort(double* left, double* right) 
	// get left and right index of the set inside zahlen[] to sort
	// pivot element is right one
	// return true if string has length 1 or 2 and is ordered, false otherwise
{
	std::cout << "# Uebergebene Werte: " << left << " (" << *left << ") und " << right << " (" << *right << "); das sind " << right-left+1 << " Elemente" << "\n";
	if ( left >= right ) // sorting done
	{
		std::cout << "#  Nur noch ein Element uebergeben -- Rekursion endet hier \n";
		return true;
	}
	else
	{
		// problems with this actual swap-mechanism for lists with only two elements
		if (  left+1 == right  ) // only 2 elements left
		{
			if ( *left <= *right ) // already ordered
			{
				std::cout << "#  Nur noch zwei geordnete Elemente (" << *left << ") und (" << *right << ")  -- Rekursion endet hier \n";
				return true;
			}
			else // left element is bigger
			{
				std::cout << "#  Nur noch zwei ungeordnete Elemente (" << *left << ") und (" << *right << ") werden geordnet -- Rekursion endet hier \n";
				double tmp = *right;
				*right = *left;
				*left = tmp;
				return true;
			}
		}

		// Start actual quicksort
		double* pivot_point = right; 
		double pivot_val = *right;
		for ( double* i = left; i < pivot_point; i++ ) // i is pointer!
			// sort all elements `left' of pivot_pointer -- the pivot
			// is moged to the left
		{
			if( *i > pivot_val )
			{
				std::cout << "# " << *i << " ist groesser als das Pivotelement " << pivot_val << "\n";
				//rearrange: i must be right of pivot
				//therefore switch i with element right of
				//pivot and move pivot one to the left
				backup();
				*pivot_point = *i;
				*i = *(--pivot_point);
				*pivot_point = pivot_val;
				print();

				//check the same data again (the newly inserted
				//might be bigger than pivot_val
				i--;
			}
			// else : do nothing
		}

		std::cout << "#Rekursion startet hier: \n";
		quicksort(left, pivot_point-1);
		quicksort(pivot_point+1,right);
		return false;
	}
}
	

int main()
{

	//// input ////
	std::ifstream eingabe;//("data");
	eingabe.open("data");

	// zahlen einlesen //
	for ( int i = 0; i < anzahl; i++)
	{
		eingabe >> zahlen[i];
	}
	
	//make copy to compare
	for ( int i = 0; i < anzahl; i++)
	{
		unveraendert[i] = zahlen[i];
	}

	std::cout << "#starte quicksort \n";
	quicksort(&zahlen[0], &zahlen[anzahl-1]);


	std::cout << "#Quicksort beendet! Hier endgueltige Ausgabe: \n\n\n";

	for ( int i = 0; i < anzahl; i++)
	{
		std::cout << i << "\t" << unveraendert[i] << "\t" << zahlen[i] << "\n";
	}
}
