#include<iostream>
#include<cmath>


const bool verbose = false;


double f(double x)
{
	//return std::sin(M_PI * x);
	return 1 / ( x * x + 1 );
}


// Polynome fuer neville
double p( int i, int k, double xi, double x[], double y[] )
{
	if( verbose ) std::cout << "Called p_ " << i << " " << k << " ( " << xi << " ) \n";
	if( i == k ) // triviales neville Polynom
		return y[i];
	else 
	{
		if( verbose ) std::cout << "   Calling p_ " << i+1 << " " << i+k << " ( " << xi << " ) \n";
		if( verbose ) std::cout << "   Calling p_ " << i << " " << i+k-1 << " ( " << xi << " ) \n";
		return ( (xi - x[k])*p(i,k-1,xi,x,y) + (x[i] - xi)*p(i+1,k,xi,x,y) )  / (x[i] - x[k] );
	}

}


// neville...
double neville( int n, double xneu, double x[], double y[] )
{
	return p(0,n,xneu,x,y);
}


int main()
{
	int n = 20;
	double a = 0;
	double b = 2;
	double dx = (b-a)/(1.0*n);
	//// aequidistant ////
	double x[n];
	double y[n];
	for( int i = 0; i <= n; i++ )
	{
		x[i] = a+i*dx;
		y[i] = f(x[i]);
	}
	//// tschebyscheff ////
	double xtsch[n];
	double ytsch[n];
	for( int i = 0; i <= n; i++ )
	{
		xtsch[i] = (a+b)/2.0 + (b-a)/2.0 * std::cos(M_PI * i / n );
		ytsch[i] = f(xtsch[i]);
	}


	double schritt = 0.1;
	double R = 3;
	double xkoord = -1;
	while ( xkoord < R )
	{
		std::cout << xkoord << "\t";
		std::cout << f(xkoord) << "\t";
		std::cout << neville( n , xkoord , x , y ) << "\t";
		std::cout << neville( n , xkoord , xtsch , ytsch ) << "\t";
		std::cout << "\n";

		xkoord += schritt;
	}


}
