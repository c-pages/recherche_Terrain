#include "Ecran.h"
#include <stdio.h>

namespace app {

/////////////////////////////////////////////////
Ecran::Ecran( Application*  appli )
:   m_appli  ( appli )
{
    //ctor
}

/////////////////////////////////////////////////
Ecran::~Ecran()
{
//    printf ("DEstruction de l'ecran abstrait");
    //dtor
}

} // fin app
