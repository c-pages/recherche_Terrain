

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
    if ( ! m_pause ) {
        m_interface->traiterEvenements  ( event );
    }
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
    m_contexte.fenetre->setView  ( m_vuePrincipale );
    m_contexte.fenetre->draw ( m_fond );
    m_contexte.fenetre->draw ( *m_interface );
}



/////////////////////////////////////////////////
void
EcranPause::initGUI  ( )
{
    std::cout << "INITIALISER ECRAN PAUSE\n";

    // Initialisation du fond.
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_contexte.fenetre->getSize() ) );
    m_fond.setFillColor  ( sf::Color (50,65,57 , 150 ));


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
    btnReprendre->lier  (  gui::Actions::Evenement::onBtnG_relacher
                        , [this, fenetrePrincipale ](){
                            retirerEcran();
                            m_pileEcrans->at(0).setPause (false);
                         });
    btnOptions->lier    (  gui::Actions::Evenement::onBtnG_relacher
                        , [this](){
                            setPause ( true );
                            ajouterEcran( app::Ecrans::Options );
                         });
    btnQuitter->lier    (  gui::Actions::Evenement::onBtnG_relacher
                        , [this](){
                         viderEcrans( );
                         ajouterEcran( app::Ecrans::Accueil );  });

    // le clavier //
    m_interface->lier   ( sf::Keyboard::Escape
                        , [this, fenetrePrincipale ](){
                         viderEcrans( );
                         ajouterEcran( app::Ecrans::Accueil );
                        });


}   // fin init GUI




}   // fin namespace app































