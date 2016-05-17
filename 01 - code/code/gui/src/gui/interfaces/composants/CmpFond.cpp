#include "interfaces/composants/CmpFond.h"



namespace gui {


/////////////////////////////////////////////////
CmpFond::CmpFond()
: m_fond   ( std::make_shared<AffRectangle>())
{

    // valeurs par defaut
    m_fondCouleur.set       ( sf::Color( 0, 0, 0, 50 )  , Etat::desactive );
    m_fondCouleur.set       ( sf::Color( 255,255,255, 50 )  , Etat::repos );
    m_fondCouleur.set       ( sf::Color( 255,255,255, 100 ) , Etat::survol );
    m_fondCouleur.set       ( sf::Color( 255,255,255, 150 ) , Etat::press );
    m_fondLgnCouleur.set    ( sf::Color( 255,255,255, 100 ) );
    m_fondLgnEpaisseur.set  ( 0 );

}

/////////////////////////////////////////////////
void CmpFond::initialiserComposants ( Gadget*     base ){
    m_base = base ;
    m_base->ajouterComposant ( m_fond );
    m_base->log("InitialiserComposants : m_fond");
};



/////////////////////////////////////////////////
void CmpFond::setFondCouleur ( sf::Color couleur ) {
    m_fondCouleur.set ( couleur );
    m_fond->setFondCouleur( couleur );
};

/////////////////////////////////////////////////
void CmpFond::setFondCouleur (sf::Color couleur , Etat etat ) {
    m_fondCouleur.set ( couleur , etat );
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpFond::setFondCouleur ( Valeurs<sf::Color> couleurs  ) {
    m_fondCouleur = couleurs;
    m_base->demanderActuaStyle();
};



/////////////////////////////////////////////////
void CmpFond::setFondLigneCouleur (sf::Color couleur  ) {
    m_fondLgnCouleur.set ( couleur );
    m_fond->setFondLigneCouleur( couleur );
};

/////////////////////////////////////////////////
void CmpFond::setFondLigneCouleur (sf::Color couleur , Etat etat ) {
    m_fondLgnCouleur.set ( couleur , etat );
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpFond::setFondLigneCouleur ( Valeurs<sf::Color> couleurs  ) {
    m_fondLgnCouleur = couleurs;
    m_base->demanderActuaStyle();
};




/////////////////////////////////////////////////
void CmpFond::setFondLigneEpaisseur (float epaisseur  ) {
    m_fondLgnEpaisseur.set ( epaisseur );
    m_fond->setFondLigneEpaisseur( epaisseur );
};


/////////////////////////////////////////////////
void CmpFond::setFondLigneEpaisseur (float epaisseur , Etat etat ) {
    m_fondLgnEpaisseur.set ( epaisseur , etat );
    m_base->demanderActuaStyle();
};


/////////////////////////////////////////////////
void CmpFond::setFondLigneEpaisseur ( Valeurs<float> epaisseur ) {
    m_fondLgnEpaisseur =  epaisseur;
    m_base->demanderActuaStyle();
};

/////////////////////////////////////////////////
void CmpFond::appliquerEtat( Etat etat ){

    m_fond->setFondCouleur    ( sf::Color (
                                      m_fondCouleur.get( etat ).r
                                    , m_fondCouleur.get( etat ).g
                                    , m_fondCouleur.get( etat ).b
                                    , m_fondCouleur.get( etat ).a * m_base->getOpacite() ) ) ;

    m_fond->setFondLigneCouleur     ( sf::Color (
                                      m_fondLgnCouleur.get( etat ).r
                                    , m_fondLgnCouleur.get( etat ).g
                                    , m_fondLgnCouleur.get( etat ).b
                                    , m_fondLgnCouleur.get( etat ).a * m_base->getOpacite() ) ) ;
    m_fond->setFondLigneEpaisseur ( m_fondLgnEpaisseur.get( etat ) ) ;
}



} // fin namespace gui
