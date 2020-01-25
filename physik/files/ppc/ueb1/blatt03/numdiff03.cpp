/**********************
* numdiff03.cpp
*
* Berechnet verschiedene Ableitungen einer Funktion mit verschiedenen Methoden
*
* Eingabe: 
* 	keine
* Ausgabe
* 	<anz stuetzstellen>	<f(x)>	<versch. abl...>
* siehe in main() fuer Reihenfolge
*
* versionen
* 02: 	dx, N sind jetzt global
* 	berechnet zweite Ableitung
* 03:	verwendet neben zentraler/rechts/links ableitung noch
* 	approximation durch hoehere Polynome...
*
*                                                          *******************/



#include<iostream>
#include<cmath>


//// GLOBALE VARIABLEN ////
const double dx = 3.0/50; //Schrittweite
const int N = 3/dx; //Schritte um Intervall [0:3] abzudecken

//// FUNKTION ////
double f(double x) //actual function
{
	return std::sin(10*x) * std::exp(-x);
}


//// ERSTE ABLEITUNG ////
// Approx Polynom Ordnung 1
double labl(double xi, double dx) //linke ableitung
{
	return (f(xi)-f(xi-dx))/dx;
}
double labl(double xi) //linke ableitung
{
	return (f(xi)-f(xi-dx))/dx;
}

double rabl(double xi, double dx) //rechte ableitung
{
	return (f(xi+dx)-f(xi))/dx;
}
double rabl(double xi) //rechte ableitung
{
	return (f(xi+dx)-f(xi))/dx;
}

//Approx Polynom Ordnung 2
double zabl(double xi, double dx) //zentrale ableitung
{
	return (f(xi+dx)-f(xi-dx))/(2*dx);
}
double zabl(double xi) //zentrale ableitung
{
	return (f(xi+dx)-f(xi-dx))/(2*dx);
}

//Approx Polynom Ordnung 3
double p3zabl(double xi) //approx. durch Polynom 3. Grades
{
	//verwendet 4 stuetzstellen
	double x0 = xi - 1.5 * dx;
	double x1 = xi - 0.5 * dx;
	double x2 = xi + 0.5 * dx;
	double x3 = xi + 1.5 * dx;
	return (f(x0)-27*f(x1)+27*f(x2)-f(x3))/(24*dx);
}


//// ZWEITE ABLEITUNG ////
//Approx Polynom Ordnung 1
double labl2(double xi) //links
{
	return (labl(xi)-labl(xi-dx))/dx;
}

double rabl2(double xi) //rechts
{
	return (rabl(xi+dx)-rabl(xi))/dx;
}

//Approx Polynom Ordnung 2
double zabl2(double xi) //zentral
{
	return (zabl(xi+dx)-zabl(xi-dx))/(2*dx);
}

//Approx Polynom Ordnung 3
double p3zabl2(double xi) //approx. durch Polynom 3. Grades
{
	//verwendet 4 stuetzstellen
	double x0 = xi - 1.5 * dx;
	double x1 = xi - 0.5 * dx;
	double x2 = xi + 0.5 * dx;
	double x3 = xi + 1.5 * dx;
	return (f(x0)-f(x1)-f(x2)+f(x3))/(2*dx*dx);
}





int main()
{

	for( int i = 0; i <= N; i++ )
	{
		double x = i * dx;
		std::cout << x << "\t";			//1
		std::cout << f(x) << "\t";		//2
		std::cout << labl(x,dx) << "\t";	//3
		std::cout << rabl(x,dx) << "\t";	//4
		std::cout << zabl(x,dx) << "\t";	//5
		std::cout << p3zabl(x) << "\t";		//6
		std::cout << labl2(x) << "\t";		//7
		std::cout << rabl2(x) << "\t";		//8
		std::cout << zabl2(x) << "\t";		//9
		std::cout << p3zabl2(x) << "\t";	//10
		std::cout << "\n";
	}

}

