/*
 * randomw_begr.cpp
 * bases on randomw.cpp
 *
 * performs a 1-dim random walk with N steps (each +1 or -1) whithin [-a,+a].
 *
 * == usage ==
 * paramter: N (int) , walks (int)
 *
 * == output =
 * if walks given, output will be statistical info:
 * N	< x >	< x^2 >
 * if not, output will be 
 * t	x(t)
 *
 */

#include<iostream>
#include<cstdlib> // rand()
#include<ctime> // time()

#define print_usage std::cout << "usage: randomw number_of_steps [ boundary [ number_of_walks = 1 (activates statistics) ] ] \n"


// // inlines // //

inline double sqr( const double x)
{
	return x * x;
}
inline double abs( const double x)
{
	if( x >= 0 ) return x;
	else return -x ;
}

int main(int argc , char* argv[] )
{

	// // parameter // // 
	
	int N ; //number of steps
	int M = 1; // number of walks
	bool stat = false;
	int a = 20;

	switch( argc )
	{
		case 4:
			M = std::atoi( argv[3] );
			stat = true;
		case 3:
			a = std::atoi( argv[2] );
		case 2:
			N = std::atoi( argv[1] );
			break;
		default:
			print_usage;
			std::exit( 2 );
			break;
	}

	// store final positions only if stat activated
	int* final; // will store final positions
	if( stat ) final = new int [M];

	// initialize generator with time --> produces if stat == false `unique' RWs
	std::srand( time( 0 ) );


	// // random walk loop // //
	
	for( int j = 0; j < M; j++ )
	{
		if( stat ) std::srand( j ); //initialize random number generator for each walk individually
		int x = 0; // position
		for( int i = 0; i < N; i++ )
		{
			// do the magic... -- consider boundary a:
			if ( std::rand() % 2 == 0 ) 	
				if( x == a ) x--; //boundary is a mirror
				else x++;
			else 
				if( x == -a ) x++;
				else x--;
			// output only if no stats are done
			if( ! stat ) std::cout << i << '\t' << x << '\n';
		}
		// store final pos
		if( stat ) final[j] = x;
		
	}



	// // the stats // //
	
	double mean = 0; // < x >
	double squaremean = 0; // < x^2 >
	
	if( stat )
	{
	
		// calcluate

		for( int i = 0; i < M; i++ )
		{
			mean += final[ i ];
			squaremean += sqr( final[i] );
		}
		mean /= M;
		squaremean /= M;

		// output
		std::cout << N << '\t' << mean << '\t' << squaremean << '\n';


		// free memory
		delete[] final;

	}

	




}
