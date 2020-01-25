#include<iostream>
#include<cmath>

//// GLOBALE VARIABLEN ////
const int n = 30;	//anzahl stuetzstellen
const double a = 0;	//untere intervallgrenze
const double b = 5;	//obere intervallgrenze
const int N = 200;	//azahl an Ausgaberasterstellen
const double delx = (b-a)/N;	//raster fuer ausgabe


double f(double x) //function
{
	return std::cos(10*x) * std::exp(-x);
}

int main()
{
	//tschebyscheff-stuetzstellen
	double xt[n]; double yt[n];
	for(int i = 0; i <= n; i++) 
	{
		xt[i] = (a+b)/2 - (b-a)/2 * std::cos(M_PI*i/n);
		yt[i] = f(xt[i]);
	}

	//aequidistante stuetzstellen
	double xa[n]; double ya[n];
	for(int i = 0; i <= n; i++) 
	{
		xa[i] = a + (b-a)/n * i;
		ya[i] = f(xa[i]);
	}

	//lagrange interpolation -- tschebyscheff
	double apprLagTsch[N];
	for (int k = 0; k <= N; k++)	//schleife ueber ausgaberaster
	{
		double xi = a + delx * k;
		double summ = 0;	//fuer summe
		for (int i = 0; i <= n; i++)	
		{
			double multip = 1;	//fuer produkt
			for (int j = 0; j <= n; j++) 
				multip *= (j==i?1: ((xi-xt[j])/(xt[i]-xt[j])) );
			multip *= yt[i];	//koeff von legender polynom drangesetzt
			summ += multip;
		}
		apprLagTsch[k] = summ;
	}

	//lagrange interpolation -- aequidistant
	double apprLagAeq[N];
	for (int k = 0; k <= N; k++)	//schleife ueber ausgaberaster
	{
		double xi = a + delx * k;
		double summ = 0;	//fuer summe
		for (int i = 0; i <= n; i++)	
		{
			double multip = 1;	//fuer produkt
			for (int j = 0; j <= n; j++)
				multip *= (j==i?1: ((xi-xa[j])/(xa[i]-xa[j])) );
			multip *= ya[i];	//koeff von legender polynom drangesetzt
			summ += multip;
		}
		apprLagAeq[k] = summ;
	}

	//Ausgabe
	for (int k = 0; k <= N; k++ )
	{
		double xi = a + delx * k;
		std::cout << xi << "\t" << f(xi) << "\t" << apprLagTsch[k] << "\t" << apprLagAeq[k] << "\n";
	}
}
