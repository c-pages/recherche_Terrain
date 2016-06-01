/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "jeu/Plante.h"
#include <iostream>


namespace jeu {

Plante::Plante()
{
    m_graine.setRadius ( 6 );
    m_graine.setOrigin ( 3,3 );
    m_graine.setFillColor ( sf::Color( 150, 80,50) );

}


void Plante::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    //On applique la transformation
    states.transform *= getTransform();

    target.draw ( m_graine , states );

}

} // fin namespace jeu

