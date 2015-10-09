#include "Integer.h"
#include <fstream>

using namespace std;

Integer::Integer()
{
	Integer( 0 );
}

Integer::Integer( u64 n )
{
	m_number = vu64( { n } );
}

Integer::Integer( vu64 number, u64 carry )
{
	m_number = number;
	if ( carry != 0 )
		m_number.push_back(carry);
}

Integer::~Integer()
{}

Integer Integer::operator+( const Integer &other )
{
	const u64 dig = 1000000000000000000;

	const vu64 &max = m_number.size() > other.m_number.size() ? m_number : other.m_number;
	const vu64 &min = m_number.size() > other.m_number.size() ? other.m_number : m_number;

	u64 carry = 0; 

	vu64 next = vu64( max.size() );

	for ( size_t i = 0; i < max.size(); i++ )
	{
		u64 result = max[i] + carry;

		if ( i < min.size() )
			result += min[i];

		carry = result / dig;
		next[i] = result - carry * dig;
	}

	return Integer( next, carry );
}

Integer Integer::operator*( int n )
{
	Integer result;
	for ( int i = 0; i < n; i++ )
		result = result + (*this);
	return result;
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
	int lastItemIdx = (int)(m_number.size() - 1);

	string s = to_string( m_number[lastItemIdx] );

	if ( lastItemIdx > 0 )
		for ( int i = lastItemIdx - 1; i >= 0; i-- )
			s = s.append( padString( to_string( m_number[i] ), 18 ) );

	return s;
}

void Integer::print(const string &prefix)
{
	printf( "%s%s\n", prefix.c_str(), toString().c_str() );
}

void Integer::toFile( const string &filename )
{
	ofstream out( filename );
	out << toString();
}