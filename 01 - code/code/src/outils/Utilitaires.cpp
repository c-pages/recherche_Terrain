

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "outils/Utilitaires.h"

#include <sstream>



/////////////////////////////////////////////////
float       toFloat(const std::string&  str  )
{
    std::istringstream  iss     ( str );
    float f_val = 0;
    iss >> f_val;
    return f_val;
}
