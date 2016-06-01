

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "appli/Application.h"
#include "appli/Config.h"

#include "appli/ecrans/EcranAccueil.h"
#include "appli/ecrans/EcranPause.h"
#include "appli/ecrans/EcranJeu.h"
#include "appli/ecrans/EcranOptions.h"

#include "gui/Gui.h"

#include <SFML/System.hpp>

namespace app {


/////////////////////////////////////////////////
Application::Application()
: m_fenetre ( )
, m_ecrans  ( Ecran::Contexte ( m_fenetre ) )
{

    /// Initialisation de la Configuration ( ensembles des ressources ...)
    Config::init();



    /// creation de la fenetre
//    m_fenetre.create (
//            sf::VideoMode(1920, 1080)
//            , "SuperOrganisme"
//            , sf::Style::Fullscreen
//            , sf::ContextSettings ( 	0, 0,   4,  2,  0) );

    m_fenetre.create (
            sf::VideoMode(1280, 720)
            , "SuperOrganisme"
            , sf::Style::Titlebar
            , sf::ContextSettings ( 	0, 0,   4,  2,  0) );
    m_fenetre.setFramerateLimit(  1 / Config::getDureeImage().asSeconds() );



    /// L'icone de la fenêtre
    sf::Image iconeFenetre;
    if( iconeFenetre.loadFromFile("media/img/Icone_test.png"))
        m_fenetre.setIcon   ( iconeFenetre.getSize().x
                            , iconeFenetre.getSize().y
                            , iconeFenetre.getPixelsPtr() );

    /// Initialiser les écrans
    m_ecrans.enregistrerEcran<EcranAccueil>     ( Ecrans::Accueil );
    m_ecrans.enregistrerEcran<EcranOptions>     ( Ecrans::Options );
    m_ecrans.enregistrerEcran<EcranJeu>         ( Ecrans::Jeu );
    m_ecrans.enregistrerEcran<EcranPause>       ( Ecrans::Pause );

    /// Le premier écran
//    m_ecrans.ajouter ( Ecrans::Accueil );
    m_ecrans.ajouter ( Ecrans::Jeu );

}


/////////////////////////////////////////////////
Application::~Application()
{
    // vider la pile des ecrans.
    m_ecrans.vider();
}


/////////////////////////////////////////////////
void    Application::executer()
{

    sf::Clock   horloge;
    sf::Time    tempsDepuisMAJ = sf::Time::Zero;

    while ( m_fenetre.isOpen() )
    {
        traiter_evenements();
        tempsDepuisMAJ += horloge.restart();
        while (tempsDepuisMAJ > Config::getDureeImage())
        {
            tempsDepuisMAJ -= Config::getDureeImage();

            // Traitement des évenements.
            traiter_evenements();

            // Actualisation des éléments des écrans.
            actualiser( Config::getDureeImage() );

            // si la pile d'écrans est vide, on ferme.
            if ( m_ecrans.estVide() )
                m_fenetre.close();
        }

        // Dessiner les écrans actifs.
        dessiner();
    }
}



/////////////////////////////////////////////////
void Application::traiter_evenements(){
    sf::Event event;
    while (m_fenetre.pollEvent(event)){
        m_ecrans.traiter_evenements ( event );
    }
}


/////////////////////////////////////////////////
void Application::actualiser ( sf::Time deltaT )
{
//    m_interface->actualiser    (  );
    m_ecrans.actualiser ( deltaT );
}


/////////////////////////////////////////////////
void Application::dessiner ( )
{

    ///< Vider la fenetre.
    m_fenetre.clear(sf::Color::Black);


    ///< Rendu des ecrans courants.
    m_ecrans.dessiner();

//    ///< rendu de l'interface
//    m_fenetre->draw ( *m_interface );

    ///< Afficher la fenêtre.
    m_fenetre.display();

}


} // namespace app
