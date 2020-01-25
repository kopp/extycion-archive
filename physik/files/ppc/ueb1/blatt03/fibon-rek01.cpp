/*****************
 * fibon-rek01.cpp
 *
 * computes the first five numbers of the fibonnacci sequence
 *
 *                                                    ********************/



#include<iostream>


int fibon(int i)
{
	if ( (i==1) || (i==0) )
	{
		return 1;
	}
	else
	{
		return (fibon(i-1) + fibon(i-2)) ;
	}
}

int main()
{
	std::cout << fibon(0) << " " ;
	std::cout << fibon(1) << " " ;
	std::cout << fibon(2) << " " ;
	std::cout << fibon(3) << " " ;
	std::cout << fibon(4) << " " ;
	std::cout << fibon(5) << "\n" ;
}
