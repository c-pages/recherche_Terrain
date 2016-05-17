

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "ecrans\EcranAccueil.h"
#include <iostream>
#include <cstdio>
#include "Config.h"

#include "gui.h"

namespace app {

/////////////////////////////////////////////////
EcranAccueil::EcranAccueil( Application*  appli )
: Ecran         ( appli )
, m_interface   ( m_appli->getInterface() )
{
    // Initialisation de l'interface graphique.
    initGUI();

}
/////////////////////////////////////////////////
EcranAccueil::~EcranAccueil( )
{
    // vide l'interface
//    m_interface->reinitialiser();
}

/////////////////////////////////////////////////
void EcranAccueil::traiter_evenements    ( const sf::Event& event )
{
//    m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranAccueil::actualiser            ( float deltaT )
{
//    m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranAccueil::dessiner ()
{
    m_appli->getFenetre()->draw ( m_fond );
//    Ecran::m_appli->getFenetre()->draw ( *m_interface );

}



/////////////////////////////////////////////////
void
EcranAccueil::initGUI  ( )
{
    // Initialisation du fond.
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_appli->getFenetre()->getSize() ) );
    m_fond.setFillColor  ( sf::Color (50,100,50));

    using namespace gui;


    std::shared_ptr<BtnTexte>   btnNouvellePartie  = m_interface->creer.boutonTexte( "Nouvelle partie" );
    std::shared_ptr<BtnTexte>   btnQuitter         = m_interface->creer.boutonTexte( "Quitter" );

    std::shared_ptr<Fenetre>    fenetre            = m_interface->creer.fenetre( "SuperOrganisme" );
    fenetre->ajouter ( btnNouvellePartie );
    fenetre->ajouter ( btnQuitter );
    fenetre->setTaille ( 500, 200 );
    fenetre->alignerSur ( m_interface , Alignement::Centre, Alignement::Centre );

    btnNouvellePartie->alignerSur( fenetre , Alignement::Centre, Alignement::Centre );
    btnQuitter->alignerSur( btnNouvellePartie , Alignement::Haut, Alignement::Bas );
    btnQuitter->move (0,10);


    // comportement de l'interface
    auto fctQuitter = [this](){
        printf ("Quitter\n");
        m_appli->getFenetre()->close();
    };
    auto fctNouvellePartie = [this](){
        printf ("NouvelleParite\n");

        m_interface->reinitialiser();
        m_appli->changerEcran( Application::Ecrans::Jeu );
    };
    m_interface->lier (sf::Keyboard::Escape , fctQuitter );
    btnNouvellePartie->lier( Evenement::onBtnG_relacher, fctNouvellePartie );
    btnQuitter->lier( Evenement::onBtnG_relacher, fctQuitter );


}   // fin init GUI




}   // fin namespace app































