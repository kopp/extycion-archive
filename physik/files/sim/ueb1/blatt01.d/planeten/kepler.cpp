/*
 * kepler.cpp
 *
 * Michael Kopp
 *
 * Simulates our solar system with different integrators
 *
 * usage:
 * all parameters must be edited in source-code -- see comments there. When run
 * the program does not need any further interaction.
 * output:
 * Output is to stdout in the scheme
 * <time> <x1> <y1> <z1> <x2> <y2> <z2> ... <xn> <yn> <zn> [<energy>]
 * where <xi> is the x-coordinate of the i-th planet. <energy> is optional
 * since one has to pass an energy-function to the output-function [default:
 * activated but `wastes' CPU-time]
 *
 */



#include<iostream>
#include "planet.h"

#include<cmath>
#include<cstring> //strcmp
#include<cstdlib> //cerr



// physical. const
const double G = 0.0001184;


// tools
const vec3d nullvec( 0., 0., 0. );


// inlines
inline double sqr( const double x)
{
	return x * x;
}
/*
* dont use std::pow but own pow, using int-powers
*/
//using std::pow;
# define pow my_pow
inline double my_pow( const double x, const int a )
{
	double foo = x;
	for( int i = 1; i < a; i++ )
		foo *= x;
	return foo;
}
		

// // functions
// forces
void calculate_forces( planet planets[], const int nr_plan )
{
	for( int i = 0; i < nr_plan; i++ )
	{
		planets[i].acc = nullvec;
		for( int j = 0; j < nr_plan; j++ )
		{
			if( i != j ) // don't calculate gravitation of a boty with its self
			{
				// cumulate forces of each interacting planet
				// since F = G m m' \vec r / r^3 and a = F/m we use
				// a = G m \vec r / r^3
				// while \vec r = \vec r_j - \vec r_i
				vec3d r = planets[j].pos - planets[i].pos;
				planets[i].acc += G * planets[j].get_m() / pow( r.norm(), 3 ) * r;
			}
		}
	}
}

// derivate of acceleration: da/dt --> stored in store_pos
void calculate_diffacc( planet planets[], const int nr_plan )
{
	/* 
	 * use 
	 *   _F = G m M _r / r^3 (_ means vector)
	 * and
	 *   _F = m _a ==> _a = _F / m = G M _r / r^3.
	 * To get d_a/dt simply use chain-rule:
	 *   d_a/dt = d ( G M _r / r^3 ) / d_r . d_r/dt
	 *          = d ( G M _r / r^3 ) / d_r . _v
	 * This yields
	 *   d_a/dt = _v / r^3 - 3 ( _v . _r ) _r / r^5
	 *
	 * we call d_a/dt now diffacc, it will be stored in planets[i].store_pos
	 */
	for( int i = 0; i < nr_plan; i++ ) //iterate over planets
	{
		planets[i].store_pos = nullvec;
		for( int j = 0; j < nr_plan; j++ ) //iterate over `partners'
		{
			if( i != j ) // don't calculate gravitation of a boty with its self
			{
				vec3d r = planets[j].pos - planets[i].pos;
				planets[i].store_pos += G * planets[j].get_m() * (
						(1./pow( r.norm() , 3)) * planets[i].vel - (3./pow(r.norm(),5))  * ( planets[i].vel * r ) * r
						);
			}
		}
	}
}


// global energy E = T + V = mv^2/2 - GmM/r
double calculate_energy( planet planets[], const int nr_plan )
{
	double V = 0; //pot
	double T = 0; //kin
	for( int i = 0; i < nr_plan; i++ )
	{
		// potential energy
		for( int j = 0; j < nr_plan; j++ )
		{
			if( i < j ) // don't calculate gravitation of a boty with its self, use symmetry |r_ij| = |r_ji|
			{
				vec3d r = planets[j].pos - planets[i].pos;
				V += - G * planets[i].get_m() * planets[j].get_m() / r.norm();
				// don't ever use factor 2 here!!!
			}
		}
		// kinetic energy
		T += 0.5 * planets[i].get_m() * sqr( planets[i].vel.norm() );
	}
	return T + V;
}

