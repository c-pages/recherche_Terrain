#ifndef PATCH_H_INCLUDED
#define PATCH_H_INCLUDED

#include <sstream>

namespace patch
{

/////////////////////////////////////////////////
template < typename T >
std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}


/////////////////////////////////////////////////
template < typename T >
double to_float( const T& n )
{
    std::stringstream ss;
    ss << n;
    double f;
    ss >> f;

    return f ;
}



} // fin namesapce patch


#endif // PATCH_H_INCLUDED
