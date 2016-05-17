/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/AffRectangle.h>
#include <gui.h>



namespace gui {

/////////////////////////////////////////////////
AffRectangle::AffRectangle ( sf::Vector2i taille )
: Affiche()
, m_rectangle           ( )
, m_fondCouleur         ( sf::Color(0,0,255,255) )
, m_fondLgnCouleur      ( sf::Color(0,0,255,200) )
, m_fondLgnEpaisseur    ( 1 )
{
    creerNomUnique ( "Rectangle");
    m_taille = taille;

    m_masqueShader.setParameter( "aTexture"     ,  false  );
}


/////////////////////////////////////////////////
void AffRectangle::actualiserGeometrie ()
{
    // Debuggage
    log ("actualiserGeometrie  ");

    m_rectangle.setSize ( { m_taille.x, m_taille.y } );

}


/////////////////////////////////////////////////
void AffRectangle::actualiserStyle ()
{
    // Debuggage
    log ("actualiserStyle  ");

    m_rectangle.setFillColor        ( m_fondCouleur );
    m_rectangle.setOutlineColor     ( m_fondLgnCouleur );
    m_rectangle.setOutlineThickness ( m_fondLgnEpaisseur );

}


/////////////////////////////////////////////////
void AffRectangle::setFondCouleur (sf::Color couleur) {
    m_fondCouleur = couleur ;
    m_rectangle.setFillColor( couleur );
};


/////////////////////////////////////////////////
void AffRectangle::setFondLigneCouleur (sf::Color couleur) {
    m_fondLgnCouleur =  couleur;
    m_rectangle.setOutlineColor( couleur );
};


/////////////////////////////////////////////////
void AffRectangle::setFondLigneEpaisseur (float epaisseur) {
    m_fondLgnEpaisseur = epaisseur;
    m_rectangle.setOutlineThickness( epaisseur );
};


//
///////////////////////////////////////////////////
//void     AffRectangle::setMasqueRect ( float posX, float posY, float tailleX, float tailleY ){
//    printf ("SETMASQUE\n");
//    m_masqueShader.setParameter( "aTexture"     ,  false  );
//    m_masqueShader.setParameter( "rectMasque"   ,  posX, posY, tailleX, tailleY  );
//
//}

/////////////////////////////////////////////////
void AffRectangle::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    //On applique la transformation
    states.transform *= getTransform();

//    if ( m_masqueShader != nullptr )
//        states->shader = m_masqueShader;
    if ( estMasque() )
        states.shader = &m_masqueShader;

    // On dessine le rectangle
    if (estVisible())
        target.draw(m_rectangle, states);
}



} // fin namespace gui




















