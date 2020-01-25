/*
 * board.h
 *
 * Michael Kopp
 *
 * provides a simple 2D lattice for the ising model
 * every field is either 1 or -1
 *
 */

#ifndef BOARD_H
#define BOARD_H


#include<cstring> // memset
#include<gsl/gsl_rng.h> // rng
#include<cstdio> // printf 
using std::printf ;
using std::fprintf ;
#include<cstdlib> // exit
#include<algorithm>
using std::copy ;



class board
{
	private:
		const unsigned int L ; // length
		int * data ; // data
		double energy ; // make it a double: it can get as big as  2 (max int)^2 ~ 2^18
		double delta_energy ; // store each output of Delta_energy so that flip() can use it...
		// inline unsigned int dereference_pos( const unsigned int _x , const unsigned int _y ) ;
		//inline unsigned int left_neighbour( const unsigned int _x , const unsigned int _y ) ;
		int magnetisation ; // total magnetisation -- sum over all spins
	public:
		// constructor
		board( const unsigned int _L  , // size of the board
				const double _deg , // deg in [0:1]: amount of fields with `1'
				const unsigned long _seed   // seed for the RNG
		     ) ;
		// load from file
		board( const unsigned int _L , const char* filename ) ;
		// =
		board& operator=( const board& foo ) ;
		// destructor
		~board()
		{
			delete[] data ;
		}

		// graphical output to Commandline
		void print_cli( ) const ;
		// graphical output to PPM file
		void print_ppm( const char* name ) const ;

		// evaluate total energy from the scratch
		void evaluate_energy() ;
		// return Energy-difference if the spin at (_x,_y) would be flipped:
		double Delta_E( const unsigned int _x , const unsigned int _y ) ;
		// flip spin 
		void flip(  const unsigned int _x , const unsigned int _y , const bool Delta_E_used_before ) ;
		
		// calculate total magnetisation 
		void evaluate_magnetisation() ;

		// output energy
		double get_energy()  const
		{ 
			return energy ;
		}

		// output magnetisation
		int get_magn() const
		{
			return magnetisation ;
		}

		// output size
		unsigned int get_length() const
		{
			return L ;
		}

		// output delta_energy (necessary for operator=)
		double get_delta_energy() const
		{
			return delta_energy ;
		}

		// save data
		void save_to_file( const char* filename ) const ;


		/* deprecated 
		// compute energy of one field and its direct neighbours:
		double energy_neighbourhood( const unsigned int _x , const unsigned int _y ) const ;
		// flip spin at (x,y) and return change of energy
		double flip_spin( const unsigned int _x , const unsigned int _y ) ;
		*/ 


};


/* *********************
 *    implementation
 * *********************/

board::board( const unsigned int _L  , // size of the board
		const double _deg , // deg in [0:1]: amount of fields with `1'
		const unsigned long _seed = 0   // seed for the RNG
     ) 
: L( _L ) , data( new int[ L * L ] )
{ 
	if( L < 2 )
	{
		fprintf( stderr , "Make L larger than 1! You set %d\n" , L ) ;
		std::exit( 1 ) ;
	}
	if( _deg == 0. )
		// std::memset( data , -1 , L*L*sizeof( int ) ) ;  
		for( unsigned int i = 0 ; i < L * L ; i++ ) data[i] = -1 ; 
	else
	{
		if( _deg == 1. )
		{
			 for( unsigned int i = 0 ; i < L * L ; i++ ) data[i] = 1 ; 
		}
		else // _deg in (0:1)
		{

			// initialize RNG
			// gsl_rng_env_setup() ;
			// const gsl_rng_type * typ = gsl_rng_default ;
			gsl_rng * generator = gsl_rng_alloc( gsl_rng_ranlxs2 ) ;

			// gls_rng_set( generator , _seed ) ; // seed generator
			gsl_rng_set ( generator, _seed ) ;

			// initialize board
			for( unsigned int i = 0 ; i < L*L ; i++ )
				if( gsl_rng_uniform( generator ) < _deg ) data[i] = 1 ;
				else data[i] = -1 ;

			// delete RNG
			gsl_rng_free( generator ) ;
		}
	}
	// spins are set -- evaluate energy etc. for this initial condition
	this->evaluate_energy() ;
	this->evaluate_magnetisation() ;
}

