#pragma once
#include "Integer.h"
#include <iostream>
#include <string>

class Fibonacci
{
public:

	/* Calculate the nth fibonacci number using a simple
	* iterative approach*/
	static Integer fibonacci_iter( i64 n );

	/* Display fibonacci numbers in range,
	* more efficient than calling fibonacci_iter(n) for each n seperatly	*/
	static Integer fibonacci_iter( i64 begin, i64 end );

	static Integer fibonacci_rec( i64 n );
	static Integer fibonacci_rec( i64 begin, i64 end );

	static std::string getNumberPrefix( i64 n );
};