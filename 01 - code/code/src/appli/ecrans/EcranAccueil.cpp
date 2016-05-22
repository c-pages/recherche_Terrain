

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
EcranAccueil::EcranAccueil( Application*  appli )
: Ecran         ( appli )
, m_interface   ( std::make_shared<gui::Gui>( appli->getFenetre() ) )
{
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
    m_interface->traiterEvenements  ( event );
}


/////////////////////////////////////////////////
void EcranAccueil::actualiser            ( sf::Time deltaT )
{
    m_interface->actualiser    (  );
}


/////////////////////////////////////////////////
void EcranAccueil::dessiner ()
{
    m_appli->getFenetre()->draw ( m_fond );
    m_appli->getFenetre()->draw ( *m_interface );

}



/////////////////////////////////////////////////
void
EcranAccueil::initGUI  ( )
{
    // Initialisation du fond.
    m_fond.setPosition(0,0);
    m_fond.setSize       ( sf::Vector2f ( m_appli->getFenetre()->getSize() ) );
    m_fond.setFillColor  ( sf::Color (50,100,50));

    // interactions de l'interface
    m_interface->lier (  sf::Keyboard::Escape
                       , [this](){  m_appli->getFenetre()->close();  }
                       );

    // creation de la fenetre
    std::shared_ptr<gui::Label>     lbl_1  =   m_interface->creer.label( );
    lbl_1->setTaille     ( 20 );
    lbl_1->setCouleur    ( sf::Color(255,255,0) );
    lbl_1->setPosition   ( 200,220 );

    std::shared_ptr<gui::Label>     lblTitre  =   m_interface->creer.label( );
    lblTitre->setPosition   ( 200,200 );
    lblTitre->setCouleur    ( sf::Color(255,255,0) );
    lblTitre->setTaille     ( 20 );
    lblTitre->setStyle      ( sf::Text::Style::Italic );

    std::shared_ptr<gui::Label>     lbl_2  =   m_interface->creer.label( );
    lbl_2->setTaille     ( 20 );
    lbl_2->setCouleur    ( sf::Color(255,255,0) );
    lbl_2->setStyle      ( sf::Text::Style::Bold );
    lbl_2->setPosition   ( 200,250 );


    std::shared_ptr<gui::Image>     img_1  =   m_interface->creer.image( Config::ms_textures.get( Config::Images::image_1 ) );
    //img_1->setSize ( {20,200});
//    img_1->setImage( Config::ms_textures.get( Config::Images::image_1 ) );
//    img_1->setImage( Config::ms_textures.get( Config::Images::image_1 ) );
    img_1->setPosition   ( 200,300 );

    std::shared_ptr<gui::Image>     img_2  =   m_interface->creer.image( Config::ms_textures.get( Config::Images::image_2 ) );
    //img_1->setSize ( {20,200});
    img_2->setTexture( Config::ms_textures.get( Config::Images::image_1 ) );
//    img_1->setImage( Config::ms_textures.get( Config::Images::image_1 ) );
    img_2->setPosition   ( 220,320 );


    std::shared_ptr<gui::Bouton>    boutonTexte_1   =   m_interface->creer.bouton( "Bouton texte sans taille" );
    boutonTexte_1->setPosition   ( 400,200 );

    std::shared_ptr<gui::Bouton>    boutonTexte_2   =   m_interface->creer.bouton( "Bouton texte AVEC taille" , {300,20});

//    boutonTexte_2->setIcone( Config::ms_textures.get( Config::Images::image_2 ) );

    boutonTexte_2->setPosition   ( 410,210 );
//    boutonTexte_2->setSize ({ 30,30});

    // interactions de l'interface
    m_interface->lier (  sf::Keyboard::Space
                       , [this, boutonTexte_1 ](){  boutonTexte_1->setEtat( gui::Gadget::Etat::Presse );  }
                       );

    // interactions de l'interface
    boutonTexte_1->lier (  gui::Actions::Evenement::onBtnG_relacher
                        , [this , boutonTexte_1 ](){
                            std::cout << "ACTION BOUTON\n";
                        });

//    boutonTexte_1->setRemplissageCouleur    ( sf::Color(0,0,200));
//    boutonTexte_1->setContourCouleur        ( sf::Color(250,250,0));
//    boutonTexte_1->setContourEpaisseur      ( 3 );
//    boutonTexte_1->setAlphaEtats            ( 255,255,0);

    std::shared_ptr<gui::Bouton>    boutonTexte_3   =   m_interface->creer.bouton( Config::ms_textures.get( Config::Images::image_2 ) );
    boutonTexte_3->setPosition   ( 400,300 );
    boutonTexte_3->setAlphaEtats            ( 0,100,250);
    boutonTexte_3->setContourEpaisseur      ( 0);
//    boutonTexte_3->setMarge({20,20});

    std::shared_ptr<gui::Bouton>    boutonTexte_4   =   m_interface->creer.bouton( Config::ms_textures.get( Config::Images::image_2 ) , { 40, 20 });
    boutonTexte_4->setPosition   ( 400,350 );








    std::shared_ptr<gui::Fenetre>    fenetreTest   =   m_interface->creer.fenetre( "Fenetre test" , { 200, 120 } );


    auto boutonPourFenetre  = m_interface->creer.bouton ("Bouton dans la fenetre");
    boutonPourFenetre->setPosition ( 10, 5 );
    auto boutonPourFenetre2 = m_interface->creer.bouton ("Bouton dans la fenetre super long pour voir quand ca depasse");
    boutonPourFenetre2->setPosition ( 10, 30 );


    fenetreTest->ajouterEnfant( boutonPourFenetre );
    fenetreTest->ajouterEnfant( boutonPourFenetre2 );
    fenetreTest->setPosition   ( 250,250 );






    boutonPourFenetre->lier (  gui::Actions::Evenement::onBtnG_relacher
                        , [this , boutonTexte_1 ](){
                            std::cout << "ACTION BOUTON 2\n";
                        });

    boutonPourFenetre2->lier (  gui::Actions::Evenement::onBtnG_relacher
                        , [this , boutonTexte_1 ](){
                            std::cout << "ACTION BOUTON 3\n";
                        });

}   // fin init GUI




}   // fin namespace app