board& board::operator=( const board& foo ) 
{
	if( this != &foo ) // no self-assignment
	{
		if( L != foo.L ){ fprintf( stderr , "You can only `=' two boards if they have the same size! Here %i != %i.\n" , L , foo.L ) ; std::exit( 7 ) ; } 

		// get memory for the data to store 
		int * new_data = new int[ L*L ] ;
		copy( foo.data , foo.data + L*L , new_data ) ;
		/*for( unsigned int i = 0 ; i < L*L ; i++ )
			new_data[i] = foo.data[i] ; */
		// free memory currently in data -- otherwise it'll be lost...
		delete[] data ;
		// now put the newly acquired data from foo into this instance's data
		data = new_data ;
		
		// additional data
		energy = foo.get_energy() ;
		delta_energy = foo.get_delta_energy() ;
		magnetisation = foo.get_magn() ;
	}
	return *this;
}




void board::print_cli( )  const
{
	for( unsigned int j = 0 ; j < L ; j++ ) // row 
	{
		printf( "\n" ) ;
		for( unsigned int i = 0 ; i < L ; i++ ) // column
		{
			if( data[i+L*j] == 1 ) printf( " #" ) ;
			else
				if( data[i+L*j] == -1 ) printf( " ." ) ;
				else printf( "\n > error at data[%i] -- containing value %i\n" , i+L*j , data[i+L*j] ) ;
		}
	}
	printf( "\n" ) ;
}



void board::print_ppm( const char* name ) const 
{
	FILE* filehandle = std::fopen( name , "w" ) ;
	// header
	fprintf( filehandle , "P1\n#\n%i %i\n" , L , L ) ;
	// image info
	for( unsigned int j = 0 ; j < L ; j++ ) // row 
	{
		for( unsigned int i = 0 ; i < L ; i++ ) // column
		{
			if( data[i+L*j] == 1 ) fprintf( filehandle , "1 " ) ;
			else
				if( data[i+L*j] == -1 ) fprintf( filehandle , "0 " ) ;
		}
		fprintf( filehandle , "\n" ) ;
	}
	std::fclose( filehandle ) ;
}

void board::evaluate_energy() 
{
	double H = 0 ; // although values are int use double as the values may become as large as 2 L^2
	// sum over all internal fields (away from the boundary)
	// AND the fields on the lower and right boundary
	// -> boundary conditions don't have to be taken into account yet
	for( unsigned int i = 1 ; i < L ; i++ ) // row 
	{
		for( unsigned int j = 1 ; j < L ; j++ ) // column
		{
			// spin at (i,j) interacts with its four neighbours
			// but we'll use only the interaction to the top and
			// the left one as the interaction with the right
			// (bottom) one will be computed when it comes to the
			// right (bottom) neighbour. So after all summing, the
			// energy is 2 x H.
			//
			// the actual interaction between spins s1 and s2 is 
			//     - s1 s2
			H += - data[ j+L*i ]* data[ (j-1) + L*i ] ;
			H += - data[ j+L*i ]* data[ j + L*(i-1) ] ;
		}
	}
	// sum over margin-fields -- and mind periodic boundary conditions in
	// every (thus 2) dimension!
	// 1. top margin (without upper left corner)
	{  unsigned int i = 0 ; // row
		for( unsigned int j = 1 ; j < L ; j++ ) // column
		{
			H += - data[ j+L*i ] * data[ (j-1) + L*i ] ;
			H += - data[ j+L*i ] * data[ j + L* (L-1) ] ;
		}
	}
	// 2. left margin (without upper left corner)
	for( unsigned int i = 1 ; i < L ; i ++ )
	{
		{ unsigned int j = 0 ;
			H += - data[ j+L*i ] * data[ (L-1) + L*i ] ;
			H += - data[ j+L*i ] * data[ j + L*(i-1) ] ;
		}
	}
	// 3. upper left corner 
	H += - data[ 0 ] * data[ (L-1) + L*0 ] ;
	H += - data[ 0 ] * data[ 0 + L*(L-1) ] ;
	

	// return it as energy
	// every interaction was counted only once, so no factor 2 is needed...
	energy = H ;
}

void board::evaluate_magnetisation() 
{
	int ma = 0 ;
	for( unsigned int i = 0 ; i < L * L ; i++ )
		ma += data[ i ] ;
	magnetisation = ma ;
}

double board::Delta_E( const unsigned int _x , const unsigned int _y )
{
	// sum of all neigbhouring spins (minding the periodic boundary conditions):
	int neighboursum = 0 ;
	neighboursum += data[ ( _x == 0 ? L-1 : _x-1 ) + L*_y ] ; // left neighbour
	neighboursum += data[ ( _x == L-1 ? 0 : _x+1 ) + L*_y ] ; // right neighbour
	neighboursum += data[  _x + L * ( _y == 0 ? L-1 : _y-1 ) ] ; // upper neighbour
	neighboursum += data[  _x + L * ( _y == L-1 ? 0 : _y+1 ) ] ; // lower neighbour

	// the spin at _x,_y will always change 2 -- either decrease (-2) or increase (+2)
	// it increases if it was a -1 before
	// but since the energy has a `-' sign in front of the spin-product:
	
	delta_energy = ( data[ _x + L*_y ] == 1 ? 2 : -2 ) * neighboursum ;
	
	return delta_energy ;
}


