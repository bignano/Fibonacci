// Main.cpp : Defines the entry point for the console application.
//

#include "Fibonacci.h"
#include "Integer.h"
#include <iostream>
#include <chrono>

using namespace std;

const char *FILENAME = "fibonacci.txt";

// single mode function pointer
Integer( *fibonacci )(i64); 

// range mode function pointer
Integer( *fibonacci_range )(i64, i64);	

// measure time 
bool benchmark = true;
string mode;

void input()
{
	printf( "n> " );
	string line;
	getline( cin, line );

	size_t comma = line.find( "," );
	cout << endl;

	chrono::time_point<chrono::steady_clock> start;
	chrono::time_point<chrono::steady_clock> end;

	if (comma == string::npos )	// single mode
	{
		int n = atoi( line.c_str() );
		if ( n < 0 ) return;

		start = chrono::high_resolution_clock::now();
		Integer f = fibonacci( n );
		end = chrono::high_resolution_clock::now();

		f.print( Fibonacci::getNumberPrefix( n ) );
		f.toFile( FILENAME );
	}
	else	// range mode
	{
		i64 b = atoll( line.substr( 0, comma ).c_str() );
		i64 e = atoll( line.substr( comma+1, line.length() ).c_str() );

		start = chrono::high_resolution_clock::now();
		fibonacci_range( b, e );
		end = chrono::high_resolution_clock::now();
	}

	if ( benchmark )
	{
		chrono::duration<i64, nano> time = end - start;
		printf( "mode: %s | time: %lli ms", mode.c_str(), time.count()/ 1000000);
	}
	cout << endl;
	input();
}

void help()
{
	cerr << "Usage:\t" << "Fibonacci.exe\t" << "<mode(s)>\nOptions:\n\t" 
		<< "-i, --iter	use iterative function\n\t" 
		<< "-f, --fast	use fast doubling function\n\t"
		<< "-r, --recursive	use recursive function\n\t"
		<< "-b, --benchmark	display statistics\n";
}

int main( int argc, char * argv[] )
{
	// default, change to fastest
	fibonacci = &Fibonacci::fibonacci_iter;
	fibonacci_range = &Fibonacci::fibonacci_iter;
	mode = "iterative";

	if ( argc > 1 )
	{
		string arg1( argv[1] );
		if ( arg1 == "-i" || arg1 == "--iter" )
		{
			fibonacci		= &Fibonacci::fibonacci_iter;
			fibonacci_range = &Fibonacci::fibonacci_iter;
			mode = "iterative";
		}
		else if ( arg1 == "-r" || arg1 == "--recursive" )
		{
			fibonacci		= &Fibonacci::fibonacci_rec;
			fibonacci_range = &Fibonacci::fibonacci_rec;
			mode = "recursive";
		}
		else help();
	}
	if ( argc > 2 )
	{
		if ( string(argv[2]) == "-b" || string( argv[2] ) == "--benchmark" )
			benchmark = true;
		else help();
	}
	if ( argc > 3 ) help();

	input();
	return 0;
}