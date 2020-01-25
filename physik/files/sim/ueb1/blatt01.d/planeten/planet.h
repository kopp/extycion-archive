/*
 * planet.h
 *
 * Michael Kopp
 *
 * provides a class to store properties (like position, velocity, ...) of an atom
 *
 */

#ifndef PLANET_H
#define PLANET_H

// positions are stored as 3-D-Vector
#include"vec3d.h"


class planet
{
	private:
		double mass;
	public:
		// some data
		vec3d pos, vel, acc, store_pos;

		// constructor
		/* info
		 * only pos and vel are used in the constructor since the
		 * physical system is characterized with these two
		 * informations. 
		 */
		planet(
				const double _x, const double _y, const double _z,
				const double _vx, const double _vy, const double _vz,
				const double _mass
		      )
			: pos ( _x, _y, _z ) , vel( _vx, _vy, _vz ), mass( _mass ) { };

		planet()
			: pos ( 0,0,0 ) , vel( 0,0,0 ), mass( 0 ) { };

		// getter
		inline double get_m() const;
		
		// setter


};

double planet::get_m() const
{
	return mass;
}

#endif //-- PLANET_H
