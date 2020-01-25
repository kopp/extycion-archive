/************
 *
 * pendel01.cpp
 *
 * Die Bewegung eines gedaempften, getriebenen Fadeenpendels wird mit Euler,
 * Euler-Chromer, Velocity Verlet und Verlet berechnet.
 *
 * Das Symplektische Verfahren Verlet scheint hier ungeeignet, weil die
 * Bewegung gedaempft ist.
 *
 * Ausgabe erfolgt nach stdout:
 * 	<zeit> <euler> <ec> <vel verl> <verlet>
 * der winkel fuer Verlet ist auf [-pi,pi] beschraenkt; das Verfahren kann
 * problemlos erweitert werden.
 * im Quelltext bei //Austabe-koordinaten ist eine Ausgabe mit t-x-y
 * implementiert.
 *
 * Interaktion mit user ist noch nicht implementiert...
 *
 *                                                        ********************/

#include <iostream>
#include <cmath>

#include "Vector2D.h"

/***
* Die bewegung wird in einem vektor gespeichert; erste Komponente ist Ort,
* zweite Ableitung.
* `Ort' ist hier der Winkel, die Abl. die Winkelgeschwindigkeit
***/



const double a = 0; //bereich fuer t
const double b = 100;
const int N = 3000; //zeitschritte
const double h = (b-a)/N;

const double g = 1.0;
const double l = 1.0;
const double q = 0.5;
const double Omega = 2.0/3.0;
const double F = 0.5;

Vector2D f(double t, Vector2D bisher)
{
	Vector2D temp;
	temp[0] = bisher[1];
	//hier y'' eingeben:
	temp[1] =  -g/l * std::sin(bisher[0]) - q*bisher[1] + F*sin(Omega*t) ;
	return temp;
}
	




int main()
{
	Vector2D anfangsbed( 0.2 , 0.0);
	//euler
	Vector2D euler[N];
	euler[0] = anfangsbed;
	for( int i = 1; i < N; i++ )
	{
		double t = i * h;
		euler[i] = euler[i-1] + h * f(t, euler[i-1]);
	}

	//euler chromer
	Vector2D eulerchromer[N];
	eulerchromer[0] = anfangsbed;
	for( int i = 1; i < N; i++ )
	{
		double t = i * h;
		Vector2D foo = f(t,eulerchromer[i-1]);
		eulerchromer[i][1] = eulerchromer[i-1][1] + h * foo[1];
		eulerchromer[i][0] = eulerchromer[i-1][0] + h * eulerchromer[i][1];
	}


	// verlet
	Vector2D verlet[N];
	verlet[0] = anfangsbed;
	verlet[1] = eulerchromer[1]; // braucht zwei anfangsbed.
	for( int i = 2; i < N; i ++)
	{
		double t = i * h;
		verlet[i][0] = 2*verlet[i-1][0] - verlet[i-2][0] + h*h*( f(t,verlet[i-1]) )[1];
		// zweite komponente von f enthaelt werte fuer zweite Ableitung!
		//
		// verlet berechnet keine geschwindigkeit; verwende ableitung
		// Problem: Man kann nur die bisher errechneten Werte
		// verwenden, weshalb ich Verfahren entwickeln musste, mit
		// denen ich die Ableitung an der `rechten' Stelle bestimmen
		// kann:
		// konstruiere approximierendes polynom vom Grad 5, leite es an
		// der stelle x5 ab und druecke alle anderen Stellen durch x5
		// und h aus... es folgt dann fuer die Ableitung (\tex):
		// $${{25\,y_{5}-48\,y_{4}+36\,y_{3}-16\,y_{2}+3\,y_{1}}\over{12\,h}}$$
		// es ist y_5 = y[i], y_4 = y[i-1], y_3 = y[i-2], ...
		// Dafuer sind natuerlich fuenf stuetzstellen noetig; sind
		// weniger Werte vorhanden, verwende stattdessen die aus
		// Euler-Chromer...
		//
		verlet[i][1] = (i>=5) ? 
			25.0*verlet[i][0]-48.0*verlet[i-1][0]+36.0*verlet[i-2][0]-16.0*verlet[i-3][0]+3.0*verlet[i-4][0] :
			eulerchromer[i][1] ; 
		//einfache methode zum Test:
		//verlet[i][1] = ( verlet[i][0] - verlet[i-1][0] ) /h;
	}


	// velocity verlet
	Vector2D velocverlet[N];
	velocverlet[0] = anfangsbed;
	for( int i = 1; i < N; i++ )
	{
		double t = i * h;
		Vector2D foo = f(t,velocverlet[i-1]);
		//velocverlet[i] = 2.0*velocverlet[i-1] = velocverlet[i-2] + h*h*f(t,velocverlet[i-1]);
		//velocverlet[i][0] = 2.0*velocverlet[i-1][0] -velocverlet[i-2][0] + h * h * foo[0];
		//velocverlet[i][1] = ( velocverlet[i][0] -velocverlet[i-2][0]) / (2.0*h) ;
		velocverlet[i][0] = velocverlet[i-1][0] + velocverlet[i-1][1]*h + 0.5 * h*h * foo[1];
		Vector2D fooneu = f(t,velocverlet[i]);
		velocverlet[i][1] = velocverlet[i-1][1] + 0.5*h*( foo[1] + fooneu[1] );
	}


	//ausgabe -- winkel
	for( int i = 0; i < N; i++ )
	{
		std::cout << i * h << "\t";	//1
		std::cout << euler[i][0] << "\t";	//2
		std::cout << eulerchromer[i][0] << "\t"; 	//3
		std::cout << velocverlet[i][0] << "\t"; 	//4
		// das ist module 2pi; nur winkelwerte in [pi,pi] werden ausgegeben
		double output = (verlet[i][0] > -1.0 * M_PI) ? verlet[i][0] - 2.0*M_PI * int( (verlet[i][0]+M_PI) / 2.0 / M_PI  ) : 
			verlet[i][0] - 2.0*M_PI * int( (verlet[i][0]+M_PI) / 2.0 / M_PI ) ;
		
	//	double output = (verlet[i][0] > M_PI) ? verlet[i][0] - 2.0*M_PI : verlet[i][0];
		std::cout << output << "\t";
		//std::cout << verlet[i][0] << "\t"; //5

		std::cout << "\n";
	}
	
	//ausgabe -- koordinaten
	/*
	//3dim mmit gnuplot plotten (splot 'foo')
	for( int i = 0; i < N; i++ )
	{
		std::cout << i * h << "\t";
		// x-komp
		std::cout << l * std::sin(velocverlet[i][0]) << "\t";
		// y-komp
		std::cout << -l * std::cos(velocverlet[i][0]) << "\t";

		std::cout << "\n";

	}
	*/

	

}
