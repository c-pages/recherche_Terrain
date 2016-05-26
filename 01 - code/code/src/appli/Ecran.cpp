#include "appli/Ecran.h"
#include "appli/Gestion_ecrans.h"

#include <stdio.h>

namespace app {

/////////////////////////////////////////////////
Ecran::Ecran( Gestion_ecrans&  pileEcrans , Contexte contexte )
: m_pileEcrans  ( &pileEcrans )
, m_contexte    ( contexte )
{
    //ctor
}

/////////////////////////////////////////////////
Ecran::~Ecran()
{
//    printf ("DEstruction de l'ecran abstrait");
    //dtor
}




/////////////////////////////////////////////////
void Ecran::ajouterEcran( Ecrans::ID ecranID )
{
    m_pileEcrans->ajouter( ecranID );
}


/////////////////////////////////////////////////
void Ecran::retirerEcran( )
{
    m_pileEcrans->retirer( );
}


/////////////////////////////////////////////////
void Ecran::viderEcrans( )
{
    m_pileEcrans->vider( );
}







} // fin app
