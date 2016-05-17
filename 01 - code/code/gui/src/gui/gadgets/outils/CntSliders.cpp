/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gadgets/outils/CntSliders.h"
#include "Enums.h"



namespace gui {

/////////////////////////////////////////////////
CntSliders::CntSliders ()
: Contenant ()
, m_slider_V ( std::make_shared<DnGlissere>() )
, m_slider_H ( std::make_shared<DnGlissere>() )
{

    ajouterComposant( m_slider_V );
    ajouterComposant( m_slider_H );

    // valeurs par defaut
    m_taille = { 900 , 900 };
    m_largeurSliders = 7;


    auto tailleMax = sf::Texture::getMaximumSize();
    if ( tailleMax < 1080 )
        m_renderTexture.create( 300  , tailleMax );
    else
        m_renderTexture.create( 300  , 1080 );

    m_btnBtnCouleurs.set       ( sf::Color( 0, 0, 0, 50 )     , Etat::desactive );
    m_btnBtnCouleurs.set       ( sf::Color( 255,255,255, 0 )  , Etat::repos );
    m_btnBtnCouleurs.set       ( sf::Color( 255,255,255, 20 ) , Etat::survol );
    m_btnBtnCouleurs.set       ( sf::Color( 255,255,255, 25 ) , Etat::press );
    m_btnBtnLgnCouleurs.set    ( sf::Color( 255,255,255, 20 ) );
    m_btnBtnLgnepaisseurs.set  ( 0 );

    m_btnSlideCouleurs.set       ( sf::Color( 0, 0, 0, 50 )     , Etat::desactive );
    m_btnSlideCouleurs.set       ( sf::Color( 255,255,255, 40 ) , Etat::repos );
    m_btnSlideCouleurs.set       ( sf::Color( 255,255,255, 60 ) , Etat::survol );
    m_btnSlideCouleurs.set       ( sf::Color( 255,255,255, 80 ) , Etat::press );
    m_btnSlideLgnCouleurs.set    ( sf::Color( 255,255,255, 20 ) );
    m_btnSlideLgnepaisseurs.set  ( 0 );

    m_btnFndCouleur            = sf::Color::Transparent;
    m_btnFndLgnCouleur         = sf::Color( 255,255,255, 20 );
    m_btnFndLgnepaisseur       = 0;

    m_slider_V->setVertical();
    m_slider_V->setLargeur ( m_largeurSliders );
    m_slider_H->setLargeur ( m_largeurSliders );
    m_slider_V->setMarge({ 0 , 0});
    m_slider_H->setMarge({ 0 , 0});

    m_slider_V->lier ( Evenement::on_valeurChange , [this](){ demanderActuaGeom (); });
    m_slider_H->lier ( Evenement::on_valeurChange , [this](){ demanderActuaGeom (); });


}

/////////////////////////////////////////////////
void CntSliders::actualiserGeometrie (){




    sf::Vector2f deplPossibleMax = deplMaxContenu();

    m_slider_H->setVisible ( deplPossibleMax.x > 1 );
    m_slider_V->setVisible ( deplPossibleMax.y > 1 );

    m_tailleContenant = { m_taille.x -  m_slider_V->getTaille().x , m_taille.y -  m_slider_H->getTaille().y };

//    m_tailleContenant = { m_taille.x  , m_taille.y  };

    // si le contenu est plus grand que le contenant
    if ( m_slider_H->estVisible() ) {
//            printf ("horiz visible\n");
        m_slider_H->setLongueur( m_tailleContenant.x );
        m_slider_H->setPosition( 0 , m_tailleContenant.y );
        float longueurCursH = m_taille.x/ float( m_groupe->getTaille().x )* 100;
        m_slider_H->setLongueurCurseur(longueurCursH);

        float coef          = ( m_slider_H->getValeur() ) / 100;
        m_posContenant.x    = coef * deplPossibleMax.x;

        m_largeurRedimH     = m_slider_H->getTaille().y;

    } else {
        m_posContenant.x    = 0;
        m_largeurRedimH     = 0;
    }

    // si contenu plus grand, on a le slider vert
    if (  m_slider_V->estVisible() ) {  // si contenu plus grand, on a le slider
//    m_slider_V->setVertical();
//            printf ("verti visible\n");
        m_slider_V->setLongueur ( m_tailleContenant.y );
        m_slider_V->setPosition ( m_tailleContenant.x , 0 );
        float longueurCursV = m_taille.y /float( m_groupe->getTaille().y )* 100 ;

        m_slider_V->setLongueurCurseur( longueurCursV );
//        m_slider_V->actualiserGeometrie();
        float coef                  = ( 100 - m_slider_V->getValeur()  ) / 100;
        m_posContenant.y              = coef * deplPossibleMax.y;
//        std::cout << "coef : " << coef << "     deplPossibleMax.y : " << deplPossibleMax.y << "\n";
    // si le contenu est plus petit, on cache le slider

        m_largeurRedimV = m_slider_V->getTaille().x;
    } else {
        m_posContenant.y      = 0;
        m_largeurRedimV = 0;
    }



    m_groupe->setPosition ( -m_posContenant.x , -m_posContenant.y );

    Contenant::actualiserGeometrie ();


}

/////////////////////////////////////////////////
void CntSliders::actualiserStyle (){


    m_slider_V->setSliderCouleur          ( m_btnSlideCouleurs  );
    m_slider_V->setSliderLigneCouleur       ( m_btnSlideLgnCouleurs   );
    m_slider_V->setSliderLigneEpaisseur   ( m_btnSlideLgnepaisseurs );
    m_slider_V->setBoutonCouleur          ( m_btnBtnCouleurs  );
    m_slider_V->setBoutonLigneCouleur       ( m_btnBtnLgnCouleurs );
    m_slider_V->setBoutonLigneEpaisseur   ( m_btnBtnLgnepaisseurs );
    m_slider_V->setFondCouleur                ( m_btnFndCouleur  );
    m_slider_V->setFondLigneCouleur             ( m_btnFndLgnCouleur  );
    m_slider_V->setFondLigneEpaisseur         ( m_btnFndLgnepaisseur );

    m_slider_H->setSliderCouleur          ( m_btnSlideCouleurs  );
    m_slider_H->setSliderLigneCouleur       ( m_btnSlideLgnCouleurs   );
    m_slider_H->setSliderLigneEpaisseur   ( m_btnSlideLgnepaisseurs );
    m_slider_H->setBoutonCouleur          ( m_btnBtnCouleurs  );
    m_slider_H->setBoutonLigneCouleur       ( m_btnBtnLgnCouleurs );
    m_slider_H->setBoutonLigneEpaisseur   ( m_btnBtnLgnepaisseurs );
    m_slider_H->setFondCouleur                ( m_btnFndCouleur  );
    m_slider_H->setFondLigneCouleur             ( m_btnFndLgnCouleur  );
    m_slider_H->setFondLigneEpaisseur         ( m_btnFndLgnepaisseur );

}




} // fin namespace gui

