/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <interfaces/Geometrie.h>
#include <interfaces/Gadget.h>
#include <Patch.h>



namespace gui {

/////////////////////////////////////////////////
void Geometrie::setTaille( float x, float y ){
    setTaille( sf::Vector2i ( x, y ) );
};

/////////////////////////////////////////////////
void Geometrie::setTaille( sf::Vector2i val ){
    if ( m_taille == val ) return;

    log ("setTaille" , val);


    if ( m_taille == val ) return;
    m_taille = val;
    static_cast<Gadget*>(this)->demanderActuaGeom();
};



/////////////////////////////////////////////////
void Geometrie::setTailleX( float val ){
    if ( m_taille.x == val ) return;

    m_taille.x = val;
    static_cast<Gadget*>(this)->log("setTailleX");
    static_cast<Gadget*>(this)->actualiserGeometrie();
//    static_cast<Gadget*>(this)->demanderActuaGeom();
};



/////////////////////////////////////////////////
void Geometrie::setTailleY( float val ){
    if ( m_taille.y == val ) return;

    m_taille.y = val;
    static_cast<Gadget*>(this)->log("setTailleY");
    static_cast<Gadget*>(this)->actualiserGeometrie();
//    static_cast<Gadget*>(this)->demanderActuaGeom();
};


/////////////////////////////////////////////////
void Geometrie::setPosAbs (sf::Vector2f posAbsDest ){

    sf::Vector2f posAbsParent = {0,0};
    if (m_parent != nullptr)
        posAbsParent = m_parent->getPosAbs();
    setPosition( posAbsDest.x -  posAbsParent.x , posAbsDest.y -  posAbsParent.y  ) ;

//    for (auto )
}

/////////////////////////////////////////////////
sf::Vector2f Geometrie::getPosAbs () const {
    if ( m_parent != nullptr)
        return getPosition() + m_parent->getPosAbs();
    else
        return getPosition();
}


/////////////////////////////////////////////////
void Geometrie::setPosition( float x , float y ){
    static_cast<Gadget*>(this)->log("setPosition");
//    m_position = {int ( x )  , int ( y )};
     sf::Transformable::setPosition( int ( x )  , int ( y ) );
     static_cast<Gadget*>(this)->demanderActuaBounds();
//     static_cast<Gadget*>(this)->demanderActuaBoundsComposants();

//     static_cast<Gadget*>(this)->actualiserBounds();
};

/////////////////////////////////////////////////
void Geometrie::setPosition( sf::Vector2f pos  ){
    static_cast<Gadget*>(this)->log("setPosition");
//    m_position = {int ( pos.x )  , int ( pos.y )};
     sf::Transformable::setPosition( int ( pos.x )  , int ( pos.y ) );
     static_cast<Gadget*>(this)->demanderActuaBounds();
//     static_cast<Gadget*>(this)->actualiserBounds();
};

/////////////////////////////////////////////////
void Geometrie::alignerSur ( std::shared_ptr<Gadget> cible, Alignement alignementThis, Alignement alignementCible)
{
    if ( cible == nullptr ) return;

    // Actualiser les geometries pour etre sûr
    actualiserGeometrie();
    cible->actualiserGeometrie();

    log ("aligner sur", cible);

    sf::Vector2i pt_origine;
    sf::Vector2i pt_cible;
    sf::Vector2f pt_destination;

    // l'origine //////

    // la ligne vert. de gauche du gadget a bouger
    if ( alignementThis == Alignement::GaucheHaut
    ||   alignementThis == Alignement::Gauche
    ||   alignementThis == Alignement::GaucheBas )
        pt_origine.x = getPosAbs().x ;

    // la ligne vert. du milieu du gadget a bouger
    else if ( alignementThis == Alignement::Haut
         ||   alignementThis == Alignement::Centre
         ||   alignementThis == Alignement::Bas )
        pt_origine.x = getPosAbs().x + getTaille().x/2;

    // la ligne vert. de droite du gadget a bouger
    else
        pt_origine.x = getPosAbs().x  + getTaille().x;


    // la ligne horiz. du haut du gadget a bouger
    if ( alignementThis == Alignement::GaucheHaut
    ||   alignementThis == Alignement::Haut
    ||   alignementThis == Alignement::DroiteHaut )
        pt_origine.y = getPosAbs().y;

    // la ligne horiz. du milieu du gadget a bouger
    else if ( alignementThis == Alignement::Gauche
         ||   alignementThis == Alignement::Centre
         ||   alignementThis == Alignement::Droite )
        pt_origine.y = getPosAbs().y + getTaille().y/2;

    // la ligne horiz. du bas du gadget a bouger
    else
        pt_origine.y = getPosAbs().y + getTaille().y;





    // la destination //////

    // la ligne vert. de gauche du gadget a bouger
    if ( alignementCible == Alignement::GaucheHaut
    ||   alignementCible == Alignement::Gauche
    ||   alignementCible == Alignement::GaucheBas )
        pt_cible.x = cible->getPosAbs().x ;

    // la ligne vert. du milieu du gadget a bouger
    else if ( alignementCible == Alignement::Haut
         ||   alignementCible == Alignement::Centre
         ||   alignementCible == Alignement::Bas )
        pt_cible.x = cible->getPosAbs().x + cible->getTaille().x/2;

    // la ligne vert. de droite du gadget a bouger
    else
        pt_cible.x = cible->getPosAbs().x  + cible->getTaille().x;


    // la ligne horiz. du haut du gadget a bouger
    if ( alignementCible == Alignement::GaucheHaut
    ||   alignementCible == Alignement::Haut
    ||   alignementCible == Alignement::DroiteHaut )
        pt_cible.y = cible->getPosAbs().y;

    // la ligne horiz. du milieu du gadget a bouger
    else if ( alignementCible == Alignement::Gauche
         ||   alignementCible == Alignement::Centre
         ||   alignementCible == Alignement::Droite )
        pt_cible.y = cible->getPosAbs().y + cible->getTaille().y/2;

    // la ligne horiz. du bas du gadget a bouger
    else
        pt_cible.y = cible->getPosAbs().y + cible->getTaille().y;


    // et on deplace le gadget sur le point de destination
    pt_destination = { pt_cible.x - pt_origine.x ,  pt_cible.y - pt_origine.y };
    move ( pt_destination );


    // actualisation de la geometrie
    static_cast<Gadget*>(this)->demanderActuaGeom();
    static_cast<Gadget*>(this)->demanderActuaContenu();

}


/////////////////////////////////////////////////
void Geometrie::actualiserBounds ()
{
    static_cast<Gadget*>(this)->log ( "ActualiserBounds  ");
    static_cast<Gadget*>(this)->log ( "taille" , getTaille() );


    sf::Vector2f pos = getPosAbs ();

    m_globalBounds.left     = pos.x;
    m_globalBounds.top      = pos.y;
    m_globalBounds.width    = getTaille().x;
    m_globalBounds.height   = getTaille().y;

    m_localBounds.left      = getPosition().x;
    m_localBounds.top       = getPosition().y;
    m_localBounds.width     = getTaille().x;
    m_localBounds.height    = getTaille().y;

    // les bounds des enfants
    for (auto gadg : getEnfants() )
        gadg->actualiserBounds();

    // les bounds des composants
    for (auto comp : static_cast<Gadget*>(this)->getComposants() )
        comp->actualiserBounds();
}



} // fin namespace gui

