/*************
* numint02.cpp
*
* Berechnet numerisch das Integral von 
* 	sin(10 x) exp(-x)
* von 0 bis 3 mit Trapezregel und Simpsonregel
* Wert von maxima:
* 	 0.09873657349707297
*
* Verwendung:
* 	$ ./a.out <nummer>
* <Nummer> gibt die Zahl der verwendeten Stuetzstellen an. Wird kein <nummer>
* angegeben, wird  N = 50  gesetzt.
*
* Ausgabe:
* <nummer> 	<trapez>	<simpson>
*
*
* Version:
* 01b	nimmt schrittzahl als parameter entgegen
* 02	kann jetzt zusaetzlich simpsonregel
* 	integral wurde zu integral_trapez umbenannt, output angepasst
* 03	kann zusaetzlich gauss-Quadratur mit 3 oder 4 stuetzpunkten
* 	output mit 25 nachkommastellen
*
*                                                 ******************/


#include<iostream>
#include<cmath>		//fuer f(x)
#include<cstdlib>	//fuer satoi
#include<iomanip>	//fuer nachkommastellen



//// global files ////
int N;
double dx;

double f(double x)
{
	return std::sin(10*x)*std::exp(-x);
}


double trapez(double xi) 
//flaeche des trapezes mit Breite dx um xi
{
	return ((f(xi-dx/2.0) + f(xi+dx/2.0))/2.0)*dx;
}

double simpson(double xi)
//flaeche unter simpson-kurve der Breite dx um xi
{
	return ((f(xi-dx/2.0) + 4*f(xi) + f(xi+dx/2.0))/6.0)*dx;
}

double gauss3(double xi)
//flaeche unter kurvenabschnitt der Breite dx um xi mit gauss, 3 stuetzstellen
{
	const int ordnung = 3;
	//integrationsintervall ist [xi-dx/2 ; xi+dx/2]; substitution:
	// 	t = (x-xi)/(dx/2)
	//damit
	//	\int_{xi-dx/2}^{xi+dx/2} f(x) \diff x
	//	=
	//	dx/2 \int_{-1}^{1} f(t) \diff t
	//	=
	//	dx/2  \sum_{i=0}^{2} w_i f(t_i)
	
	// Stuetzstellen: 0, +- sqrt{3/5}
	//nur fuer die transformierte Version bekannt
	double x[ordnung] = {-sqrt(3.0/5.0), 0.0, sqrt(3.0/5.0) };
	//transformation
	double t[ordnung];
	for( int i = 0; i < ordnung; i++ )
	{
		t[i] = xi + dx/2 * x[i];
	}
	// gewichte
	double w[ordnung] = {5.0/9.0 , 8.0/9.0 , 5.0/9.0 };
	// integration
	double summe = 0;
	for( int i = 0; i < ordnung; i++ )
		summe += f(t[i]) * w[i];
	return dx/2 * summe;

}

double gauss4(double xi)
//flaeche unter kurvenabschnitt der Breite dx um xi mit gauss, 4 stuetzstellen
//siehe funktion gauss3() fuer mehr info
{
	const int ordnung = 4;
	double x[ordnung] = {
		-sqrt(3.0/7 + 2.0/7 * sqrt(6.0/5) ) ,
		-sqrt(3.0/7 - 2.0/7 * sqrt(6.0/5) ) ,
		+sqrt(3.0/7 - 2.0/7 * sqrt(6.0/5) ) ,
		+sqrt(3.0/7 + 2.0/7 * sqrt(6.0/5) ) };
	//transformation
	double t[ordnung];
	for( int i = 0; i < ordnung; i++ )
	{
		t[i] = xi + dx/2 * x[i];
	}
	// gewichte
	double w[ordnung] = {
		(18 - sqrt(30.0))/36.0 ,
		(18 + sqrt(30.0))/36.0 ,
		(18 + sqrt(30.0))/36.0 ,
		(18 - sqrt(30.0))/36.0 };
	// integration
	double summe = 0;
	for( int i = 0; i < ordnung; i++ )
		summe += f(t[i]) * w[i];
	return dx/2 * summe;

}




int main(int argc, char* argv[])
{
	// Parameterabfrage
	if ( argv[1] == NULL )
	{
		N = 50;
	}
	else
	{
		N = atoi(argv[1]);
	}
	dx = 3.0 / N;

	//Trapezintegral berechnen
	double integral_trapez = 0;
	for( int i = 0; i < N; i++ )
	{
		integral_trapez += trapez(i*dx + dx/2.0); 
		//das `+dx/2.0' wird benoetigt, weil die Stuetzstelle in der 
		//Mitte eines Intervalls liegen soll; fuer  i=0  laege xi
		//sonst bei x=0 und das Trapez ginge von -dx/2 bis dx/2.
	}

	//Simpsonregel berechnen
	double integral_simpson = 0;
	for ( int i = 0; i < N; i++ )
	{
		integral_simpson += simpson(i*dx+dx/2.0);
	}

	//Gauss 3 Ordnung berechnen
	double integral_gauss3 = 0;
	for ( int i = 0; i < N; i++ )
		integral_gauss3 += gauss3(i*dx+dx/2.0);

	//Gauss 4 Ordnung berechnen
	double integral_gauss4 = 0;
	for ( int i = 0; i < N; i++ )
		integral_gauss4 += gauss4(i*dx+dx/2.0);

	//Ausgabe
	std::cout << N << "\t" ;
	std::cout << std::setprecision(25);
	std::cout << integral_trapez << "\t" ;
	std::cout << integral_simpson << "\t"; 
	std::cout << integral_gauss3 << "\t"; 
	std::cout << integral_gauss4 << "\t"; 
	std::cout << "\n";
}
