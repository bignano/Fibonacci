#include "Fibonacci.h"

using namespace std;

Integer Fibonacci::fibonacci_iter( i64 n )
{
	if ( n < 2 )
		return Integer( n );

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

Integer Fibonacci::fibonacci_iter( i64 begin, i64 end )
{
	if ( !(begin <= end && begin >= 0) )
	{
		std::cerr << "erorr: use 0 <= start <= finish\n";	
		return Integer( 101 );
	}

	if ( begin < 2 )
	{
		if ( begin == 0 )
			Integer( 0 ).print( getNumberPrefix( 0 ) );
		if ( end != 0 )
			Integer( 1 ).print( getNumberPrefix( 1 ) );
	}

	Integer a, b( 1 ), c;
	for ( int i = 2; i <= end; i++ )
	{
		c = a + b;
		a = b;
		b = c;
		if ( i >= begin )
			c.print( getNumberPrefix( i ) );
	}
	return c;
}

Integer Fibonacci::fibonacci_rec( i64 n )
{
	if ( n < 2 ) return Integer(n);
	return fibonacci_rec( n - 1 ) + fibonacci_rec( n - 2 );
}

Integer Fibonacci::fibonacci_rec( i64 begin, i64 end )
{
	cerr << "Range not available in recursive mode.\n";
	return Integer( 911 );
}

string Fibonacci::getNumberPrefix( i64 n )
{
	return to_string( n ).append( ":\t" );
}