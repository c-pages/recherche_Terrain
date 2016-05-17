#include "interfaces/composants/CmpGlissere.h"

namespace gui {
/////////////////////////////////////////////////
CmpGlissere::CmpGlissere()
: m_boutonFond  ( std::make_shared<BtnRectangle>() )
, m_slider      ( std::make_shared<BtnRectangle>() )
, m_fond        ( std::make_shared<AffRectangle>() )
, m_longueur    ( 180 )
, m_largeur     ( 15 )
, m_horizontal  ( true )
{

    // valeurs par defaut
    m_btnCouleurs.set       ( sf::Color( 0, 0, 0, 50 )     , Etat::desactive );
    m_btnCouleurs.set       ( sf::Color( 255,255,255, 0 ) , Etat::repos );
    m_btnCouleurs.set       ( sf::Color( 255,255,255, 20 ) , Etat::survol );
    m_btnCouleurs.set       ( sf::Color( 255,255,255, 25 ) , Etat::press );
    m_btnLgnCouleurs.set    ( sf::Color( 255,255,255, 20 ) );
    m_btnLgnepaisseurs.set  ( 0 );

    m_slideCouleurs.set       ( sf::Color( 0, 0, 0, 50 )     , Etat::desactive );
    m_slideCouleurs.set       ( sf::Color( 255,255,255, 40 ) , Etat::repos );
    m_slideCouleurs.set       ( sf::Color( 255,255,255, 60 ) , Etat::survol );
    m_slideCouleurs.set       ( sf::Color( 255,255,255, 80 ) , Etat::press );
    m_slideLgnCouleurs.set    ( sf::Color( 255,255,255, 20 ) );
    m_slideLgnepaisseurs.set  ( 0 );

    m_fndCouleur            = sf::Color::Transparent;
    m_fndLgnCouleur         = sf::Color( 255,255,255, 20 );
    m_fndLgnepaisseur       = 1;

}


/////////////////////////////////////////////////
void CmpGlissere::initialiserComposants ( Gadget*     base ){
    m_base = base ;
    m_base->ajouterComposant ( m_boutonFond );
    m_base->ajouterComposant ( m_slider );
    m_base->ajouterComposant ( m_fond );
};


/////////////////////////////////////////////////
void CmpGlissere::setSliderCouleur ( Valeurs<sf::Color> couleurs  ) {
    m_slideCouleurs = couleurs;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setSliderLigneCouleur ( Valeurs<sf::Color> couleurs  ) {
    m_slideLgnCouleurs = couleurs;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setSliderLigneEpaisseur ( Valeurs<float> epaisseur ) {
    m_slideLgnepaisseurs =  epaisseur;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setBoutonCouleur ( Valeurs<sf::Color> couleurs  ) {
    m_btnCouleurs = couleurs;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setBoutonLigneCouleur ( Valeurs<sf::Color> couleurs  ) {
    m_btnLgnCouleurs = couleurs;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setBoutonLigneEpaisseur ( Valeurs<float> epaisseur ) {
    m_btnLgnepaisseurs =  epaisseur;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setFondCouleur ( sf::Color couleurs  ) {
    m_fndCouleur = couleurs;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setFondLigneCouleur ( sf::Color couleurs  ) {
    m_fndLgnCouleur = couleurs;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setFondLigneEpaisseur ( float epaisseur ) {
    m_fndLgnepaisseur =  epaisseur;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpGlissere::setLongueurCurseur( float pourcentage ){

    if ( pourcentage > 100 )    pourcentage = 100;
    if ( pourcentage < 0 )      pourcentage = 0;

    if ( m_horizontal ){
        m_slider->setTailleX( m_longueur * pourcentage/100- 2*m_base->getMarge().x );
        m_slider->setTailleY( m_largeur - 2*m_base->getMarge().y );

    }else{
        m_slider->setTailleX( m_largeur - 2*m_base->getMarge().y);
        m_slider->setTailleY( m_longueur * pourcentage/100- 2*m_base->getMarge().x);
    }


}
/////////////////////////////////////////////////
void CmpGlissere::setLongueur( float longueur ){
    m_longueur = longueur;
//    m_base->demanderActuaGeom ();
    m_base->actualiserGeometrie();
}

/////////////////////////////////////////////////
void CmpGlissere::setLargeur( float largeur ){

    m_base->log ("setLargeur");
    m_largeur = largeur;
    m_base->log ("m_largeur", m_largeur);
//    m_base->demanderActuaGeom ();
    m_base->actualiserGeometrie();
}

/////////////////////////////////////////////////
void CmpGlissere::setHorizontal (  ){
    m_horizontal = true;
    m_base->demanderActuaGeom ();
}

/////////////////////////////////////////////////
void CmpGlissere::setVertical (  ){

    m_horizontal = false;
    m_base->demanderActuaGeom ();
}

} // fin namespace gui











