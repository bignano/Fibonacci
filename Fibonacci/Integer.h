#pragma once
#include <stdint.h>
#include <vector>
#include <string>

typedef uint64_t u64;
typedef std::vector<u64> vu64;

class Integer
{
public:
	Integer();
	Integer( u64 n );
	~Integer();

	Integer operator+( const Integer &other );
	Integer operator*( int n );

	std::string toString();
	void print(const std::string &prefix="");
	void toFile( const std::string &filename );

private:
	vu64 m_number;
	
	Integer(vu64 number, u64 carry);

	static std::string padString( const std::string &src, int l );

};