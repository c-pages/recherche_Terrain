#ifndef UTILITAIRES_H
#define UTILITAIRES_H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <sstream>




// conversions d'un nombre en string
// (le "to_string" sur MinGW marche pas alors on refait le notre )
template <typename T>
std::string toString(const T& value);

// conversions d'un string en float
float       toFloat(const std::string&   str );



///////////////////////////////////////
#include <outils/Utilitaires.inl>







#endif // UTILITAIRES_H
