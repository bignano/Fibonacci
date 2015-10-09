#include "Integer.h"
#include <fstream>

using namespace std;

Integer::Integer()
{
	// single block with value 0
	m_number = new u64[2];
	m_number[0] = 0;
	m_number[1] = 1;
	m_size = 1;
	//owner = true;
}

Integer::Integer( u64 n )
{	
	// single block with value n 
	m_number = new u64[2];
	m_number[0] = n;
	m_number[1] = 1;
	m_size = 1;
	//owner = true;
}

Integer::Integer( const Integer& src )
{
	m_number = src.m_number;
	m_size = src.m_size;
	m_number[m_size]++;
	//owner = false;
}

Integer::Integer( u64* number, i64 size )
{
	m_number = number;
	m_size = size;
	m_number[m_size] = 1;
	//owner = true;
}

Integer::~Integer()
{
//	if ( owner ) delete[] m_number;
	if ( --m_number[m_size] == 0 )
		delete[] m_number;
}

Integer Integer::operator+( const Integer &other )
{
	// 10 to the max number of digits in one u64 (18)
	const u64 dig = 1000000000000000000;

	/* find which number is longer and which is shorter */
	const Integer& max = m_size > other.m_size ? (*this) : other;
	const Integer& min = m_size > other.m_size ? other : (*this);

	u64 carry = 0;

	u64* next = new u64[max.m_size + 2];

	// iterate through all number blocks and adding,
	// with carrying the 19th digit
	for ( i64 i = 0; i < max.m_size; i++ )
	{
		u64 result = max.m_number[i] + carry;

		// to prevent out-of-bounds
		if ( i < min.m_size )
			result += min.m_number[i];

		// keep the 19th digit
		carry = result / dig;

		// remove the 19th digit from result
		next[i] = result - carry * dig;
	}

	if ( carry != 0 )
	{
		next[max.m_size] = carry;
		return Integer( next, max.m_size + 1 );
	}
	else return Integer( next, max.m_size );
}

Integer Integer::operator*( int n )
{
	/* add this to itself n times */
	Integer result;
	for ( int i = 0; i < n; i++ )
		result = result + (*this);
	return result;
}

Integer& Integer::operator=( const Integer &src )
{
	if ( --m_number[m_size] == 0 )
		delete[] m_number;
	m_number = src.m_number;
	m_size = src.m_size;
	//owner = false;
	m_number[m_size]++;
	return *this;
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
	//if ( !m_string.empty() ) return m_string;

	int lastItemIdx = (int)(m_size - 1);

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