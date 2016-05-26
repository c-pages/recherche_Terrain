

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "appli/ecrans\EcranAccueil.h"
#include "appli/Config.h"
#include <iostream>
#include <cstdio>

//#include "gui.h"

namespace app {

/////////////////////////////////////////////////
EcranAccueil::EcranAccueil( Gestion_ecrans&  pileEcrans , Contexte contexte  )
: Ecran         ( pileEcrans,  contexte )
//, m_interface   ( std::make_shared<gui::Gui>( contexte.fenetre ) )
{
    m_interface   = std::make_shared<gui::Gui>( m_contexte.fenetre ) ;

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
    if ( ! m_pause )
        m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranAccueil::actualiser            ( sf::Time deltaT )
{
    if ( ! m_pause )
        m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranAccueil::dessiner ()
{
    m_contexte.fenetre->draw ( m_fond );
    m_contexte.fenetre->draw ( *m_interface );

}



/////////////////////////////////////////////////
void
EcranAccueil::initGUI  ( )
{
    /// Initialisation du fond. ///
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_contexte.fenetre->getSize() ) );
    m_fond.setFillColor  ( sf::Color (50,70,50));
    m_fond.setTexture    ( &Config::ms_textures.get ( Config::Images::FondAccueil ) );

    /// l'interface graphique //////
    // la fenetre //
    auto   fenetrePrincipale   =   m_interface->creer.fenetre( "  meTaORGanISmE" , { 230, 125 }, true );
    fenetrePrincipale->aligner( m_interface );

    // les boutons //
    sf::Vector2i tailleBtn = { 200 , 20 } ;
    auto    btnNEW      =   m_interface->creer.bouton( "Nouvel partiE" , tailleBtn );
    auto    btnOptions  =   m_interface->creer.bouton( "OPtionS" , tailleBtn );
    auto    btnQuitter  =   m_interface->creer.bouton( "quITteR" , tailleBtn );

    fenetrePrincipale->ajouterEnfant    ( btnNEW );
    fenetrePrincipale->ajouterEnfant    ( btnOptions );
    fenetrePrincipale->ajouterEnfant    ( btnQuitter );

    btnNEW->aligner( fenetrePrincipale );
    btnNEW->setPosition ( btnNEW->getPosition ().x, 10. );
    btnOptions->aligner( btnNEW );
    btnOptions->move( 0 , 30 );
    btnQuitter->aligner( btnOptions );
    btnQuitter->move( 0 , 30 );

    /// interactions //////
    // les boutons //
    btnNEW->lier        (  gui::Actions::Evenement::onBtnG_relacher
                        , [this](){
                         retirerEcran();
                         ajouterEcran( app::Ecrans::Jeu );
                         });
    btnOptions->lier    (  gui::Actions::Evenement::onBtnG_relacher
                        , [this](){  ajouterEcran( app::Ecrans::Options ); });
    btnQuitter->lier    (  gui::Actions::Evenement::onBtnG_relacher
                        , [this](){  m_contexte.fenetre->close();  });

    // le clavier //
    m_interface->lier   ( sf::Keyboard::Escape
                        , [this](){
                         std::cout << "ACCUEIL:Escape\n";
                         m_contexte.fenetre->close();  });


}   // fin init GUI




}   // fin namespace app































