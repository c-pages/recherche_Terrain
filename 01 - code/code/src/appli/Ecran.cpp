#include "appli/Ecran.h"
#include "appli/Gestion_ecrans.h"

#include <stdio.h>

namespace app {

/////////////////////////////////////////////////
Ecran::Ecran( Gestion_ecrans&  pileEcrans , Contexte contexte )
: m_pileEcrans  ( &pileEcrans )
, m_contexte    ( contexte )
{

    /// Initialisation de la vue ///
//    auto    tailleCarte     = m_jeu.getTailleCarte();
    auto    taillefenetre   = m_contexte.fenetre->getSize();
    m_vuePrincipale.setSize     ( {taillefenetre.x, taillefenetre.y} );
    m_vuePrincipale.setCenter   ( taillefenetre.x/2, taillefenetre.y/2 );

    m_vueInterface.setSize      ( {taillefenetre.x, taillefenetre.y} );
//    m_vueInterface.setViewport  ( sf::FloatRect(0, 0, 1, 1));
    m_vueInterface.setCenter    ( taillefenetre.x/2, taillefenetre.y/2 );
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
