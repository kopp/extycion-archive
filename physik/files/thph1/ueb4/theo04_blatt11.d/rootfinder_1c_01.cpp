#include<cstdio>
#include<gsl/gsl_roots.h>
#include<gsl/gsl_errno.h> // GSL_CONTINUE


/*
 * we have a function containing (above others) h and m and we would like to
 * get an expression h = h(m). Unfortunately this seems to be impossible, so
 * we'll try to solve for different m the equation numerically...
 */


// parameters to pass to the expression
struct params
{
	double t ; // temp T/T_c
	double N ; // number of particles
	double amg ; // a/mg a: VdW gas
	double b ; // b: VdW gas
	double A ; // area of the piston
	double g ; // g from F = m g
} ;

// this is what gsl requires
double func( double h , void * par )
{
	params * foo = (params*) par ;
	double t = (foo->t) ;
	double N = foo->N ;
	double amg = foo->amg ;
	double b = foo->b ;
	double A = foo->A ;
	double g = foo->g ;

	return (8. * N * t * h*h * amg )/(27. * b * (h-b*N/A) ) - amg * N * N / A - h*h ;
}





int main()
{

	// parameters
	// below critical temperature t_c = 3 
	double t = 0.95 ;

	FILE * hmfh = std::fopen( "hm.data" , "a" ) ;

	std::fprintf( hmfh , "# m h(m) T/T_c \n" ) ;

	for( double m = 0.01 ; m < 4 ; m += 0.01 ) 
	{

		params paramtopass = { t , 1. , 9.81 * 1. * m , 1. , 1. , 9.81 } ;

		// function handle for gsl
		gsl_function F ;
		F.function = &func ;
		F.params = &paramtopass ;

		/* range check 
		   FILE * fh = std::fopen( "functionvalues.data" , "w" ) ;
		   for( double h = 0 ; h < 20; h += 0.01 )
		   fprintf( fh , "%f %f\n" , h ,  ( *(F.function) )( h , F.params ) ) ;
		   std::fclose( fh ) ;
		   */

		// initialize solver
		gsl_root_fsolver * solv = gsl_root_fsolver_alloc( gsl_root_fsolver_bisection ) ;
		gsl_root_fsolver_set( solv , &F , 1.001 , 1000. ) ;

		int status;
		do
		{
			// do one iteration
			gsl_root_fsolver_iterate( solv ) ;
			double x_lo = gsl_root_fsolver_x_lower( solv ) ;
			double x_hi = gsl_root_fsolver_x_upper( solv ) ;
			status = gsl_root_test_interval( x_lo , x_hi , 1e-4 , 0 ) ;
		}
		while( status == GSL_CONTINUE ) ;


		// output
		double root = gsl_root_fsolver_root( solv ) ;
		std::fprintf( hmfh , "%f %f %f\n" , m , root , t ) ;

		// discharge solver
		gsl_root_fsolver_free( solv ) ;

	}


	std::fclose( hmfh ) ;

}
