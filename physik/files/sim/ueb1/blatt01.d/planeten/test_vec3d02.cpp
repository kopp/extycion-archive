#include<iostream>
#include"vec3d.h"

int main()
{
	vec3d foo( 1, 1, 1 );
	vec3d bar( 1, 2, -3);
	vec3d duh( 0, 2, 4);

	vec3d asdf( foo + bar + duh);
	print_cli(asdf,true);
}
