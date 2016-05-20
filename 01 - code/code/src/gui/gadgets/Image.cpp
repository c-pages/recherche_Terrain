/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Image.h>
#include <iostream>


namespace gui {

/////////////////////////////////////////////////
Image::Image ( sf::Texture& texture )
: m_shape (  )
{
    setTexture ( texture );
}


/////////////////////////////////////////////////
void Image::setTexture ( sf::Texture& texture )
{
    // on applique la texture
    m_shape.setTexture  ( &texture );

    // on reajuste la taille du textureRect à la nouvelle texture
    m_shape.setTextureRect( {0,0,texture.getSize().x, texture.getSize().y} );

    // on reajuste la taille du gadget
    setSize         ( { texture.getSize().x, texture.getSize().y } );
}



/////////////////////////////////////////////////
void Image::actualiser ()
{
    // ajuste la taille du shape à la taille du gadget 'm_taille'
    m_shape.setSize     ( { getSize().x, getSize().y } );

    // on actualise les bases du gadget (Bounds)
    Gadget::actualiser();
}


/////////////////////////////////////////////////
void Image::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    // si non visible on sort
    if (! estVisible () ) return;

    //On applique la transformation
    states.transform *= getTransform();

    // On dessine le texte
    target.draw ( m_shape , states );
}


} // fin namespace gui

