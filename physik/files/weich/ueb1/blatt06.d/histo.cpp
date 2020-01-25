#include<cstdio>
#include<gsl/gsl_histogram.h>
#include<cmath>
using std::log ;


int main()
{
	// // histogramm eigenschaften // //
	// bins
	int anz_bins = 100 ;
	// range
	float xmin =  -0.1 ;
	float xmax =   0.7 ;
	// initialisieren
	gsl_histogram * histo =  gsl_histogram_alloc( anz_bins ) ;
	gsl_histogram_set_ranges_uniform(histo, xmin, xmax) ;
		
	

	// // daten einlesen ----------------
	FILE * fh = std::fopen( "tirm.data" , "r" ) ;

	float* time = new float ; 
	float* intens  = new float ;
	double z_minus_z0 = 0 ;

	while( ! std::feof( fh ) )
	{
		// lesen
		std::fscanf( fh , "%f\t%f\n" , time , intens ) ;
		// berechnungen
		// WICHTIG: Hier wird 1/\beta = 0.147 \mu m verwendet! z_minus_z0 ist also im \mu m.
		z_minus_z0 = - 0.147 * log( *intens ) ;
		// zu histogramm hinzufuegen
		gsl_histogram_increment(histo, z_minus_z0 ) ;
	}
	delete time ;
	delete intens ;
	std::fclose( fh ) ;
	// ----------------------------------
	
	// normieren
	float sum = gsl_histogram_sum( histo ) ;
	gsl_histogram_scale(histo, 1./sum ) ;



	// // ausgabe in datei
	FILE * of = std::fopen( "tirm_histo.data" , "w" ) ;
	gsl_histogram_fprintf( of , histo , "%f", "%f" ) ;
	
	// aufraeumen
	gsl_histogram_free( histo ) ;
}
