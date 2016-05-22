

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "appli/ecrans\EcranJeu.h"
#include "appli/Config.h"
#include <iostream>
#include <stdio.h>
//#include "GUI.h"

namespace app {

/////////////////////////////////////////////////
EcranJeu::EcranJeu( Application*  appli )
: Ecran ( appli )
//, m_interface   ( m_appli->getInterface() )
{
    // Initialisation de l'interface graphique.
    initGUI();

    // Demarrer une nouvelle partie
//    m_jeu.demarrerPartie ();

}


/////////////////////////////////////////////////
void EcranJeu::traiter_evenements    ( const sf::Event& event )
{
//    m_jeu.traiterEvenements  ( event );
//    m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranJeu::actualiser            ( sf::Time deltaT )
{
//    m_jeu.actualiser ( deltaT );
//    m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranJeu::dessiner ()
{
//    Ecran::m_appli->getFenetre()->draw (  );
}



/////////////////////////////////////////////////
void
EcranJeu::initGUI  ( )
{

    // Initialisation du fond.
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_appli->getFenetre()->getSize() ) );
    m_fond.setFillColor  ( sf::Color (50,50,50));

}   // fin init GUI




}   // fin namespace app































