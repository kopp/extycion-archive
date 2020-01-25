/*****************
 * fibon-rek01c.cpp
 *
 * computes the first n elements of the fibonnacci sequence and gives
 * verbose output if second flag is nonempty:
 * <n>   <fibon(n)>   <exec. time [sec]>
 *
 * Version-history
 * 01	prints out first 5 numbers
 * 01b	one int parameter  n  is required; the program outputs the  n-th
 * 	number of the fibonacci sequence
 * 	error handling: if a non-integre is entered as first parameter, 
 * 	it is interpreted as  n = 0.
 * 01c	if second flag is nonempty give verbose output (see above)
 *                                                    ********************/




#include<iostream>	//for cout
#include<cstdlib>	//for atoi
#include<ctime>		//to measure execution time


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
	bool verbose = false;
	if ( argv[2] != NULL )
	{
		verbose = true;
	}

	int n = std::atoi(argv[1]);

	if ( verbose )
	{
		std::cout << n << "\t";
		clock_t timestamp_start = std::clock();
		std::cout << fibon(n) << "\t";
		clock_t timestamp_stop = std::clock();
		double duration = (double) (timestamp_stop - timestamp_start)/ CLOCKS_PER_SEC;
		std::cout << duration << "\n";
	}
	else
	{
		std::cout << fibon(n) << "\n";
	}
}
