#include<iostream>

#include "Vector6D.h"
// bewegung wird in einem Vektor gespeicher:
// (x1 v1 x2 v2 x3 v3)


/* 
 * Bewegungsgleichung:
 *
 *
*/


//// Physikalische Konstanten ////
//Masse
const double m[] = {1.0, 1.0, 1.0};
//Federhaerte
const double D[] = {1.0, 1.0, 1.0, 1.0};
//abstand von linker wand
const double L[] = { 1./12. , 2./12. , 3./12. };
//Anfangsbedingungen
const Vector6D anfangsbedingungen( 0., 0., 0., 0., 1.1/12., 0. );


//// Konstanten zur Simulation ////
const double a = 0; 	//anfangszeit
const double b = 10; 	//endzeit
const int N = 10;	//zeitschritte
const double h = (b-a)/N; 	// laenge zeitschritt


Vector6D f(double t, Vector6D bew)
// xi' = f( t , xi )
{
	Vector6D foo;
	// von System 2. Ordnung nach 1. Ordn:
	foo[0] = bew[1];
	foo[2] = bew[3];
	foo[4] = bew[5];
	// Beschleunigungen
	//Teilchen 0
	foo[1] = (  -(D[1] + D[0])*bew[0] + D[1]*bew[2]  ) / m[0] ;
	//Teilchen 1
	foo[3] = (  D[1]*bew[0] - (D[1] + D[2])*bew[2] + D[3]*bew[4]  ) / m[1] ;
	//Teilchen 2
	foo[5] = (  -(D[2] + D[3])*bew[4] + D[2]*bew[2]  ) / m[2];
	/*
	foo[1] = -2.0*bew[0] + bew[2];
	foo[3] = bew[0] - 2*bew[2] + bew[4];
	foo[5] = -2.0*bew[4] + bew[2];
	*/

	return foo;
}



int main()
{
	// Runge Kutta
	Vector6D runge[N];
	runge[0] = anfangsbedingungen;
	for( int i = 1; i < N; i++ )
	{
		double t = i * h;

		Vector6D k1 = f(t,runge[i-1]);
		Vector6D k2 = f(t+h/2.0 , runge[i-1]+(h/2.0)*k1);
		Vector6D k3 = f(t+h/2.0 , runge[i-1]+(h/2.0)*k2);
		Vector6D k4 = f(t+h , runge[i-1]+h*k2);

		runge[i] = runge[i-1] + (h/6.0)* ( k1 + 2.0*k2 + 2.0*k3 + k4 );
	}


	// Ausgabe
	for( int i = 1; i < N; i++ )
	{
		double t = i * h;
		std::cout << t << "\t";
		std::cout << runge[i][0] + L[0] << "\t"
			<< runge[i][2] + L[1]  << "\t"
			<< runge[i][4] + L[2] << "\t" ;

		std::cout << "\n";
	}
}
