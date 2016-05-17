
/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Gestion_ecrans.h"

namespace app
{
/////////////////////////////////////////////////
void    Gestion_ecrans::ajouter ( Ecran* ecran )
{
    m_pile.push_back( ecran );
}


/////////////////////////////////////////////////
void    Gestion_ecrans::retirer ()
{
    delete *(m_pile.end() - 1);
//    delete ptr;
    m_pile.pop_back();
}


/////////////////////////////////////////////////
void    Gestion_ecrans::vider()
{
    //   Retirer tous les écrans actifs de la pile.
    while(!m_pile.empty())
        retirer();
}


/////////////////////////////////////////////////
bool    Gestion_ecrans::estVide ()
{
    return m_pile.empty();
}


/////////////////////////////////////////////////
void    Gestion_ecrans::changer ( Ecran* ecran )
{
    if(!m_pile.empty())
        retirer();
    ajouter( ecran );
}


/////////////////////////////////////////////////
Ecran*  Gestion_ecrans::courant ( )
{
    if(m_pile.empty()) return nullptr;
    return *m_pile.end() - 1 ;
}


/////////////////////////////////////////////////
void    Gestion_ecrans::traiter_evenements (sf::Event event )
{
    for ( Ecran* ecran : m_pile )
        ecran->traiter_evenements( event );
}


/////////////////////////////////////////////////
void    Gestion_ecrans::actualiser ( sf::Time deltaT )
{
    for ( Ecran* ecran : m_pile )
        ecran->actualiser( deltaT );
}


/////////////////////////////////////////////////
void    Gestion_ecrans::dessiner ()
{
   for ( Ecran* ecran : m_pile )
      ecran->dessiner();
}
}// fin app
