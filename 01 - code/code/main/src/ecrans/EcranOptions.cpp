

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "ecrans\EcranOptions.h"
#include <iostream>
#include <cstdio>
#include "Config.h"

#include "gui.h"

namespace app {

/////////////////////////////////////////////////
EcranOptions::EcranOptions( Application*  appli )
: Ecran         ( appli )
, m_interface   ( m_appli->getInterface() )
{
    // Initialisation de l'interface graphique.
    initGUI();

}

/////////////////////////////////////////////////
EcranOptions::~EcranOptions()
{
//    m_fenetre->demander_a();
    m_fenetre->demander_aEtre_supprimer();
}


/////////////////////////////////////////////////
void EcranOptions::traiter_evenements    ( const sf::Event& event )
{
//    m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranOptions::actualiser            ( float deltaT )
{
//    m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranOptions::dessiner ()
{
    Ecran::m_appli->getFenetre()->draw ( m_fond );
//    Ecran::m_appli->getFenetre()->draw ( *m_interface );

}


/////////////////////////////////////////////////
void
EcranOptions::initGUI  ( )
{
    // Initialisation du fond.
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_appli->getFenetre()->getSize() ) );
    m_fond.setFillColor  ( sf::Color (100,100,50, 200));


    using namespace gui;

    // Creation de l'interface qui gère un ensemble de gadget.
//    m_interface = std::make_shared<Interface>( m_appli->getFenetre() );
//    m_interface->setAfficherFPS ( true );

    std::shared_ptr<BtnTexte>   btnRetour         = m_interface->creer.boutonTexte( "Retour" );
    std::shared_ptr<BtnTexte>   btnQuitter         = m_interface->creer.boutonTexte( "Quitter" );

    m_fenetre            = m_interface->creer.fenetre( "Options" );

    m_fenetre->ajouter ( btnRetour );
    m_fenetre->ajouter ( btnQuitter );
    m_fenetre->setTaille ( 500, 200 );
    m_fenetre->setPosition ( 800, 600);

    btnRetour->alignerSur( m_fenetre , Alignement::Centre, Alignement::Centre );
    btnQuitter->alignerSur( btnRetour , Alignement::Haut, Alignement::Bas );
    btnQuitter->move (0,5);

    auto fctRetour = [this](){
        printf ("Retour\n");
        m_appli->retirerEcran();
    };
    auto fctQuitter = [this](){
        printf ("Quitter\n");
        m_appli->getFenetre()->close();
    };

    btnRetour->lier( Evenement::onBtnG_relacher, fctRetour );
    btnQuitter->lier( Evenement::onBtnG_relacher, fctQuitter );

    m_fenetre->lier (Evenement::onFen_fermer, fctRetour );

}   // fin init GUI




}   // fin namespace app































