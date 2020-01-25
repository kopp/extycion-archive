/*
 * oszi01.cpp
 *
 * Solves Schroedinger's Equation (1D, time dependent) numerically (approximatively)
 *
 * Output 
 * gnuplot style file `oszi01.data'
 * warning: output is overwritten in subsequent runs!
 *
 * Input
 * No input possible (yet?) -- parameters must be altered in the source code
 * manually
 *
 * Compile
 * g++ -O2 oszi01.cpp
 *
 * Problems:
 * - instability
 *   the program 
 * - algorithm
 *   make sure to set dx large if dt is small: dx ~ 0.1 for dt ~ 0.0001
 *
 * Michael Kopp
 *
 */

#include<complex>
using std::complex ;
#include<cstdio>
#include<cmath>
using std::exp ; 
using std::sqrt ;
using std::abs ;
#include<cstdlib> // exit()

// Constants
#define hbar 1.0
#define mass 1.0
#define I_imag (complex<double>(0,1))

// inlines
inline double sqr( const double x )
{
	return x * x ;
}


// // functions // //

// potential 
inline double V( const double x )
{
	// harmonic oscillator
	//return 0.5 * sqr( x ) ;
	// anharmonic
	return 0.5 * sqr( x ) - 0.005 * sqr(sqr(x)) ;
	// morse
	double D = 30 ; // energy well
	//return D*sqr(1-exp(-x/sqrt(2.*D))) ;
}

// first derivative
complex<double> delx( 
		const complex<double>* psi  // wave function
		, const int pos  // where the derivation etc. shall be evaluated
		, const double dx // spatial discretisation
		, const int N // length of psi 
		)
{
	if( pos == N-2 )
		return ( 11.* psi[pos] - 18.*psi[pos-1] + 9.*psi[pos-2] -2.*psi[pos-3] ) / (6. * dx ) ;
	if( pos == 1 )
		return - ( 11.* psi[pos] - 18.*psi[pos+1] + 9.*psi[pos+2] -2.*psi[pos+3] ) / (6. * dx ) ;
}


// second derivative
complex<double> delxx( 
		const complex<double>* psi  // wave function
		, int pos  // where the derivation etc. shall be evaluated
		, const double dx // spatial discretisation
		, const int N // length of psi 
		)
{
	// internal fields -- central derivation
	if( pos != 0 and pos != N-1 )
		return (psi[pos+1] - 2.*psi[pos] + psi[pos-1])/sqr( dx ) ;
	else
	{
		// boundary
		if( pos == N-1 )
		{
			//return + ( 3.*psi[pos-1] - 8.*psi[pos-2] + 7.*psi[pos-3] - 2.*psi[pos-4] )/(dx*dx) ;
			pos = N-2 ;
			return (psi[pos+1] - 2.*psi[pos] + psi[pos-1])/sqr( dx ) ;
		}
		if( pos == 0 )
		{
			//return  ( 3.*psi[pos+1] - 8.*psi[pos+2] + 7.*psi[pos+3] - 2.*psi[pos+4] )/(dx*dx) ;
			pos = 1 ;
			return (psi[pos+1] - 2.*psi[pos] + psi[pos-1])/sqr( dx ) ;
		}
		// this should never happen
		std::fprintf( stderr , "delxx was called for pos==%i nur psi is said to have only length N==%i -- exiting\n" , pos , N );
		std::exit( 3 ) ;
	}
}

// time propagator ( i \del_t \psi = H \psi ==> \del_t = H/i )
complex<double> delt( 
		const complex<double>* psi  // wave function
		, const int pos  // where the derivation etc. shall be evaluated
		, const double dx // spatial discretisation
		, const int center // center of coordinate system
		, const int N // length of psi 
		)
{
	complex<double> potential ( V( (pos-center) * dx ) , 0 ) ; // V is real: V = V + 0i
	//complex<double> derivative = (psi[pos+1] - 2.*psi[pos] + psi[pos-1])/sqr( dx ) ;
	return I_imag * ( delxx(psi,pos,dx,N)  * hbar / 2. / mass - potential * psi[pos] / hbar ) ;
}


