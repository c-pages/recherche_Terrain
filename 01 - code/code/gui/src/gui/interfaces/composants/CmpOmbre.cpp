#include "interfaces/composants/CmpOmbre.h"



namespace gui {


/////////////////////////////////////////////////
CmpOmbre::CmpOmbre()
: m_ombre       ( std::make_shared<AffRectangle>())
, m_ombreActive ( true )
{

    // valeurs par defaut
    m_ombreCouleur = sf::Color( 0, 0, 0, 120 )  ;

    m_ombre->setFondCouleur         ( m_ombreCouleur ) ;
    m_ombre->setFondLigneCouleur    ( sf::Color::Transparent ) ;
    m_ombre->setFondLigneEpaisseur  ( 0 ) ;

    m_ombre->setPosition (5,5);
}

/////////////////////////////////////////////////
void CmpOmbre::initialiserComposants ( Gadget*     base ){
    m_base = base ;
    m_base->ajouterComposant ( m_ombre );
};


/////////////////////////////////////////////////
void CmpOmbre::setOmbreActive ( bool val ) {
    m_ombreActive = val;
    m_ombre->setVisible (m_ombreActive);
};

/////////////////////////////////////////////////
void CmpOmbre::setOmbreCouleur ( sf::Color couleur ) {
    m_ombreCouleur = couleur ;
    m_ombre->setFondCouleur( couleur );
};


} // fin namespace gui
