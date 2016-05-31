

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
, m_jeu         ( m_contexte )
{
    // Initialisation de l'interface graphique.
    initGUI();

    // Demarrer une nouvelle partie
    m_jeu.demarrerPartie( );

    /// Initialisation de la vue ///
    auto    tailleCarte     = m_jeu.getTailleCarte();
    m_vuePrincipale.setCenter( tailleCarte.x/2, tailleCarte.y/2);

}


/////////////////////////////////////////////////
void EcranJeu::traiter_evenements    ( const sf::Event& event )
{
    if ( m_pause ) return;


    // gestion du drag de la vuePrincipale à la souris
    switch ( event.type){
        case sf::Event::MouseMoved :
            if ( m_drag ){

                auto window         = m_contexte.fenetre;
                auto tailleCarte    = m_jeu.getTailleCarte();

                sf::Vector2f posVue =   { m_posVueOrigine.x + m_posSourisOrigine.x - sf::Mouse::getPosition(*window).x
                                        , m_posVueOrigine.y + m_posSourisOrigine.y - sf::Mouse::getPosition(*window).y };

                // limitation dans la fenetre
                if ( posVue.x < window->getSize().x/2 )
                    posVue.x = window->getSize().x/2;
                if ( posVue.y < window->getSize().y/2 )
                    posVue.y = window->getSize().y/2;
                if ( posVue.x > tailleCarte.x - window->getSize().x/2 )
                    posVue.x = tailleCarte.x - window->getSize().x/2;
                if ( posVue.y > tailleCarte.y - window->getSize().y/2 )
                    posVue.y = tailleCarte.y - window->getSize().y/2;


                // on applique le deplacement de la vue
                m_vuePrincipale.setCenter( posVue );

                // on indique au shader du terrain le changement d'origine
                m_jeu.setShadersOrigin( posVue );

                // on recentre le vignetting ( \todo: voir comment on peut faire ça en shader )
//                shpVignetting.setPosition( posVue );
//                rectVueMiniCarte.setPosition( posVue );

            }
            break;

        case sf::Event::MouseButtonPressed :
            if ( event.mouseButton.button == sf::Mouse::Middle ){
                m_posVueOrigine       = m_vuePrincipale.getCenter();
                m_posSourisOrigine    = sf::Mouse::getPosition(*m_contexte.fenetre);
                m_drag = true;

            }
            break;

        case sf::Event::MouseButtonReleased :
            if ( event.mouseButton.button == sf::Mouse::Middle )
                m_drag = false;

            break;
    }



    m_jeu.traiterEvenements  ( event );
    m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranJeu::actualiser   ( sf::Time deltaT )
{
    if ( m_pause ) return;

    m_jeu.actualiser ( deltaT );
    m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranJeu::dessiner ()
{
//    m_contexte.fenetre->draw ( m_fond );

    // passer dans la vue principale
    m_contexte.fenetre->setView  ( m_vuePrincipale );
    m_contexte.fenetre->draw ( m_jeu );

//m_contexte.fenetre->setView  ( );

    // \todo : passer dans la vue interface
    m_contexte.fenetre->draw ( *m_interface );
}



/////////////////////////////////////////////////
void
EcranJeu::initGUI  ( )
{

//    // Initialisation du fond.
//    m_fond.setPosition(0,0);
//    m_fond.setSize       ( sf::Vector2f ( m_contexte.fenetre->getSize() ) );
//    m_fond.setFillColor  ( sf::Color (50,50,50 , 150));


    /// l'interface graphique //////
    // Interactions clavier //
    m_interface->lier   ( sf::Keyboard::Escape
                        , [this ](){
                         setPause ( true );
                         ajouterEcran ( app::Ecrans::Pause );
                         });


    m_interface->lier   ( sf::Keyboard::PageUp
                        , [this ](){
                         std::cout <<"monter\n";
                         m_jeu.etageMonter();
                         });
    m_interface->lier   ( sf::Keyboard::PageDown
                        , [this ](){
                         std::cout <<"descendre\n";
                         m_jeu.etageDescendre();
                         });



}   // fin init GUI




}   // fin namespace app































