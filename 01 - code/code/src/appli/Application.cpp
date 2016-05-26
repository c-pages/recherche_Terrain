

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
: m_fenetre ( sf::VideoMode(1280, 720)
            , "SuperOrganisme"
            , sf::Style::Titlebar
            , sf::ContextSettings ( 	0, 0,   4,  2,  0) )
, m_ecrans  ( Ecran::Contexte ( m_fenetre ) )
{

    /// Initialisation de la Configuration ( ensembles des ressources ...)
    Config::init();

    /// le frameRate de la fenetre
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
    m_ecrans.ajouter ( Ecrans::Accueil );

}


/////////////////////////////////////////////////
Application::~Application()
{
    // vider la pile.
    m_ecrans.vider();
}


/////////////////////////////////////////////////
void    Application::executer()
{

    sf::Clock   horloge;
    sf::Time    tempsDepuisMAJ = sf::Time::Zero;

//sf::sleep( sf::seconds(0.005f)) ;

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

/*
/////////////////////////////////////////////////
void Application::changerEcran( Ecrans ecran ){

    switch (ecran){
    case Accueil :
            m_ecrans.changer( new EcranAccueil( this )  );
        break;
    case Jeu :
            m_ecrans.changer( new EcranJeu( this )  );
        break;
    case Pause :
            m_ecrans.changer( new EcranPause( this )  );
        break;
    case Options :
            m_ecrans.changer( new EcranOptions( this )  );
        break;
    }
}
*/
/*
/////////////////////////////////////////////////
void Application::ajouterEcran( Ecrans::ID ecranID )
{

}


/////////////////////////////////////////////////
void Application::retirerEcran( )
{

}


/////////////////////////////////////////////////
void Application::viderEcrans( )
{

}
*/


/*
/////////////////////////////////////////////////
void Application::ajouterEcran( Ecrans ecran ){

    std::cout << " Application :: ajouterEcran avt\n";
    switch (ecran){
    case Accueil :
        std::cout << "      EcranAccueil\n";
            m_ecrans.ajouter( new EcranAccueil( this )  );
        break;
    case Jeu :
        std::cout << "      EcranJeu\n";
            m_ecrans.ajouter( new EcranJeu( this )  );
        break;
    case Pause :
        std::cout << "      EcranPause\n";
            m_ecrans.ajouter( new EcranPause( this )  );
        break;
    case Options :
        std::cout << "      EcranOptions\n";
            m_ecrans.ajouter( new EcranOptions( this )  );
        break;
    }
    std::cout << " Application :: ajouterEcran fin\n";
}


/////////////////////////////////////////////////
void Application::retirerEcran(  ){

    m_ecrans.retirer(  );
}

/////////////////////////////////////////////////
void    Application::retirer ( unsigned int index )
{
    m_ecrans.retirer( index );
}


*/








//
//
///////////////////////////////////////////////////
//sf::RenderWindow*    Application::getFenetre() {
//    return m_fenetre;
//}



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
