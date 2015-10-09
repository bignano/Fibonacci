#include "Integer.h"
#include <fstream>

using namespace std;

Integer::Integer()
{
	Integer( 0 );
}

Integer::Integer( u64 n )
{	
	// single block with value n 
	m_number = vu64( { n } );
}

Integer::Integer( vu64 number, u64 carry )
{
	m_number = number;
	if ( carry != 0 )	// carry = 0 means no carry
		m_number.push_back(carry);
}

Integer::~Integer()
{}

Integer Integer::operator+( const Integer &other )
{
	// 10 to the max number of digits in one u64 (18)
	const u64 dig = 1000000000000000000;

	/* find which number is longer and which is shorter */
	const vu64 &max = m_number.size() > other.m_number.size() ? m_number : other.m_number;
	const vu64 &min = m_number.size() > other.m_number.size() ? other.m_number : m_number;

	u64 carry = 0; 

	// pre-allocate for speed
	vu64 next = vu64( max.size() );

	// iterate through all number blocks and adding,
	// with carrying the 19th digit
	for ( size_t i = 0; i < max.size(); i++ )
	{
		u64 result = max[i] + carry;

		// to prevent out-of-bounds
		if ( i < min.size() )
			result += min[i];

		// keep the 19th digit
		carry = result / dig;

		// remove the 19th digit from result
		next[i] = result - carry * dig;
	}

	return Integer( next, carry );
}

Integer Integer::operator*( int n )
{
	/* add this to itself n times */
	Integer result;
	for ( int i = 0; i < n; i++ )
		result = result + (*this);
	return result;
}

bool Integer::operator==( const Integer &other )
{
	return m_number == other.m_number;
}

std::string Integer::padString( const std::string &src, int l )
{
	string pad = src;
	for ( size_t i = 0; i < l - src.length(); i++ )
		pad = string( "0" ).append( pad );
	return pad;
}

string Integer::toString()
{
	if ( !m_string.empty() ) return m_string;

	int lastItemIdx = (int)(m_number.size() - 1);

	// don't pad the left-most number block
	m_string = to_string( m_number[lastItemIdx] );

	// pad all the rest 
	if ( lastItemIdx > 0 )
		for ( int i = lastItemIdx - 1; i >= 0; i-- )
			m_string = m_string.append( padString( to_string( m_number[i] ), 18 ) );

	return m_string;
}

void Integer::print(const string &prefix )
{
	printf( "%s%s\t(%zu)\n", prefix.c_str(), toString().c_str(), toString().length() );
}

void Integer::toFile( const string &filename )
{
	ofstream out( filename );
	out << toString();
}