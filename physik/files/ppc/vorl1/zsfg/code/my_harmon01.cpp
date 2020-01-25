/*
 * This solves the DGL 
 * 	x''  =  -k x
 * the user is asked for values for  k , initial conditions, the time interval and accuracy.
 *
 * A waek and a strong method is used.
 *
 * Output: ASCII file; 3 columns:
 * 	[time] \t [x numerically, weak] \t [x numerically, strong]  \t [x analytically]
 *
 */


#include<iostream>
using namespace std;
#include<cmath>	// for cos, sqrt

int main()
{
	// declaration
	double k, dt, tmax, v0, x0;
	// user input
	cout << "#Federhaerte k:         "; cin >> k;
	cout << "#Anfangsauslenkung:     "; cin >> x0;
	cout << "#Anfangsgeschw.:        "; cin >> v0;
	cout << "#Intervalldauer:        "; cin >> tmax;
	cout << "#Groesse Zeitschritt:   "; cin >> dt;

	// // internal variables
	// weak
	double xw[2], vw[2]; // x[0]: x(t), x[1]: x(t+dt) dito v[.]
	// strong
	double xs[2], vs[2];
	// analytic
	double xa, omega, ampl, phase;
	//frequency
	omega = sqrt(k);
	int use_ana = 1; // if k<0 sqrt(k) is ... ungood. Output for x_analytic then is 0.
	if ( k < 0 )
	{
		use_ana = 0;
	}
	// phase, amplitude
	if ( x0 != 0 )
	{
		phase = atan(-v0/x0)/omega;
		ampl = x0/cos(phase);
	}
	else
	{
		phase = -2.0 * atan(1.0); // -pi/2
		ampl = v0/omega;
	}

	// initialize
	xw[0]=x0; vw[0]=v0;
	xs[0]=x0; vs[0]=v0;

	// loop
	cout << "# --- start computing --- ";
	for ( double t=0; t <= tmax; t+=dt )
	{
		// // compute
		// weak method
		vw[1] = - k * xw[0] * dt + vw[0];
		xw[1] = vw[0] * dt + xw[0];
		// strong method
		vs[1] = - k * xs[0] * dt + vs[0];
		xs[1] = vs[1] * dt + xs[0];
		// analytic
		xa = use_ana * ampl * cos(omega * (t+dt) + phase);
		// output
		cout << t << "\t" << xw[0] << "\t" << xs[0] << "\t" << xa << "\n";
		// shift arrays x,v ([0] needs to be _current_ value
		xw[0]=xw[1]; vw[0]=vw[1];
		xs[0]=xs[1]; vs[0]=vs[1];
	}
	cout << "# --- loop done ---";
}


