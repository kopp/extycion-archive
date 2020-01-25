/*
 * vec3d.h
 *
 * Michael Kopp
 *
 * provides 3-dim vectors with some functionality 
 */

#ifndef VEC3D_H
#define VEC3D_H

#include<cstdlib> // cerr
#include<cmath> // pow in norm()
using std::pow;


class vec3d
{
	private:
		double * koords; // save (x,y,z) here
	public:
		// constructor
		vec3d( double _x, double _y, double _z )
			: koords ( new double[3] )
		{ koords[0] = _x; koords[1] = _y; koords[2] = _z; }
		vec3d()
			: koords( new double [3] )
		{ koords[0] = 0.; koords[1] = 0.; koords[2] = 0.; }

		// destructor
		~vec3d() { delete[] koords; }

		// rule of the three
		vec3d( const vec3d & _v )
			: koords ( new double[3] )
		{ koords[0] = _v.get(1); koords[1] = _v.get(2); koords[2] = _v.get(3); }

		vec3d & operator=( const vec3d & _v )
		{
			if( this != &_v )
			{
				// allocate new memory
				double * new_koord = new double[3];
				for( int i = 0; i < 3; i++ )
					new_koord[i] = _v.get( i+1 );
				// deallocate old
				delete[] koords;
				// assign new
				koords = new_koord;
			}
			// convention
			return *this;
		}



		// getter
		inline double get_x() const ;
		inline double get_y() const ;
		inline double get_z() const ;
		inline double get( const int _i ) const ;

		//setter
		inline void set_x( const double _x );
		inline void set_y( const double _y );
		inline void set_z( const double _z );
		inline void set( const int _i, const double _x );
		inline void set( const double _x, const double _y, const double _z);

		// // math
		// onary
		inline double norm( const double _p ) const; // p-norm
		inline double norm(  ) const; // p=2-norm
		inline vec3d operator- ( );
		inline vec3d & operator+=( const vec3d & _v );
		inline vec3d & operator-=( const vec3d & _v );
		inline vec3d & operator*=( const double _a );
		// binary
		inline friend vec3d operator* ( const double _a, const vec3d & _v);
		inline friend vec3d operator+ ( const vec3d  & _u, const vec3d & _v);
		inline friend vec3d operator- ( const vec3d  & _u, const vec3d & _v);
		inline friend double operator* ( const vec3d & _u, const vec3d & _v); //scalar product

};


// // non-class functions
void print_cli( vec3d & _v , bool abs = false )
{
	for( int i = 1; i <= 3; i++ )
		std::cout << _v.get( i ) << '\t';
	if( abs ) std::cout << '\n';
}


	


// getter
// only get( i ) will know how to `resolve' the data -- thus if it's saved
// otherwise, only this must be changed
inline double vec3d::get( const int _i ) const 
{
	switch( _i )
	{
		case 1: return koords[0]; break;
		case 2: return koords[1]; break;
		case 3: return koords[2]; break;
		default:
			std::cerr << "fatal error (vec3d::get()): vec3d provides only 3-dim-vectors (val 1-3, not " << _i << "). Quitting";
			std::exit( 1 );
			break;
	}
}

inline double vec3d::get_x() const
{
	this->get( 1 );
}
inline double vec3d::get_y() const
{
	this->get( 2 );
}
inline double vec3d::get_z() const
{
	this->get( 3 );
}


// setter
// only set( i ) will know how to `resolve' the data -- thus if it's saved
// otherwise, only this must be changed
inline void vec3d::set( const int _i, const double _x )
{
	switch( _i )
	{
		case 1: koords[0] = _x; break;
		case 2: koords[1] = _x; break;
		case 3: koords[2] = _x; break;
		default:
			std::cerr << "fatal error (vec3d::set()): vec3d provides only 3-dim-vectors. Quitting";
			std::exit( 1 );
			break;
	}
}
inline void vec3d::set( const double _x, const double _y, const double _z)
{
	this->set( 1 , _x );
	this->set( 2 , _y );
	this->set( 3 , _z );
}
inline void vec3d::set_x( const double _x )
{
	this->set( 1 , _x );
}
inline void vec3d::set_y( const double _y )
{
	this->set( 2 , _y );
}
inline void vec3d::set_z( const double _z )
{
	this->set( 3 , _z );
}


// math

// onary

double vec3d::norm( const double _p ) const
{
	double norm = 0;
	for( int i = 0; i < 3; i++ )
		norm += pow(koords[i],_p);
	return pow(norm, 1./_p );
}
double vec3d::norm(  ) const
{
	return this->norm( 2 );
}
vec3d vec3d::operator- ( )
{
	return vec3d( - koords[0] , - koords[1], - koords[2] );
}
vec3d & vec3d::operator+=( const vec3d & _v )
{
	this -> set( 1 , this->get(1) + _v.get(1) );
	this -> set( 2 , this->get(2) + _v.get(2) );
	this -> set( 3 , this->get(3) + _v.get(3) );
	return *this;
}
vec3d & vec3d::operator-=( const vec3d & _v )
{
	this -> set( 1 , this->get(1) - _v.get(1) );
	this -> set( 2 , this->get(2) - _v.get(2) );
	this -> set( 3 , this->get(3) - _v.get(3) );
	return *this;
}
vec3d & vec3d::operator*=( const double _a )
{
	this -> set( 1 , this->get(1) * _a );
	this -> set( 2 , this->get(2) * _a );
	this -> set( 3 , this->get(3) * _a );
	return *this;
}

		
// binary
vec3d operator* ( const double _a, const vec3d & _v) 
{
	return vec3d( _v.koords[0] * _a , _v.koords[1] * _a , _v.koords[2] * _a );
}	
vec3d operator+ ( const vec3d & _u, const vec3d & _v)
{
	return vec3d( _u.get(1) + _v.get(1) , _u.get(2) + _v.get(2) , _u.get(3) + _v.get(3) );
}
vec3d operator- ( const vec3d & _u, const vec3d & _v)
{
	return vec3d( _u.get(1) - _v.get(1) , _u.get(2) - _v.get(2) , _u.get(3) - _v.get(3) );
}
		
double operator* ( const vec3d & _u, const vec3d & _v) //scalar product
{
	return _u.get(1) * _v.get(1) + _u.get(2) * _v.get(2) + _u.get(3) * _v.get(3);
}


#endif //-- VEC3D_H
