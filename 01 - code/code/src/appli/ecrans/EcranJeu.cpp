

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
EcranJeu::EcranJeu( Gestion_ecrans&  pileEcrans , Contexte contexte  )
: Ecran         ( pileEcrans,  contexte )
, m_interface   ( std::make_shared<gui::Gui>( m_contexte.fenetre ) )
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

    if ( ! m_pause )
        m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranJeu::actualiser            ( sf::Time deltaT )
{
//    m_jeu.actualiser ( deltaT );
    if ( ! m_pause )
        m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranJeu::dessiner ()
{
    m_contexte.fenetre->draw ( m_fond );
    m_contexte.fenetre->draw ( *m_interface );
}



/////////////////////////////////////////////////
void
EcranJeu::initGUI  ( )
{

    // Initialisation du fond.
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_contexte.fenetre->getSize() ) );
    m_fond.setFillColor  ( sf::Color (50,50,50 , 150));


    /// l'interface graphique //////
/*    // la fenetre //
    auto   fenetrePrincipale   =   m_interface->creer.fenetre( "  Options" , { 230, 125 }, true );
    fenetrePrincipale->aligner      ( m_interface );
    fenetrePrincipale->setVisible   ( false );

    // les boutons //
    sf::Vector2i tailleBtn = { 200 , 20 } ;
    auto    btnReprendre      =   m_interface->creer.bouton( "rePreNDre" , tailleBtn );
    auto    btnOptions  =   m_interface->creer.bouton( "OPtiOnS" , tailleBtn );
    auto    btnQuitter  =   m_interface->creer.bouton( "Retour Accueil" , tailleBtn );

    fenetrePrincipale->ajouterEnfant    ( btnReprendre );
    fenetrePrincipale->ajouterEnfant    ( btnOptions );
    fenetrePrincipale->ajouterEnfant    ( btnQuitter );

    btnReprendre->aligner( fenetrePrincipale );
    btnReprendre->setPosition ( btnReprendre->getPosition ().x, 10. );
    btnOptions->aligner( btnReprendre );
    btnOptions->move( 0 , 30 );
    btnQuitter->aligner( btnOptions );
    btnQuitter->move( 0 , 30 );

    /// interactions //////
    // les boutons //
    btnReprendre->lier  (  gui::Actions::Evenement::onBtnG_relacher
                        , [this, fenetrePrincipale ](){  m_pause = false; fenetrePrincipale->setVisible ( false );  });
    btnOptions->lier    (  gui::Actions::Evenement::onBtnG_relacher
                        , [this](){  std::cout << "Options\n"; });
    btnQuitter->lier    (  gui::Actions::Evenement::onBtnG_relacher
                        , [this](){  m_appli->changerEcran( Application::Ecrans::Accueil );  });
*/
    // le clavier //
    m_interface->lier   ( sf::Keyboard::Escape
                        , [this ](){
                         ajouterEcran ( app::Ecrans::Pause );
                         });
}   // fin init GUI




}   // fin namespace app































