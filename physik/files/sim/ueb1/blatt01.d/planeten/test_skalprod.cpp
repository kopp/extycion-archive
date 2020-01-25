#include<iostream>
#include"vec3d.h"

int main()
{
	vec3d foo( 1,2,3 );
	vec3d bar( -2,0,1 );

	std::cout << foo * bar << '\n';
}
