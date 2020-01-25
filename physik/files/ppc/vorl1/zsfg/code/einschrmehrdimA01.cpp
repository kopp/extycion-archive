#include<iostream>
#include<cmath>

const int dim = 2;
// Die Variablen y und v werden in einem Array der Dimension 2 gespeichert.

const int N = 50000; //Schritte
const double a = 0; //Intervall
const double b = 100;
const double h = (b-a)/N; //Zeitschritt

const double anfangsbed[dim] = { 0.0 , 10.0 }; // { pos, geschw }

// BEISPIEL HARMONISCHER OSZILLATOR
const double om = 7; //frequenz -- masse: m==1
const double omq = om * om; //frequenzquadrat
void f(double t, double in[], double out[])
{
	out[0] = in[1]; 
	out[1] = - omq * in[0]; 
}

double energie_harmosz( double ortgeschw[] )
{
	double kin = 0.5 * ortgeschw[1] * ortgeschw[1];
	double pot = 0.5 * omq * ortgeschw[0] * ortgeschw[0];
	return kin + pot;
}

int main()
{

	//// EULER ////
	double yeuler[N][dim];
	for( int k=0; k< dim; k++)
		yeuler[0][k] = anfangsbed[k];

	for( int i = 1; i <= N; i++ )
	{
		double foo[dim];
		f( i*h , yeuler[i-1] , foo );
		for( int k=0; k< dim; k++ )
			yeuler[i][k] = yeuler[i-1][k] + h* foo[k];
	}

	//// KLASS. RUNGE KUTTA /////
	double yklrunge[N][dim];
	for( int k=0; k< dim; k++)
		yklrunge[0][k] = anfangsbed[k];
	for( int i = 1; i <= N; i++ )
	{
		double t = i*h;
		double k1[dim];
		f( t , yklrunge[i-1] , k1 );

		double k2[dim];
		double k2hilfe[dim];
		for( int k=0; k< dim; k++)
			k2hilfe[k] = yklrunge[i-1][k]+ k1[k] * h/2.0;
		f( t+h/2 , k2hilfe , k2 );

		double k3[dim];
		double k3hilfe[dim];
		for( int k=0; k< dim; k++)
			k3hilfe[k] = yklrunge[i-1][k] + k2[k] * h/2.0;
		f( t+h/2 , k3hilfe , k3 );

		double k4[dim];
		double k4hilfe[dim];
		for( int k=0; k< dim; k++)
			k4hilfe[k] = yklrunge[i-1][k] + k3[k]*h;
		f( t+h   , k4hilfe , k4 ); 

		for( int k=0; k< dim; k++)
			yklrunge[i][k] = yklrunge[i-1][k] + ( k1[k] + 2*k2[k] + 2*k3[k] + k4[k] ) * h/6;
	}


	//// ENERGIE ////
	double energie_euler[N], energie_klrunge[N];
	for( int i = 1; i <= N; i++ )
	{
		energie_euler[i] = energie_harmosz( yeuler[i] );
		energie_klrunge[i] = energie_harmosz( yklrunge[i] );
	}

	///// Ausgabe ////
	std::cout << "#Zeit \t Euler \t Energie(Euler) \t Kl. Runge-Kutta  \t Energie(Kl Runge) \n";
	for( int i = 1; i <= N; i++ )
	{
		std::cout << i*h << "\t";			//1
		std::cout << yeuler[i][0] << "\t";		//2
		std::cout << energie_euler[i] << "\t";		//3
		std::cout << yklrunge[i][0] << "\t";		//4
		std::cout << energie_klrunge[i] << "\t";	//5
		std::cout << "\n";
	}
}
