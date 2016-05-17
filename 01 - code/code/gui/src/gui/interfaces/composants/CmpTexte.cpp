#include "interfaces/composants/CmpTexte.h"
#include "gui.h"
namespace gui {


CmpTexte::CmpTexte()
: m_label   ( std::make_shared<AffLabel>())
{

    // valeurs par defaut
    m_textCouleur.set( sf::Color::White );
    m_textCouleur.set( sf::Color( 100,100,100 ) , Etat::desactive );
    m_textTaille.set ( 12 ) ;
    m_textPolice.set ( Interface::ms_polices.get( "Defaut" ) ) ;
    m_textStyle.set  ( sf::Text::Style::Regular ) ;
}


/////////////////////////////////////////////////
void CmpTexte::initialiserComposants ( Gadget*     base ){
    m_base = base ;
    m_base->ajouterComposant ( m_label );
};

/////////////////////////////////////////////////
void CmpTexte::setTexte( std::string val ){
    m_base->log("setTexte ", val  );
    m_texte = val;
    m_label->setTexte ( val ) ;
    m_base->demanderActuaGeom();
};

/////////////////////////////////////////////////
std::string  CmpTexte::getTexte( ) const{
    return m_texte;
};


/////////////////////////////////////////////////
void CmpTexte::setTexteTaille( float val , Etat etat ){
    m_textTaille.set ( val , etat ) ;
    m_base->demanderActuaStyle();
};



/////////////////////////////////////////////////
void CmpTexte::setTexteTaille( Valeurs<float> val ){
    m_textTaille = val;
    m_base->demanderActuaStyle();
};


/////////////////////////////////////////////////
void CmpTexte::setTexteCouleur( sf::Color couleur , Etat etat){
    m_textCouleur.set ( couleur , etat ) ;
    m_base->demanderActuaStyle();
};



/////////////////////////////////////////////////
void CmpTexte::setTexteCouleur( Valeurs<sf::Color> couleur  ){
    m_textCouleur = couleur ;
    m_base->demanderActuaStyle();
}


/////////////////////////////////////////////////
void CmpTexte::setTextePolice( sf::Font val  , Etat etat ){
    m_textPolice.set ( val , etat ) ;
    m_base->demanderActuaStyle();
}


/////////////////////////////////////////////////
void CmpTexte::setTextePolice( Valeurs<sf::Font> val   ){
    m_textPolice.set ( val ) ;
    m_base->demanderActuaStyle();
}


/////////////////////////////////////////////////
void CmpTexte::setTexteStyle( sf::Text::Style val   , Etat etat )  {
    m_textStyle.set ( val  , etat ) ;
    m_label->setTexteStyle    ( val  ) ;
}


/////////////////////////////////////////////////
void CmpTexte::setTexteStyle( Valeurs<sf::Text::Style> val ){
    m_textStyle.set ( val );
    m_base->demanderActuaStyle();
}


/////////////////////////////////////////////////
void CmpTexte::appliquerEtat( Etat etat ){

    m_label->setTexteCouleur    ( sf::Color (
                                      m_textCouleur.get( etat ).r
                                    , m_textCouleur.get( etat ).g
                                    , m_textCouleur.get( etat ).b
                                    , m_textCouleur.get( etat ).a * m_base->getOpacite() ) ) ;
    m_label->setTexteTaille     ( m_textTaille.get( etat ) ) ;
    m_label->setTextePolice     ( m_textPolice.get( etat ) ) ;
    m_label->setTexteStyle      ( m_textStyle.get( etat ) ) ;

    m_base->demanderActuaStyle();
}



}



















