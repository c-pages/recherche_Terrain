

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "ecrans\EcranJeu.h"
#include <iostream>
#include "Config.h"
#include <stdio.h>
//#include "GUI.h"

namespace app {

/////////////////////////////////////////////////
EcranJeu::EcranJeu( Application*  appli )
: Ecran ( appli )
, m_interface   ( m_appli->getInterface() )
{
    // Initialisation de l'interface graphique.
    initGUI();

    // Demarrer une nouvelle partie
    m_jeu.demarrerPartie ();

}


/////////////////////////////////////////////////
void EcranJeu::traiter_evenements    ( const sf::Event& event )
{
    m_jeu.traiterEvenements  ( event );
//    m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranJeu::actualiser            ( sf::Time deltaT )
{
    m_jeu.actualiser ( deltaT );
//    m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranJeu::dessiner ()
{
    Ecran::m_appli->getFenetre()->draw ( m_jeu );
}



/////////////////////////////////////////////////
void
EcranJeu::initGUI  ( )
{

    // Initialisation du fond.
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_appli->getFenetre()->getSize() ) );
    m_fond.setFillColor  ( sf::Color (50,50,50));



    auto fctCreerFenetreOptions = [this](){

        std::shared_ptr<gui::BtnTexte>   btnRetour         = m_interface->creer.boutonTexte( "Retour à la partie en cours" );
        std::shared_ptr<gui::BtnTexte>   btnQuitter         = m_interface->creer.boutonTexte( "Quitter" );
        btnRetour->setAutoAjuster(false);
        btnRetour->setTailleX (400);
        btnQuitter->setAutoAjuster(false);
        btnQuitter->setTailleX (400);

        m_fenetreOptions            = m_interface->creer.fenetre( "Options" );

        m_fenetreOptions->ajouter ( btnRetour );
        m_fenetreOptions->ajouter ( btnQuitter );
        m_fenetreOptions->setTaille ( 500, 200 );
        m_fenetreOptions->setPosition ( 800, 600);

        m_fenetreOptions->alignerSur( m_interface , gui::Alignement::Centre, gui::Alignement::Centre );
        btnRetour->alignerSur( m_fenetreOptions , gui::Alignement::Centre, gui::Alignement::Centre );
        btnQuitter->alignerSur( btnRetour , gui::Alignement::Haut, gui::Alignement::Bas );
        btnQuitter->move (0,5);

        auto fctRetour = [this](){
            printf ("Retour à la partie\n");
            m_pause = false;
            m_fenetreOptions->demander_aEtre_supprimer();
//            m_appli->retirerEcran();
        };
        auto fctQuitter = [this](){
            printf ("Quitter\n");
            m_interface->reinitialiser();
            m_appli->changerEcran( Application::Ecrans::Accueil );
        };

        btnRetour->lier( gui::Evenement::onBtnG_relacher, fctRetour );
        btnQuitter->lier( gui::Evenement::onBtnG_relacher, fctQuitter );

        m_fenetreOptions->lier (gui::Evenement::onFen_fermer, fctRetour );

    };

    // creation des machins
    m_interface->lier ( sf::Keyboard::Escape, [this, fctCreerFenetreOptions]() {
                        if ( ! m_pause ) {
                            printf ("OPTIONS!!!!\n");
                            m_pause = true;
                            fctCreerFenetreOptions();
                        } else {
                            m_pause = false;
                            m_fenetreOptions->demander_aEtre_supprimer();
                        }
                    } );
/*
    using namespace gui;

    // Creation de l'interface qui gère un ensemble de gadget.
    m_interface = std::make_shared<Interface>( m_appli->getFenetre() );
    m_interface->setAfficherFPS ( true );

    m_interface->lier ( sf::Keyboard::Escape, [this]() {
                       printf ("OPTIOPNS!!!!\n");
                       if (! m_afficheEcranOptions ) {

                            m_afficheEcranOptions = true;
                            m_appli->ajouterEcran( Application::Ecrans::Options);
                       } else {
                           m_afficheEcranOptions = false;
                       }
                    } );
*/
}   // fin init GUI




}   // fin namespace app































