// Fibonacci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Integer.h"
#include <chrono>
#include <iostream>

using namespace std;

const char *FILENAME = "fibonacci.txt";

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
			printf( "in fibonacci(%i)...\r", i );
	}
	return c;
}

void input()
{
	printf( "get the nth fibonacci number:\nn> " );
	string line;
	getline( cin, line );
	int n = atoi( line.c_str() );
	if ( n < 0 )
		return;
	Integer f = fibonacci( n );
	f.print();
	f.toFile( FILENAME );
	input();
}

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
		if ( (arg1 == "-v" || arg1 == "--value") && argc == 3 )
		{
			Integer fi = fibonacci( atoi( argv[2] ) );
			printf( "%i:\t%s\n", atoi( argv[2] ), fi.toString().c_str() );
			fi.toFile( FILENAME );
		}

		else if ( (arg1 == "-r" || arg1 == "--range") && argc == 4 && atoi(argv[2]) <= atoi(argv[3]))
		{
			for ( int i = atoi( argv[2] ); i < atoi( argv[3] ); i++ )
				printf( "%i:\t%s\n", i, fibonacci( i ).toString().c_str() );
		}
		else help();
	}
    return 0;
}

