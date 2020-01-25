/* 
 * wave2d.cpp
 * derived from wave.cpp
 *
 * Michael Kopp
 *
 * Solve the two dimensional wave equation 
 *
 * output: 
 * many files which can be processed as video
 *
 */


#include<cstdio>
#include<iostream>
#include<cmath>
using std::sin ;
using std::cos ;
using std::exp ;
using std::sqrt ; // ?
using std::abs ;
#include<cstring>
using std::strcmp ;

inline double sqr( const double x )
{
	return x * x ;
}


// // global variables // //
// length/width of the square
double x_max ;
double c ;
/* 
double c( const double x , const double y ) 
{
	if( x > y ) return 0.5 ;
	else return 1. ;
}

inline double r( const double x , const double y , const double dx , const double dt ) 
{
	return sqr( c(x,y) * dt / dx ) ;
}
*/

// simple wave
inline double propagating_wave( const double x , const double y , const double t ) 
{
	// wave vector
	double k_x = 10. ; double k_y = 0. ; // propagate in x direction
	// omega
	double omega = c * sqrt( sqr(k_x)+sqr(k_y) ) ; // standard dispersion relation
	// phase
	double phase = k_x * x + k_y * y - omega * t ; // simple plane wave
	// amplitude
	/* limited width
	double width = x_max / 20. ;
	double height = 1./15. ;
	double A = height * sin(M_PI*(y-x_max/2.)/width) * ( abs( y-x_max/2.) <= width ) ;
	*/
	double A = 0.1 ;
	// finally:
	return A * sin( phase ) ;
}



int main(int argc, char* argv[])
{

	// // parameters // // 
	// length/width of the square
	x_max = 5. ;
		// int n_x = 21 ;
	// space step
		// double dx = x_max / n_x ;
	double dx = 0.05 ;
	// discretisation: Number of bins
	int n_x = x_max / dx ;
	// time to examine
	double t_max = 7.0 ;
	// timestep
	double dt = 0.001 ;
	// number of timesteps
	int n_t = t_max / dt ;
	// phase speed
	c = 1.0 ;
	// output n_op time steps at all
	int n_op = 500 ;

	
	// // flags // //
	/* output
	bool output_many_files = false ;
	*/

	/* // parse command line arguments // //
	for( char** point = argv; *point ; point++ )
	{
		if( std::strcmp(*point,"-m") == 0 ) output_many_files = true ; 
	}
	*/

	
	if( n_op > n_t ) n_op = n_t ; // don't try to output more than what's computed


	// // derived parameters // //
	const double r = c*c*dt*dt/dx/dx ; // sqr( c * dt / dx ) ; // in conflict with the function r(..)


	// // system // //
	double** phi_new   = new double*[ n_x+1 ] ;
	double** phi_old   = new double*[ n_x+1 ] ;
	double** phi_older = new double*[ n_x+1 ] ;
	for( int i = 0 ; i < n_x+1 ; i++ )
	{
		phi_new[i] =   new double[ n_x+1 ] ;
		phi_old[i] =   new double[ n_x+1 ] ;
		phi_older[i] = new double[ n_x+1 ] ;
	}

	// // imitial conditions // //
	// choose freely
	/* gauss */
	for( int i = 1 ; i < n_x ; i++ )
	for( int j = 1 ; j < n_x ; j++ )
	{
		// gaussian bell:
		// phi_older[i][j] = exp( - ( sqr(dx*i-x_max/2.) + sqr(dx*j-x_max/2.) ) / 0.005 ) * ( (sqr(dx*i-x_max/2.)+sqr(dx*j-x_max/2.)) <= sqr(.25) ) ;
		// propagating wave:
		phi_older[i][j] = propagating_wave( i * dx , j * dx , 0. ) ;
	}


	// // first timestep // //
	for( int i = 1 ; i < n_x ; i++ )
	for( int j = 1 ; j < n_x ; j++ )
	{
		// //  d phi / d t ( t = 0 ) = 0 : 
		// sophisticated:
		phi_old[i][j] = 0.5*r*( phi_older[i-1][j]+phi_older[i+1][j]+phi_older[i][j-1]+phi_older[i][j+1] ) + (1-2.*r)*phi_older[i][j] ;
		// simple:
		// phi_old[i][j] = phi_older[i][j] ;

		// propagating wave:
		phi_old[i][j] = propagating_wave( i * dx , j * dx , dt ) ;
	}


	// // boundary conditions // //
	for( int i = 0 ; i < n_x+1 ; i++ )
	{
		phi_older[i][0]   = 0 ;
		phi_older[i][n_x] = 0 ;
		phi_older[0][i]   = 0 ;
		phi_older[n_x][i] = 0 ;
		phi_old[i][0]   = 0 ;
		phi_old[i][n_x] = 0 ;
		phi_old[0][i]   = 0 ;
		phi_old[n_x][i] = 0 ;
		phi_new[i][0]   = 0 ;
		phi_new[i][n_x] = 0 ;
		phi_new[0][i]   = 0 ;
		phi_new[n_x][i] = 0 ;
	}
	


	// debug
	std::printf( "# x <= %6.5f , dx = %6.5f , n_x = %6i , t <= %6.5f , dt = %6.5f , n_t = %6i , c = %6.5f , r = %6.5f \n " , x_max , dx , n_x , t_max , dt , n_t , c , r ) ;


	// // timelooop // //
	for( int t = 0 ; t < n_t ; t ++ )
	{
		for( int i = 1; i < n_x; i++ )
		for( int j = 1; j < n_x; j++ )
		// for( int i = n_x-2; i > 0; i-- )
			// phi_new[i] = r * ( phi_old[i+1] + phi_old[i-1] ) + 2.*(1.-r)*phi_old[i] - phi_older[i] ;
			phi_new[i][j] = r*( phi_old[i-1][j]+phi_old[i+1][j] + phi_old[i][j-1]+phi_old[i][j+1] ) + 2.*(1-2.*r)*phi_old[i][j] - phi_older[i][j] ;

		// interchange old/new/older...
		// double* foo = phi_older ;
		double** foo = phi_old ;
		phi_old = phi_new ;
		phi_older = foo ;
		phi_new = phi_older ;


		// output 
		if( t % (n_t/n_op) == 0 )
		{
			// output one file for each time
			// static int opnr = 0 ; // sequentially numbered output -- use opnr++ in sprintf(outputname...
			char* outputname = new char[18] ;
			std::sprintf( outputname , "txp2d%010i.data" , t ) ; // filename has 10 digits forming `t'
			FILE * filehandle;
		        filehandle = std::fopen( outputname , "w" ) ;
			for( int i = 0 ; i < n_x+1; i++ )
			{
				for( int j = 0 ; j < n_x+1; j++ )
				{
					std::fprintf( filehandle , "%.6e \t %.6e \t %.6e \n" , i * dx , j * dx , phi_old[ i ][ j ] ) ;
				}
				std::fprintf( filehandle , "\n" ) ; // draw one empty line: gnuplot will like this ;-)
			}
			std::fclose( filehandle ) ;

		}


	}

}


