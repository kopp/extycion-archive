#include<iostream>
#include<cmath>		//fuer f(x)
#include<cstdlib>	//fuer satoi
#include<iomanip>	//fuer nachkommastellen

//// global variables ////
int N;
double dx;

double f(double x)
{
	return std::sin(10*x)*std::exp(-x);
}

double gauss3(double xi)
//flaeche unter kurvenabschnitt der Breite dx um xi mit gauss, 3 stuetzstellen
{
	const int ordnung = 3;
	//integrationsintervall ist [xi-dx/2 ; xi+dx/2]; substitution:
	// 	t = (x-xi)/(dx/2)
	//damit
	//	\int_{xi-dx/2}^{xi+dx/2} f(x) \diff x 	=
	//	dx/2 \int_{-1}^{1} f(t) \diff t 	=
	//	dx/2  \sum_{i=0}^{2} w_i f(t_i)
	// Stuetzstellen: 0, +- sqrt{3/5}
	//nur fuer die transformierte Version bekannt
	double x[ordnung] = {-sqrt(3.0/5.0), 0.0, sqrt(3.0/5.0) };
	//transformation
	double t[ordnung];
	for( int i = 0; i < ordnung; i++ )
		t[i] = xi + dx/2 * x[i];
	// gewichte
	double w[ordnung] = {5.0/9.0 , 8.0/9.0 , 5.0/9.0 };
	// integration
	double summe = 0;
	for( int i = 0; i < ordnung; i++ )
		summe += f(t[i]) * w[i];
	return dx/2 * summe;

}

int main(int argc, char* argv[])
{
	N = 50; 	//in wie viele Abschnitte $[a,b]$ geteilt wird
	dx = 3.0 / N;

	//Gauss 3 Ordnung berechnen
	double integral_gauss3 = 0;
	for ( int i = 0; i < N; i++ )
		integral_gauss3 += gauss3(i*dx+dx/2.0);
		//das `+dx/2.0' wird benoetigt, weil die Stuetzstelle in der 
		//Mitte eines Intervalls liegen soll; fuer  i=0  laege xi
		//sonst bei x=0 und das Trapez ginge von -dx/2 bis dx/2.

	std::cout << "Wert des Integrals: ";
	std::cout << std::setprecision(25);
	std::cout << integral_gauss3 << "\n"; 
}
