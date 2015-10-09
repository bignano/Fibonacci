#pragma once
#include <stdint.h>
#include <vector>
#include <string>

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
	
	~Integer();

	/* Operator overloading, add and multiply only */

	Integer operator+( const Integer &other );
	Integer operator*( int n );

	/* Get the representation of the number as string*/
	std::string toString();

	/* Print the number to console, prepending the given string */
	void print(const std::string &prefix="");

	/* Save the number to a file */
	void toFile( const std::string &filename );

private:

	vu64 m_number;
	
	/* Private constructor used to */
	Integer(vu64 number, u64 carry);

	/* Prepend zeros to string up to length l */
	static std::string padString( const std::string &src, int l );

};