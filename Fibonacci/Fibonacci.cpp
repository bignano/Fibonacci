// Fibonacci.cpp : Defines the entry point for the console application.
//

#include "Integer.h"
#include <iostream>

using namespace std;

const char *FILENAME = "fibonacci.txt";

/* Calculate the nth fibonacci number using a simple
 * iterative approach
 */
Integer fibonacci( int n )
{
	if ( n < 2 )
		return Integer(n);

	Integer a, b( 1 ), c;
	for ( int i = 1; i < n; i++ )
	{
		c = a + b;
		a = b;
		b = c;
		if ( i % 10000 == 0 )
			printf( "in fibonacci(%i)...\r", i ); // display progress
	}
	return c;
}

// ask user for input, negative stops execution.
void input()
{
	printf( "get the nth fibonacci number:\nn> " );
	string line;
	getline( cin, line );
	int n = atoi( line.c_str() );
	if ( n < 0 )
		return;
	Integer f = fibonacci( n );
	f.print();	// print result
	f.toFile( FILENAME );	// save result to file, as it can be huge
	input();
}

// display usage
void help()
{
	cerr 
		<< "Usage: "  
		<< "\n\t -v, --value [place]" 
		<< "\n\t -r, --range [start] [end]\n";
}

int main(int argc, char * argv[])
{
	if ( argc == 1 )
		input();
	else
	{
		string arg1( argv[1] );
		/* Calc. single value of fibonacci */
		if ( (arg1 == "-v" || arg1 == "--value") && argc == 3 )
		{
			Integer fi = fibonacci( atoi( argv[2] ) );
			printf( "%i:\t%s\n", atoi( argv[2] ), fi.toString().c_str() );
			fi.toFile( FILENAME );
		}

		/* Display a range of values */
		else if ( (arg1 == "-r" || arg1 == "--range") && argc == 4 && atoi(argv[2]) <= atoi(argv[3]))
		{
			for ( int i = atoi( argv[2] ); i < atoi( argv[3] ); i++ )
				printf( "%i:\t%s\n", i, fibonacci( i ).toString().c_str() );
		}
		else help();
	}
    return 0;
}

