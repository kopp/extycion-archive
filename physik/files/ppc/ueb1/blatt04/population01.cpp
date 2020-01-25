/***************
 *
 * population01.cpp
 *
 * Integriert Volterra- und Lotka-Volterra-Modell mit Runge-Kutta
 *
 *                                                         *******************/

#include<iostream>

#include "Vector2D.h" //2-dim vekoren

/* 
 * verwende einen Vektor um population zu beschreiben:
 * (beute, raeuber)
 */



//// Konstanten zur Simulation ////
const double birth = 0.1; 	//geburtsrate beute
const double mortal = 0.2; 	//sterberate raeuber
const double K = 0.5; 	//Schranke Lebensraum Beute
Vector2D anfangsbedingungen(0.25, 0.25);


//// KOnstanten zur Simulation ////
const double a = 0;     //anfangszeit
const double b = 250;    //endzeit
const int N = 5000;       //zeitschritte
const double h = (b-a)/N;       // laenge zeitschritt

// Volterra gl
// y' = f(t, y)
Vector2D fvolterra(double t, Vector2D popalt)
{
	return Vector2D( (birth*popalt[0] - popalt[0]*popalt[1]) , (-mortal*popalt[1] + popalt[0]*popalt[1]) );
}

// Lotka-Volterra-Gl
// y' = f(t, y)
Vector2D flotka(double t, Vector2D popalt)
{
	return Vector2D( (birth*(1.0-popalt[0] / K)*popalt[0] - popalt[0]*popalt[1]) , (-mortal*popalt[1] + popalt[0]*popalt[1]) );
}


int main()
{

	// Runge Kutta Volterra
	Vector2D volterra[N];
	volterra[0] = anfangsbedingungen;
	for( int i = 1; i < N; i++ )
	{
		double t = i * h;

		Vector2D k1 = fvolterra(t,volterra[i-1]);
		Vector2D k2 = fvolterra(t+h/2.0 , volterra[i-1]+(h/2.0)*k1);
		Vector2D k3 = fvolterra(t+h/2.0 , volterra[i-1]+(h/2.0)*k2);
		Vector2D k4 = fvolterra(t+h , volterra[i-1]+h*k2);

		volterra[i] = volterra[i-1] + (h/6.0)* ( k1 + 2.0*k2 + 2.0*k3 + k4 );
	}

	// Runge Kutta Lotka Volterra
	Vector2D lotka[N];
	lotka[0] = anfangsbedingungen;
	for( int i = 1; i < N; i++ )
	{
		double t = i * h;

		Vector2D k1 = flotka(t,lotka[i-1]);
		Vector2D k2 = flotka(t+h/2.0 , lotka[i-1]+(h/2.0)*k1);
		Vector2D k3 = flotka(t+h/2.0 , lotka[i-1]+(h/2.0)*k2);
		Vector2D k4 = flotka(t+h , lotka[i-1]+h*k2);

		lotka[i] = lotka[i-1] + (h/6.0)* ( k1 + 2.0*k2 + 2.0*k3 + k4 );
	}

	//Ausgabe
	for( int i = 1; i < N; i++ )
	{
		double t = i * h;
		std::cout << t << "\t";			//1
		std::cout << volterra[i][0] << "\t";	//2
		std::cout << volterra[i][1] << "\t"; 	//3
		std::cout << lotka[i][0] << "\t";	//4
		std::cout << lotka[i][1] << "\t";	//5

		std::cout << "\n";
	}



}
