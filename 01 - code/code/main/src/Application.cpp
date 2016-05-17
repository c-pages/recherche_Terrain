

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Application.h"
#include "Config.h"
#include "ecrans/EcranAccueil.h"
#include "ecrans/EcranJeu.h"
//#include "ecrans/EcranOptions.h"

#include "gui.h"

#include <SFML/System.hpp>

namespace app
{
/////////////////////////////////////////////////
Application::Application()
: m_fenetre     ( new sf::RenderWindow() )
, m_interface   ( std::make_shared<gui::Interface>( m_fenetre ) )
{

    //   Initialisation de la Configuration ( ensembles des ressources ...)
    Config::init();

    //   Creation de la fenêtre SFML.
    sf::ContextSettings 	contextFenetre  ( 	0,  //  depth
                                                0,  //  stencilc
                                                4,  //  antialiasing
                                                2,  //  major
                                                0); //  minor
    m_fenetre->create(sf::VideoMode(1920, 1080)
                      , "SuperOrganisme"
                      , sf::Style::Fullscreen
                      , contextFenetre );

    sf::Image iconeFenetre;
    if( iconeFenetre.loadFromFile("media/img/Icone_test.png"))
        m_fenetre->setIcon( iconeFenetre.getSize().x
                           ,iconeFenetre.getSize().y
                           ,iconeFenetre.getPixelsPtr());

    // La synchronisation verticale pour des histoire de bugs de chargement de police bidule truc
//    m_fenetre->setVerticalSyncEnabled(true);
    int dureeTmp = 1 / Config::getDureeImage().asSeconds() ;
    m_fenetre->setFramerateLimit( dureeTmp );

    //   Ajout du premier écran.
    m_ecrans.ajouter( new EcranAccueil( this ) );




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

    while ( m_fenetre->isOpen() )
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
                m_fenetre->close();
        }

        // Dessiner les écrans actifs.
        dessiner();
    }
}


/////////////////////////////////////////////////
void Application::changerEcran( Ecrans ecran ){

    switch (ecran){
    case Accueil :
            m_ecrans.changer( new EcranAccueil( this )  );
        break;
    case Jeu :
            m_ecrans.changer( new EcranJeu( this )  );
        break;
//    case Options :
//            m_ecrans.changer( new EcranOptions( this )  );
//        break;
    }
}


/////////////////////////////////////////////////
void Application::ajouterEcran( Ecrans ecran ){

    switch (ecran){
    case Accueil :
            m_ecrans.ajouter( new EcranAccueil( this )  );
        break;
    case Jeu :
            m_ecrans.ajouter( new EcranJeu( this )  );
        break;
//    case Options :
//            m_ecrans.ajouter( new EcranOptions( this )  );
//        break;
    }
}


/////////////////////////////////////////////////
void Application::retirerEcran(  ){

            m_ecrans.retirer(  );
}

/////////////////////////////////////////////////
sf::RenderWindow*    Application::getFenetre() {
    return m_fenetre;
}



/////////////////////////////////////////////////
void Application::traiter_evenements(){
    sf::Event event;
    while (m_fenetre->pollEvent(event)){
        m_ecrans.traiter_evenements ( event );
        m_interface->traiterEvenements(event);
    }
}


/////////////////////////////////////////////////
void Application::actualiser ( sf::Time deltaT )
{
    m_interface->actualiser    (  );
    m_ecrans.actualiser ( deltaT );
}


/////////////////////////////////////////////////
void Application::dessiner ( )
{

    ///< Vider la fenetre.
    m_fenetre->clear(sf::Color::Black);


    ///< Rendu des ecrans courants.
    m_ecrans.dessiner();

    ///< rendu de l'interface
    m_fenetre->draw ( *m_interface );

    ///< Afficher la fenêtre.
    m_fenetre->display();

}


} // namespace app
