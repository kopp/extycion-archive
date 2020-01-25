/*
 * ising2d.cpp
 *
 * Michael Kopp
 *
 * The ising model using Metropolis' algorithm for a 2D square magnet.
 *
 * compile:
 * to simply use the code issue
 *  $ g++ `gsl-config --libs`  -O2 -DHAVE_INLINE -o ising2d  ising2d.cpp
 * for debugging use
 *  $ g++ -Wall `gsl-config --libs` -O0 -ggdb -DHAVE_INLINE -o debug_ising2d  ising2d.cpp
 * IMPORTANT: This program requires the Gnu Scientific Library (GSL) to compute
 * random numbers. If it's not installed, you'll have to substitute some oter
 * random number generator.
 *
 * usage:
 * The important parameters can be controlled using command line switches. For
 * each vairable, reasonable default settings are hardcoded.
 * Use the `-h' switch to get an overview of the switches.
 *
 * output:
 * Also see the `-h' switch.
 * 
 *
 */

#include"board.h"
#include<cstdio>
using std::printf ;
using std::fprintf ;
using std::sprintf ;
#include<gsl/gsl_rng.h>
#include<cmath>
using std::exp ;
using std::abs ;
#include<cstdlib>
using std::atoi ;
using std::atof ;


// metropolis algorithm for one timestep
// returns number of flipped spins
inline int metropolis( board& foo , const double temp , gsl_rng* gen ) 
{
	int flipped = 0 ;
	unsigned int L = foo.get_length() ;
	for( unsigned int i = 0 ; i < L ; i++ )
	{
		for( unsigned int j = 0 ; j < L ; j++ )
		{
			double delta = foo.Delta_E( j , i ) ;
			if( delta < 0 ) // always flip if it minimizes energy
			{
				foo.flip( j , i , true ) ;
				flipped ++ ;
			}
			else // flip with p = exp(-delta/temp) if it increases energy
				if( exp( - delta / temp ) > gsl_rng_uniform( gen ) ) 
				{
					foo.flip( j , i , true ) ;
					flipped++ ;
				}
		}
	}

	return flipped ;
}


void print_help()
{
	printf( "ising2d\n=======\n\nMichael Kopp\n\n" ) ;
	printf( "Simple model of a magnet using Metropolis' algorithm\n\n" ) ;
        printf( "== Command line switches ==  \n") ;
        printf( "In square brackets the type of data to follow the switch and the default value is given \n") ;
        printf( "A ' - ' indicates, that this switch does not expect any argument \n") ;
        printf( "A 'disabled' or 'enabled' means that the _feature_ is per default dis-/enabled \n") ;
        printf( "A sanity check for each parameter is performed\n\n") ;
	printf( "\t - help - \n" ) ;
        printf( "-h \t print this help and exit \n") ;
	printf( "\t - physical parameters - \n" ) ;
        printf( "-L \t set length L [int,1000] \n") ;
        printf( "-d \t set degree of positive magnetisation [double,0.5] \n") ;
        printf( "-T \t set temperature in kT/J [double,2.0] \n") ;
	printf( "\t - timesteps - \n" ) ;
        printf( "-N \t set number of maximal timesteps [int,10000] \n") ;
        printf( "-e \t set numbers of timesteps to equilibrate [int,500] \n") ;
        printf( "   \t only then the collection of data for averages will be started \n") ;
	printf( "\t - output - \n" ) ;
        printf( "-pm \t print every pm-th output to 'current.data' [int,50] \n") ;
        printf( "-im \t print every im-th output to ppm-file 'magnXXXXXX.ppm' [int,timesteps_max/50] \n") ;
	printf( "\t - load/save -\n" ) ;
        printf( "-if \t save initial state to file [string,initialmagnet.save] \n") ;
        printf( "-sf \t save final state to file [string,magnet.save] \n") ;
        printf( "-lf \t load initial state from this stat [string,magnet.save] \n") ;
        printf( "-nl \t disable loading from file [ - ,disabled] \n") ;
        printf( "-dl \t enable loading from file [ - ,disabled] \n") ;
        printf( "-ni \t disable saving initial state [ - ,enabled] \n") ;
        printf( "-nf \t disable saving final state [ - ,enabled] \n") ;
	printf( "\n\n== Output == \n" ) ;
	printf( "- current.data: Outputs every pm-th step (default every 50-th). If the program\n" ) ;
	printf( "is invoked several times, the new data is appended to current.data. Each time a\n" ) ;
	printf( "descriptive header is printed with a leading `#' so the output is gnuplot\n" ) ;
	printf( "compatible. Each time the output consists of \n" ) ;
	printf( "   # timestep, current m, current e, just changed, temp, L, deg\n" ) ;
	printf( "- magnXXXXXX.ppm: Every im-th step (default 50 images at total) a PPM image of\n" ) ;
	printf( "the current state is written to file.\n" ) ;
	printf( "- *.save: The state of the magnet at the beginning/end is written to file.\n" ) ;
	printf( "Final output: Outputs mean (absolute) magnetisation and mean energy per unit\n" ) ;
	printf( "volume (in 2D per 1/L^2). This data is collected only after the timespan set by\n" ) ;
	printf( "`-e' is exceeded. Additionally the initial and final energy are outputted (this\n" ) ;
	printf( "can be helpful to check, if a state has been loaded sucessfully...)\n" ) ;
	printf( "\n\n== Loading == \n" ) ;
	printf( "it can be read using either the `-dl' or the `-lf <filename>' switch.\n" ) ;
	printf( "IMPORTANT: It's only possible to load files with the same L. So check the L of \n" ) ;
	printf( "the saved data, e.g. using \n" ) ;
	printf( "  $ head -n 1 <filename>.save\n" ) ;
	printf( "if a file is loaded.\n" ) ;
	printf( "This is possible due to the constructor board(L,<filename>) in board.h\n" ) ;
	printf( "\n\n" ) ;
	printf( "For further details and `documentation' see the source code\n" ) ;

}

