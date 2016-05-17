/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/AffIcone.h>
#include <cmath>



namespace gui {

/////////////////////////////////////////////////
AffIcone::AffIcone ()
: AffImage      ()
, m_index       ( 1 )
, m_nbrIcones   (0)
{
    creerNomUnique( "Icone");


//    m_mute = false;

}


/////////////////////////////////////////////////
void AffIcone::actualiserGeometrie ()
{
    // Debuggage
    log ("actualiserGeometrie");

    //calcul de la largeur d'un coté
    int largeur = m_texture->getSize().y;

    // c'est toujours un carrée
    m_taille = { largeur , largeur };
    m_rectangle.setSize ( { largeur , largeur } );

    demanderActuaBounds();
}

/////////////////////////////////////////////////
void AffIcone::actualiserStyle ()
{
    // Debuggage
    log ("actualiserStyle  <-----", sf::Vector2i( m_texture->getSize() ) );

    //calcul de la largeur d'un coté
    int largeur = m_texture->getSize().y;

    // debug {
//    auto image = sf::Image ( m_texture->copyToImage() );
//    image.saveToFile( "POPOPOPO.jpg");

//    m_fondCouleur = sf::Color(255,220,50, 200);
    // }debug



    // les style du rectangle
    m_rectangle.setFillColor        ( m_fondCouleur );
    m_rectangle.setOutlineColor     ( m_fondLgnCouleur );
    m_rectangle.setOutlineThickness ( m_fondLgnEpaisseur );
    m_rectangle.setTextureRect      ( { ( m_index-1) * largeur, 0, largeur, largeur } );
    m_rectangle.setTexture          ( m_texture );

}


/////////////////////////////////////////////////
void AffIcone::setIndex( unsigned int val ){
    m_index = val;
    demanderActuaStyle ();
}


/////////////////////////////////////////////////
unsigned int AffIcone::getIndex () const {
    return m_index;
}


} // fin namespace gui

