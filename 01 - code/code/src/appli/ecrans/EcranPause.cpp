

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "appli/ecrans\EcranPause.h"
#include "appli/Config.h"
#include <iostream>
#include <stdio.h>


namespace app {

/////////////////////////////////////////////////
EcranPause::EcranPause( Gestion_ecrans&  pileEcrans , Contexte contexte  )
: Ecran         ( pileEcrans,  contexte )
, m_interface   ( std::make_shared<gui::Gui>( m_contexte.fenetre ) )
{
    // Initialisation de l'interface graphique.
    initGUI();

}


/////////////////////////////////////////////////
void EcranPause::traiter_evenements    ( const sf::Event& event )
{
    if ( ! m_pause )
        m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranPause::actualiser            ( sf::Time deltaT )
{
    if ( ! m_pause )
        m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranPause::dessiner ()
{
    m_contexte.fenetre->draw ( m_fond );
    m_contexte.fenetre->draw ( *m_interface );
    std::cout << "EcranPause::dessiner \n";
}



/////////////////////////////////////////////////
void
EcranPause::initGUI  ( )
{
    std::cout << "INIT GUI DE L4ECRAN PAUSE\n";

    // Initialisation du fond.
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_contexte.fenetre->getSize() ) );
    m_fond.setFillColor  ( sf::Color (50,65,57));


    /// l'interface graphique //////
    // la fenetre //
    auto   fenetrePrincipale   =   m_interface->creer.fenetre( "  PAUsE" , { 230, 125 }, true );
    fenetrePrincipale->aligner      ( m_interface );
//    fenetrePrincipale->setVisible   ( false );

    // les boutons //
    sf::Vector2i tailleBtn = { 200 , 20 } ;
    auto    btnReprendre    =   m_interface->creer.bouton( "rePreNDre" , tailleBtn );
    auto    btnOptions      =   m_interface->creer.bouton( "OPtiOnS" , tailleBtn );
    auto    btnQuitter      =   m_interface->creer.bouton( "Retour Accueil" , tailleBtn );

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
//    btnReprendre->lier  (  gui::Actions::Evenement::onBtnG_relacher
//                        , [this, fenetrePrincipale ](){  m_appli->retirerEcran();  });
//    btnOptions->lier    (  gui::Actions::Evenement::onBtnG_relacher
//                        , [this](){  m_appli->ajouterEcran( app::Application::Ecrans::Options ); });
//    btnQuitter->lier    (  gui::Actions::Evenement::onBtnG_relacher
//                        , [this](){
//                         m_appli->retirer( 0 );
//                         m_appli->changerEcran( Application::Ecrans::Accueil );  });
//
//    // le clavier //
//    m_interface->lier   ( sf::Keyboard::Escape
//                        , [this, fenetrePrincipale ](){
//                         std::cout << "PAUSE:Escape\n";
//                            m_appli->retirerEcran(); });


}   // fin init GUI




}   // fin namespace app