// // output
// with energy-function
void output_pos( planet planets[], const int nr_plan , const int t, const double dt, double (*energy)( planet* , const int ) )
{
	std::cout << t * dt << '\t' << '\t';
	for( int i = 0; i < nr_plan; i++ )
	{
		print_cli( planets[i].pos );
		std::cout << '\t';
	}
	std::cout << '\t';
	std::cout << energy( planets , nr_plan ) ;
	std::cout << '\n';
}

// without energy
void output_pos( planet planets[], const int nr_plan , const int t, const double dt )
{
	std::cout << t * dt << '\t' << '\t';
	for( int i = 0; i < nr_plan; i++ )
	{
		print_cli( planets[i].pos );
		std::cout << '\t';
	}
	std::cout << '\n';
}


int main(int argc, char* argv[] )
{

	

	// numerical const
	int N = 10000;
	double dt =0.012; //timestep: use 0.012 to use earth-years as unit of time-measurement

	// // planets
	// archive
	planet erde( 1.,0.,0.,  0.,2. * M_PI,0.,  1. );
	planet sonne( 0., 0., 0., 0., 0., 0., 332946. );
	planet mond( 1.0 + 384400./1.5e8,0.,0.,    0.,2.*M_PI+2.*M_PI*365./27.7*384400./1.5e8,0.,    1./80.3 );
		double param = 1.5241;
	planet mars( param,0.,0.,    0.,2.*M_PI*265./668.*param,0.,   0.1 );
		param = 0.723;
	planet venus( param,0.,0.,   0.,2.*M_PI*356./224.*param,0.,   4.869e24/5.974e24  );
		param = 5.203;
	planet jupiter( param,0.,0.,   0.,2.*M_PI*1./11.86*param,0.,   1.899e27/5.974e24 );
	// what we will use now
	const int nr_plan = 6;
	planet planets[nr_plan];
	planets[0] = sonne;
	planets[1] = erde;
	planets[2] = mond;
	planets[3] = mars;
	planets[4] = venus;
	planets[5] = jupiter;

	// integration method
	int integration_method = 4;
	/* 
	* 1   velocity verlet
	* 2   leapfrog
	* 3   euler
	* 4   Verlet
	* 5   Runge-Kutta (Order 5)
	* 6   Predictor Corrector
	* 7   Predictor Corrector, a,da/dt are calculated every step
	*/


	// //  command line parameters

	for( char** foo = argv; *foo != NULL; foo++ )
	{
		if( std::strcmp(*foo,"-m")==0 )
		{
			foo++;
			integration_method = std::atoi( *foo );
			std::cout << "# integration_method set to " << integration_method << '\n';
			std::cerr << "# integration_method set to " << integration_method << '\n';
		}

		if( std::strcmp(*foo,"-N")==0 )
		{
			foo++;
			N = std::atoi( *foo );
			std::cout << "# N set to " << N << '\n';
			std::cerr << "# N set to " << N << '\n';
		}

		if( std::strcmp(*foo,"-dt")==0 )
		{
			foo++;
			dt = std::atof( *foo );
			std::cout << "# dt set to " << dt << '\n';
			std::cerr << "# dt set to " << dt << '\n';
		}
	}


	output_pos( planets , nr_plan , 0 , dt , calculate_energy);



	// // integration 
	switch( integration_method )
	{
		case 1: // velocity verlet
			/*
			 * my velocity-verlet is
			 *  x(i+1)   = x(i) + v(i) * dt + 1/2 * a(i) * dt^2
			 *  v(i+1/2) = v(i) + a(i) * dt/2
			 *  a(i+1)   = F(x(i+1))/m
			 *  v(i+1)   = v(i+1/2) + a(i+1) * dt/2
			 */
			// do forces a first time
			calculate_forces( planets , nr_plan );
			// loop
			for( int t = 0; t < N; t++ ) //timesteps
			{
				// iterate over planets
				for( int i = 0; i < nr_plan; i++ )
				{
					// 1. update pos
					planets[i].pos = planets[i].pos + dt * planets[i].vel + 0.5 * sqr(dt) * planets[i].acc;
					// 2. halfstep for velocity
					planets[i].vel = planets[i].vel + 0.5 * dt * planets[i].acc;
					// 3. update acceleration
					calculate_forces( planets, nr_plan );
					// 4. second halfstep for velocity
					planets[i].vel = planets[i].vel + 0.5 * dt * planets[i].acc;

				}

				// output
				output_pos( planets , nr_plan , t , dt , calculate_energy );
			}
			break;

		case 2: // leapfrog
			/*
			 * my leapfrog is (i: timestep)
			 *  x(i+1)   = x(i) +     v(i+1/2) * dt.
			 *  v(i+3/2) = v(i+1/2) + a(i+1) * dt.
			 * while the very first step is
			 *  v(i+1/2) = v(i) + a(i) * dt/2.
			 */
			// start asynchronousity in velocity: compute v(0 + dt/2)
			// --> the computation of velocity is dt/2 ahead!
			calculate_forces( planets , nr_plan );
			for( int i = 0; i < nr_plan; i++ )
				planets[i].vel += 0.5 * dt * planets[i].acc;

			for( int t = 0; t < N; t++ ) //timesteps
			{
				for( int i = 0; i < nr_plan; i++ ) // iterate over planets
				{
					// compute pos
					planets[i].pos += dt * planets[i].vel;
					// compute velocity 
					calculate_forces( planets , nr_plan ); // compute acceleration
					planets[i].vel += dt * planets[i].acc;
				}

				// output
				output_pos( planets , nr_plan , t , dt , calculate_energy );
			}
			break;

		case 3: //euler
			/*
			 * my euler is
			 *  x(i+1) = x(i) + v(i) * dt
			 *  v(i+1) = v(i) + a(i) * dt
			 */
			calculate_forces( planets , nr_plan );
			for( int i = 0; i < nr_plan; i++ )
				planets[i].vel += 0.5 * dt * planets[i].acc;

			for( int t = 0; t < N; t++ ) //timesteps
			{
				for( int i = 0; i < nr_plan; i++ ) // iterate over planets
				{
					calculate_forces( planets , nr_plan ); // compute acceleration
					// compute pos
					planets[i].pos += dt * planets[i].vel;
					// compute velocity 
					planets[i].vel += dt * planets[i].acc;
				}

				// output
				output_pos( planets , nr_plan , t , dt , calculate_energy );
			}
			break;

		case 4: //Verlet
			/* my verlet is
			 *  x(i+1) = 2*x(i) - x(i-1) + a(i) * dt^2
			 *
			 * since verlet needs x(i) and x(i-1) to compute x(i+1)
			 * the first x(i+1)-value must be computed using a
			 * one-step method. We will use something like
			 * leapfrog.
			 *
			 * x(i-1) is stored in store_pos.
			 *
			 * IMPROVEMENT: To minimize messing with storage
			 * alternate between pos and store_pos. use bool toggle
			 * therefore: toggle is 
			 *   true   if the most current pos is stored in pos, 
			 *   false  if the most current pos is stored in store_pos.
			 * problem: The functions calculate_forces, _energy,
			 * output_pos are currently unable to deal with
			 * positions stored in store_pos -- thus overload these
			 * functions with some toggle-flag...
			 *
			 * The verlet-algorithm does not compute the velocity
			 * of the particle. Thus use a differentiation to
			 * calculate v from x(i) and x(i-1). Thus the x(i+1) is
			 * stored outside of planets and x(i-1),x(i),x(i+1) are
			 * used to calculate v(i) via
			 *  v(i) = ( x(i+1) - x(i-1) ) / ( 2 * dt )
			 */
			// get first step with other integrator:
			/* sophisticated */
			calculate_forces( planets , nr_plan );
			for( int i = 0; i < nr_plan; i++ )
				planets[i].vel += 0.5 * dt * planets[i].acc; //get v(i+1/2)
			for( int i = 0; i < nr_plan; i++ )
			{
				planets[i].store_pos = planets[i].pos;
				planets[i].pos = planets[i].store_pos + dt * planets[i].vel; //get x(i+1)
			}
			/* euler  (debug sophisticated method)
			for( int i = 0; i < nr_plan; i++ )
			{
				planets[i].store_pos = planets[i].pos;
				planets[i].pos += dt * planets[i].vel;
			}
			*/

			

			// bool toggle = true; // implement toggle from here..
			
			// now to normal buisiness
			{ //-- bracket needed to initialize variables -- here: aiding_pos
				vec3d aiding_pos(0.,0.,0.);  //use this to store newly calculated pos
				for( int t = 0; t < N; t++ ) //timesteps
				{
					for( int i = 0; i < nr_plan; i++ ) // iterate over planets
					{
						calculate_forces( planets , nr_plan ); // compute acceleration
						// verlet
						aiding_pos = 2. * planets[i].pos - planets[i].store_pos + sqr( dt ) * planets[i].acc ;
						// calculate velocity
						planets[i].vel = (0.5 / dt ) * ( planets[i].store_pos - aiding_pos );
						// swap variables; this could be gone after the IMPROVEMENT mentioned above
						planets[i].store_pos = planets[i].pos;
						planets[i].pos = aiding_pos;
					}

					// output 
					output_pos( planets , nr_plan , t , dt , calculate_energy );
				}
			} //-- die, aiding_pos, die!
			break;

		case 5: // Runge-Kutta (Order 5)
			/* my runge kutta is:
			 * the dgl to solve is
			 *   (x,v)' = (v,a) = (v,F(x)/m)  <==>  y' = F(y) with y = (x,v)
			 * Runge Kutta is (y = y(i))
			 *   k1 = dt F(y)
			 *   k2 = dt F(y+k1/2)
			 *   k3 = dt F(y+k2/2)
			 *   k4 = dt F(y+k3)
			 * and finally
			 *   y(i+1) = y(i) + (1/6)( k1 + 2 k2 + 2 k3 + k4 )
			 *
			 * In this formalism actually k1 would be a 6-D-vect.,
			 * so ki = (kix,kiv) with two 3-D-vect.
			 *  
			 */
			for( int t = 0; t < N; t++ ) //timesteps
			{
				for( int i = 0; i < nr_plan; i++ ) // iterate over planets
				{
					// 1.
					calculate_forces( planets , nr_plan ); 
					vec3d k1x = dt * planets[i].vel;
					vec3d k1v = dt * planets[i].acc;
					// 2.
					planets[i].pos += 0.5 * k1x;
					calculate_forces( planets , nr_plan ); 
					planets[i].pos -= 0.5 * k1x;
					vec3d k2x = dt * ( planets[i].vel + 0.5 * k1v );
					vec3d k2v = dt * planets[i].acc;
					// 3.
					planets[i].pos += 0.5 * k2x;
					calculate_forces( planets , nr_plan ); 
					planets[i].pos -= 0.5 * k2x;
					vec3d k3x = dt * ( planets[i].vel + 0.5 * k2v );
					vec3d k3v = dt * planets[i].acc;
					// 4.
					planets[i].pos += k3x;
					calculate_forces( planets , nr_plan ); 
					planets[i].pos -= k3x;
					vec3d k4x = dt * ( planets[i].vel + k3v );
					vec3d k4v = dt * planets[i].acc;
					// next step
					planets[i].pos += (1./6) * ( k1x + 2. * k2x + 2. * k3x + k4x );
					planets[i].vel += (1./6) * ( k1v + 2. * k2v + 2. * k3v + k4v );
				}
				// output 
				output_pos( planets , nr_plan , t , dt , calculate_energy );
			}

		case 6: //Predicotr Corrector (Gear, Order 4)
			/* my Predicotr Corrector is (left hand side: always
			 * (i+1), right hand (i); u = da/dt)
			 *   Predictor:
			 *  xp = x + v dt + 1/2 a dt^2 + 1/6 u dt^3
			 *  vp = v + a dt + 1/2 r dt^2
			 *  ap = a = u dt
			 *  up = u
			 *   Corrector
			 *  ac = F(x)/m; del := ac - ap
			 *  xc = xp + c0 del dt^2/2
			 *  vc = vp + c1 del dt/2
			 *  ac = ap + c2 del
			 *  uc = up + c3 del 3/dt
			 * with c0 = 1/6, c1 = 5/6, c2 = 1, c3 = 1/3
			 *
			 * since u is needed, store_pos can be used for that. The function
			 */
			// to start: x,v,a,u must be given -- so calculate them.
			calculate_forces( planets , nr_plan ); // compute acceleration
			calculate_diffacc( planets, nr_plan ); // compute u (remember: u -> store_pos)
			for( int t = 0; t < N; t++ ) //timesteps
			{
				for( int i = 0; i < nr_plan; i++ ) // iterate over planets
				{
					vec3d del = nullvec;
					// predict
					planets[i].pos = planets[i].pos + dt * planets[i].vel + 0.5 * sqr( dt ) * planets[i].acc + (pow( dt , 3 ) /6.) * planets[i].store_pos;
					planets[i].vel = planets[i].vel + dt * planets[i].acc + 0.5 * sqr( dt ) * planets[i].store_pos;
					del = - (planets[i].acc + dt * planets[i].store_pos ); // 
					/* store acc in del since acc will be
					 * overwritten in calculate_forces; the
					 * `-' is necessary to use += later */
					// compute del
					calculate_forces( planets , nr_plan ); // compute acceleration
					del += planets[i].acc;
					// correct
					planets[i].pos += ( (1./6) * sqr( dt ) / 2. ) * del;
					planets[i].vel += ( (5./6) * dt / 2. ) * del;
					planets[i].store_pos += ( 1. / dt ) * del;
				}
				// output
				output_pos( planets , nr_plan , t , dt , calculate_energy );
			}
			break;

		case 7: // Predictor Corrector, a, da/dt calculated every step
			// see Pred. Corr. above for more info...
			for( int t = 0; t < N; t++ ) //timesteps
			{
				for( int i = 0; i < nr_plan; i++ ) // iterate over planets
				{
					vec3d del = nullvec;
					// predict
					calculate_forces( planets , nr_plan ); // compute acceleration
					calculate_diffacc( planets, nr_plan ); // compute u (remember: u -> store_pos)
					planets[i].pos = planets[i].pos + dt * planets[i].vel + 0.5 * sqr( dt ) * planets[i].acc + (pow( dt , 3 ) /6.) * planets[i].store_pos;
					planets[i].vel = planets[i].vel + dt * planets[i].acc + 0.5 * sqr( dt ) * planets[i].store_pos;
					del = - (planets[i].acc + dt * planets[i].store_pos );  
					// compute del
					calculate_forces( planets , nr_plan ); // compute acceleration
					del += planets[i].acc;
					// correct
					planets[i].pos += ( (1./6) * sqr( dt ) / 2. ) * del;
					planets[i].vel += ( (5./6) * dt / 2. ) * del;
					planets[i].store_pos += ( 1. / dt ) * del;
				}
				// output
				output_pos( planets , nr_plan , t , dt , calculate_energy );
			}
			break;

		default: // not yet implemented
			std::cerr << "fatal error: The requested integration-method (" << integration_method << ") is not yet implemented -- please chose an other one\n";
			std::exit( 7 );
			break;
	}





}
