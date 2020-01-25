/*****************
 * fibon-rek01b.cpp
 *
 * computes the first n elements of the fibonnacci sequence
 *
 * Version-history
 * 01	prints out first 5 numbers
 * 01b	one int parameter  n  is required; the program outputs the  n-th
 * 	number of the fibonacci sequence
 * 	error handling: if a non-integre is entered as first parameter, 
 * 	it is interpreted as  n = 0.
 *                                                    ********************/




#include<iostream>
#include<cstdlib>


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

int main(int argc, char * argv[])
{
	int n = std::atoi(argv[1]);
	std::cout << fibon(n) << "\n";
}
