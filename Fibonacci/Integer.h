#pragma once
#include <stdint.h>
#include <vector>
#include <string>

// 64-bit signed integer for human input (that may be negative)
typedef int64_t i64;
// 64-bit unsigned integer, single number block
typedef uint64_t u64;
// vector of number blocks
typedef std::vector<u64> vu64;

/* Represent huge non-negative integers
 * and perform basic arithmetic on them.
 
 * Every 18 digits are stored in a 64-bit unsigned int,
 * called a number block.

 * Every two number block are added while the remainder is
 * used in the next calculation.

 * The theoretical bound for the number of digits depends
 * on the available RAM, which is how it can store many many digits.
*/
class Integer
{
public:

	/* Integer(0) */
	Integer();

	/* Represent n as Integer*/
	Integer( u64 n );
	
	Integer( const Integer& src );

	~Integer();

	/* Operator overloading, add and multiply only */

	Integer operator+( const Integer &other );
	Integer operator*( int n );
	Integer& operator=( const Integer &src );
	bool operator==( const Integer &other );

	/* Get the representation of the number as string*/
	std::string toString();

	/* Print the number to console, prepending and appending the given strings */
	void print( const std::string &prefix = "" );

	/* Save the number to a file */
	void toFile( const std::string &filename );

private:

	u64*  m_number;
	i64 m_size;
	std::string m_string;
	//bool owner;

	/* Private constructor used to */
	Integer(u64* number, i64 size);

	/* Prepend zeros to string up to length l */
	static std::string padString( const std::string &src, int l );

};