#include<iostream>
#include<cmath>
#include"vec3d.h"

int main()
{
	vec3d foo( 1, 2, 3);
	//std::cout << foo.get_x( ) << '\n';

	vec3d bar;
	bar.set( 4., M_PI, 2.3 );
	std::cout << bar.get(1) << '\t' << bar.get(2) << '\t' << bar.get(3) << '\n';

	vec3d foobar( 1 , 0 , 1 );
	std::cout << foobar.norm(2) << '\n';


	for( int i = 1; i <= 3; i++ )
		std::cout << foo.get(i) << '\t';
	std::cout << '\n';
	vec3d adsf( 3 * ( - foo + bar ) );

	for( int i = 1; i <= 3; i++ )
		std::cout << adsf.get(i) << '\t';
	std::cout << '\n';

	adsf += foo;


	for( int i = 1; i <= 3; i++ )
		std::cout << adsf.get(i) << '\t';
	std::cout << '\n';

}