// interpolate boundaries
/* 
void interpolate_boundary(
		const complex<double>* psi // data array
		, const int pos // position of the field to interpolate
		, const int width // number of fields to interpolate
		, const double step // dx for the right boundary, -dx for the left one
		)
{
	// currently only width==1 is supported
	if( width != 1 ){ std::printf( stderr , "The routine interpolate_boundary() was called with width=%i -- currently only width==1 is supported... exiting\n" ) ; std::exit( 2 ) ; }
	const int direction = ( step > 0 ? 1 : -1 ) ;
	const int x = pos - direction ; // the last `known' field
	
	// values for the taylor approximation
//	complex<double> f0 = psi[ x ] ; // f(x)
//	complex<double> f1 = ( psi[ x - 2 * direction ] - 4. * psi[ x - 1 * direction ] + 3. * psi[ x ] ) / (2.*abs(dx)) ;
//	complex<double> f2 = ...
	// not necessary -- the theoretically derived values were directly
	// substituted into Taylor's formula
	

	psi[ pos ] = 
}
*/

int main()
{

	// // system parameters // //
	// Length of the 1D system
	double L = 20. ;
	// Time to run the simulation
	double T = 20. ;
	// number of ouptuts
	int op = 500 ;


	// // simulational parameters // //
	// spatial discretisation
	double dx = 0.1;
	// temporal discretisation
	double dt = 0.000001 ;


	// // derived parameters // //
	const int Nx = L / dx ;
	const int Nt = T / dt ;
	const int center = Nx/2 ;
	const int dump_frequency = Nt / op ; // output every ...th timestep

	std::printf( "Nx = %i , Nt = %i \n" , Nx , Nt ) ;


	// // wave function // //
	//complex<double>* psi1, psi2 ; // strangely does not work...
	complex<double>* psi1 ;
	complex<double>* psi2 ;
	psi1 = new complex<double> [ Nx ] ;
	psi2 = new complex<double> [ Nx ] ;
	/*
	complex<double> psi1[ Nx ] ;
	complex<double> psi2[ Nx ] ;
	*/


	// // initialize wave function // //
	// Gaussian
	double normierung = sqrt( sqrt( M_PI ) ) ; 
	for( int i = 0 ; i < Nx ; i ++ ) 
		psi1[ i ] = complex<double>( exp(- sqr( ( i - 2*Nx/3 ) * dx ) / 2. ) / normierung , 0 ) ;
	// boundary conditions
	/*
	psi1[ 0 ] = 0 ;
	psi1[ Nx-1 ] = 0 ;
	psi2[ 0 ] = 0 ;
	psi2[ Nx-1 ] = 0 ;
	*/


	// // output // //
	FILE* op_handle = std::fopen( "oszi01.data" , "w" ) ;
	std::fprintf( op_handle , "# t\tx\tsqr(abs(psi))\tRe(psi)\tIm(psi)\n" ) ;
	std::fprintf( op_handle , "# L = %3f , T = %3f , dx = %3e , dt = %3e , op = %i\n" , L , T , dx , dt , op ) ;

	// // time loop // //
	for( int i = 0 ; i < Nt ; i++ )
	{
		// iterate over `internal' (not boundary) positions
		for( int j = 1 ; j < Nx-1 ; j++ )
		//for( int j = 0 ; j < Nx ; j++ )
			psi2[j] = psi1[j] + dt * delt( psi1 , j , dx , center , Nx ) ;
			// psi2[j] = psi1[j] + (dt/dx/dx) * (psi1[j+1]-2.*psi1[j]+psi1[j-1]) ; // debug

		// interpolate the boundary
		// use f(x+h) = f(x) + f'(x) h + (1/2) f''(x) h^2 + O( h^3 ) 
		// where f(x) is the next-to-boundary and f(x+h) the boundary itself.
		// the derivatives are then approximated using some data near the boundary.
		// interpolate_boundary_left(  );
		
		// most simple approximation
		//psi2[0] = psi2[1] ;
		//psi2[Nx-1] = psi2[Nx-2] ;

		// taylor first order
		psi2[0] = psi2[1] - dx * delx( psi2 , 1 , dx , Nx ) ;
		psi2[Nx-1] = psi2[Nx-2] + dx * delx( psi2 , Nx-1 , dx , Nx ) ;
			
		// switch new/old phi
		complex<double>* foobarasdf = psi1 ;
		psi1 = psi2 ;
		psi2 = foobarasdf ;

		// output
		if( i % dump_frequency == 0 )
		{
			// the output begins with a newline since gnuplot will then
			// understand the data as `girdded' datat
			std::fprintf( op_handle , "\n" ) ;
			for( int j = 0 ; j < Nx ; j++ )
				std::fprintf( op_handle , "%f\t%f\t%f\t%f\t%f\n" , i*dt , j*dx , sqr(std::abs(psi2[j])) , std::real(psi2[j]) , std::imag(psi2[j]) ) ;
		}
	}


	// // clean up // //
	delete[] psi1 ;
	delete[] psi2 ;
	std::fclose( op_handle ) ;

}
