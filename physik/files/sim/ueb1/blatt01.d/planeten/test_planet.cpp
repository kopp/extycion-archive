#include<iostream>
#include"planet.h"

#include<cmath>
using std::pow;


int main()
{

	const double G = 0.0001184;

	planet sonne( 0, 0, 0, 0, 0, 0, 332946. );
	/*
	for( int i = 1; i <= 3; i++ )
		std::cout << sonne.pos.get(i) << '\t';
	std::cout << '\n';
	*/
	planet erde( 1,0,0,  0,2. * M_PI,0,  1. );
	planet mond( 1.0 + 384400./1.5e8,0,0,    0,2.*M_PI+2.*M_PI*365./27.7*384400./1.5e8,0,    1./80.3 );

	int N = 1000;
	double dt = 0.01;
		vec3d force( sonne.pos-erde.pos );
		force *= (  G * sonne.get_m() * erde.get_m() / pow(force.norm(), 3. ) );
	for( int i = 0; i < N; i++ )
	{
		std::cout << i * dt << '\t'; print_cli( erde.pos ); print_cli( erde.vel, true );
		/*
		// force
		vec3d force( sonne.pos-erde.pos );
		force *= (  G * sonne.get_m() * erde.get_m() / pow(force.norm(), 3. ) );
		*/

		//print_cli( force );


		/* debug
		vec3d v1 = dt*erde.vel;
		vec3d v2 = ( 0.5 * dt * dt / erde.get_m() ) * force;
		print_cli( erde.pos ); print_cli( erde.vel ); print_cli( v1 ); print_cli( v2 ); std::cout <<'\n';
		erde.pos = erde.pos + v1 + v2;
		std::cout << "i = " << i << '\t' << "dt = " << dt << '\n';
		*/
		// integration -- velocity verlet
		erde.pos = erde.pos + dt * erde.vel + ( 0.5 * dt * dt / erde.get_m() ) * force;
		erde.vel = erde.vel + (0.5 * dt / erde.get_m() ) * force;

		force =  sonne.pos-erde.pos ;
		force *= (  G * sonne.get_m() * erde.get_m() / pow(force.norm(), 3. ) );

		erde.vel = erde.vel + (0.5 * dt / erde.get_m() ) * force;

	}

}