void board::flip(  const unsigned int _x , const unsigned int _y , const bool Delta_E_used_before = false ) 
{
	// you can speed up this if you set the Delta_E_used_before bolean to
	// true -- but then the Function Delta_E really must have been caled
	// prior to flip() as flip then relies on the private variable
	// delta_energy and does not compute it again...
	if( Delta_E_used_before )
	{
		energy += delta_energy ;
	}
	else
	{
		double delta = this->Delta_E( _x , _y ) ;
		energy += delta ;
	}

	// do the actual flip...
	data[ _x + L*_y ] *= -1 ;


	// change magnetisation
	magnetisation += 2 * data[ _x + L*_y ] ;
	
}



void board::save_to_file( const char* filename ) const 
{
	FILE * op = std::fopen( filename , "w" ) ;
	fprintf( op , "%i\n" , L ) ;
	for( unsigned int i = 0 ; i < L*L ; i++ )
		fprintf( op , "%i " , data[i] ) ;
	fprintf( op , "\n" ) ;

	/*
	for( unsigned int i = 0 ; i < L*L ; i+=10 )
		fprintf( op , "%i %i %i %i %i %i %i %i %i %i\n" , data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7], data[i+8], data[i+9] ) ;
	for( unsigned int i = L/10 ; i < L ; i++ ) 
		fprintf( op , "%i " , data[i] ) ;
	fprintf( op , "\n" ) ;
	*/

	std::fclose( op ) ;
}



board::board( const unsigned int _L , const char* filename ) 
: L( _L ) , data( new int[ L*L ] ) 
{
	// printf( "Reading from file %s ...\n" , filename ) ;

	FILE * fh = std::fopen( filename , "r" ) ;
	unsigned int* compare_L = new unsigned int ;
	std::fscanf( fh , "%i\n" , compare_L ) ;
	// printf( "Read L = %i\n" , *compare_L ) ;
	if( L != *compare_L ){ fprintf( stderr , "Error while loading %s: %i != %i\n" , filename , L , *compare_L ) ; std::exit( 5 ) ; }
	// get data
	for( unsigned int i = 0 ; i < L*L ; i++ )
		std::fscanf( fh , "%i " , data + i ) ;
	std::fclose( fh ) ;

	// spins are set -- evaluate energy etc. for this initial condition
	this->evaluate_energy() ;
	this->evaluate_magnetisation() ;
}



/* deprecated 
double board::energy_neighbourhood( const unsigned int _x , const unsigned int _y ) const
{
	int data_this = data[ _x + L*_y ] ; // shorthand
	// compute energy of this very spin with its neigbourhood before the flipping:
	// mind periodic boundary conditions!
	double energy_before = 0 ;
	energy_before += - data_this * data[ ( _x == 0 ? L-1 : _x-1 ) + L*_y ] ; // left neighbour
	energy_before += - data_this * data[ ( _x == L-1 ? 0 : _x+1 ) + L*_y ] ; // right neighbour
	energy_before += - data_this * data[  _x + L * ( _y == 0 ? L-1 : _y-1 ) ] ; // upper neighbour
	energy_before += - data_this * data[  _x + L * ( _y == L-1 ? 0 : _y+1 ) ] ; // lower neighbour

	return energy_before ;
}

double board::flip_spin( const unsigned int _x , const unsigned int _y ) 
{
	// calculate energy of neighbourhood without flip
	double energy_before = this->energy_neighbourhood( _x , _y ) ;
	// flip that spin
	if( data[ _x + L*_y ] == -1 ) data[ _x + L*_y ] = 1 ;
	else
		if( data[ _x + L*_y ] == 1 ) data[ _x + L*_y ] = -1 ;
		else { fprintf( stderr , "error -- spin %i foud at (%i,%i)\n" , data[_x+L*_y] , _x , _y ) ; std::exit( 3 ) ; }
	double energy_after = this->energy_neighbourhood( _x , _y ) ;

	// energychange is thus
	double Delta_energy = energy_after - energy_before ;

	// this changes the energy of the system
	energy += Delta_energy ;
	return Delta_energy ;
}
*/

#endif // BOARD_H