int main( int argc , char* argv[] )
{
	// // parameter // //
	// length/width of the magnet
	int L = 1000 ;
	double V = L*L ;
	// degree of positive magnetisation
	double deg = 0.5 ;
	// temperature 
	double Temp = 2. ;
	// number of timesteps
	// one timestep means to calculate and flip/not flip every single step in the magnet.
	unsigned int timesteps_max = 10000 ;
	// timesteps to equilibrate
	// start collecting data for average values only after this period
	unsigned int timesteps_equil = 500 ;
	// -- output --
	// print output every ... steps [set 0 to disable print output]
	unsigned int print_mod = 50 ;
	// output an image every ... steps [set 0 to disable image output]
	unsigned int image_mod = timesteps_max / 50 ;
	// -- load/save --
	// save after run to this file
	char * savefilename ;
	char default_savefilename[] = "magnet.save" ;
	savefilename = default_savefilename ;
	// save initial magnet to this file
	char * initialsavename ;
	char default_initialsavename[] = "initialmagnet.save" ;
	initialsavename = default_initialsavename ;
	// save magnet
	bool save_final = true; 
	// save magnet directly after initialisation
	bool save_initial = true ;
	// load from this file
	char * loadfilename;
	char default_loadfilename[] = "magnet.save" ;
	loadfilename = default_loadfilename ;
	// load from file or generate new one?
	bool load_from_file = false ;

	// // command line arguments // //
	for( char** pointer = argv ; *pointer ; pointer++ )
        {
                if( std::strcmp( *pointer , "-h" ) == 0 ) { print_help() , std::exit(0) ; }
                if( std::strcmp( *pointer , "-L" ) == 0 ) { L = atoi( *(++pointer) ); }
                if( std::strcmp( *pointer , "-d" ) == 0 ) { deg = atof( *(++pointer) ); }
                if( std::strcmp( *pointer , "-T" ) == 0 ) { Temp = atof( *(++pointer) ); }
                if( std::strcmp( *pointer , "-N" ) == 0 ) { timesteps_max = atoi( *(++pointer) ); }
                if( std::strcmp( *pointer , "-e" ) == 0 ) { timesteps_equil = atoi( *(++pointer) ); }
                if( std::strcmp( *pointer , "-pm" ) == 0 ) { print_mod = atoi( *(++pointer) ); }
                if( std::strcmp( *pointer , "-im" ) == 0 ) { image_mod = atoi( *(++pointer) ); }
                if( std::strcmp( *pointer , "-if" ) == 0 ) { initialsavename =  *(++pointer) ; save_initial = true ; }
                if( std::strcmp( *pointer , "-sf" ) == 0 ) { savefilename =  *(++pointer) ; save_final = true ; }
                if( std::strcmp( *pointer , "-lf" ) == 0 ) { loadfilename =  *(++pointer) ; load_from_file = true ; }
                if( std::strcmp( *pointer , "-nl" ) == 0 ) { load_from_file = false ; } 
                if( std::strcmp( *pointer , "-dl" ) == 0 ) { load_from_file = true  ; } 
                if( std::strcmp( *pointer , "-ni" ) == 0 ) { save_initial = false ; } 
                if( std::strcmp( *pointer , "-nf" ) == 0 ) { save_final = false ; } 
        }

	// // check integrity // //
	if( deg < 0 ) deg = 0 ;
	if( deg > 1 ) deg = 1 ;
	if( Temp < 0 ) Temp = 0 ;
	if( timesteps_equil > timesteps_max ) timesteps_equil = timesteps_max / 2 ;
	if( print_mod > timesteps_max ) print_mod = timesteps_max / 200 ; // make 200 prints
	if( image_mod > timesteps_max ) image_mod = timesteps_max / 20 ; //  take 20 images

	// // initialize RNG // //
	gsl_rng_env_setup() ;
	const gsl_rng_type * typ = gsl_rng_default ;
	gsl_rng * generator = gsl_rng_alloc( typ ) ;

	// // initialize magnet // //
	board magnet( L , 0 , 0 ) ;
	if( load_from_file )
	{
		// board magnet( L , loadfilename ) ;
		board foo( L , loadfilename ) ;
		magnet = foo ;
	}
	else
	{
		// board magnet( L , deg , gsl_rng_uniform( generator ) ) ;
		board foo( L , deg , gsl_rng_uniform( generator ) ) ;
		magnet = foo ;
	}
	double initial_energy = magnet.get_energy() ;
	if( save_initial ) magnet.save_to_file( initialsavename ) ;
	
	// // initialize output // //
	// current: Output for every print_med steps
	FILE * op = std::fopen( "current.data" , "a" ) ;
	fprintf( op , "# timestep, current m, current e, just changed, temp, L, deg \n" ) ;

	// // averaging values // //
	double m_avg = 0 ; // mean magnetisation
	double e_avg = 0 ; // mean energy


	// counter and stuff
	int image = 0 ;
	char imagename[20] ;


	// // time loop // //
	for( unsigned int t = 0 ; t < timesteps_max ; t++ )
	{
		// actual Metropolis algorighm
		int changed = metropolis( magnet , Temp , generator ) ;

		// averaging 
		if( t > timesteps_equil )
		{
			e_avg += magnet.get_energy() ;
			m_avg += abs( magnet.get_magn() ) ;
		}

		// // output 
		// print
		if( print_mod != 0 and t % print_mod == 0 )
		{
			fprintf( op , "%i \t%f \t%f \t%i \t%f \t%i \t%f \n" , t , magnet.get_magn()/V , magnet.get_energy()/V , changed , Temp , L , deg  ) ;
		}
		if( image_mod != 0 and t % image_mod == 0)
		{
			sprintf( imagename , "magn%06i.ppm" , image )  ;
			magnet.print_ppm( imagename ) ;
			image ++ ;
		}

	}

	// // finalize // //
	double final_energy = magnet.get_energy() ;
	if( save_final) magnet.save_to_file( savefilename ) ;

	// // renormalize averaging // //
	e_avg /= ( V * (timesteps_max - timesteps_equil) ) ;
	m_avg /= ( V * (timesteps_max - timesteps_equil) ) ;

	// // output // //
	printf( "L: %5i, T: %8.6f, mean energy: %.7e, mean magnetisation: %.7e\ninitial energy: %6.0f, final energy: %6.0f\n" , L , Temp , e_avg , m_avg , initial_energy , final_energy ) ;

		
	// // clean up // //
	std::fclose( op ) ;
	gsl_rng_free( generator ) ;

}
