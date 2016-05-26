

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "appli/ecrans\EcranOptions.h"
#include "appli/Config.h"
#include <iostream>
#include <stdio.h>
//#include "GUI.h"

namespace app {

/////////////////////////////////////////////////
EcranOptions::EcranOptions( Gestion_ecrans&  pileEcrans , Contexte contexte  )
: Ecran         ( pileEcrans,  contexte )
, m_interface   ( std::make_shared<gui::Gui>( m_contexte.fenetre ) )
{ initGUI(); }


/////////////////////////////////////////////////
void EcranOptions::traiter_evenements    ( const sf::Event& event )
{ m_interface->traiterEvenements  ( event ); }


/////////////////////////////////////////////////
void EcranOptions::actualiser            ( sf::Time deltaT )
{ m_interface->actualiser    (  ); }


/////////////////////////////////////////////////
void EcranOptions::dessiner ()
{   m_contexte.fenetre->draw ( m_fond );
    m_contexte.fenetre->draw ( *m_interface );
}



/////////////////////////////////////////////////
void
EcranOptions::initGUI  ( )
{

    /// Initialisation du fond. //////
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_contexte.fenetre->getSize() ) );
    m_fond.setFillColor  ( sf::Color (70,70,30 , 150 ));


    /// l'interface graphique //////
    // la fenetre //
    auto   fenetrePrincipale   =   m_interface->creer.fenetre( "  OptIOnS" , { 230, 125 }, true );
    fenetrePrincipale->aligner      ( m_interface );

    // les boutons //
    sf::Vector2i tailleBtn = { 200 , 20 } ;
    auto    btnQuitter      =   m_interface->creer.bouton( "Retour" , tailleBtn );
    fenetrePrincipale->ajouterEnfant    ( btnQuitter );
    btnQuitter->aligner( fenetrePrincipale );
    btnQuitter->setPosition ( btnQuitter->getPosition ().x, 70. );

    /// interactions //////
    // les boutons //
    btnQuitter->lier    (  gui::Actions::Evenement::onBtnG_relacher
                        , [this](){
                            m_pileEcrans->at( m_pileEcrans->size() -2).setPause ( false );
                            retirerEcran();
                         });

    // le clavier //
    m_interface->lier   ( sf::Keyboard::Escape
                        , [this](){
                            std::cout << "OPTIONS:Escape\n";
                            m_pileEcrans->at( m_pileEcrans->size() -2).setPause ( false );
                            retirerEcran();

                         });

}   // fin init GUI




}   // fin namespace app































