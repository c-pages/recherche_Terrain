/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Label.h>
#include "appli/Config.h"
#include <iostream>

namespace gui {

/////////////////////////////////////////////////
Label::Label ( std::string texte)
: m_texte (  )
{

    /// Initialisation du texte SFML
    m_texte.setString           ( texte );
    m_texte.setCharacterSize    ( 10 );
    m_texte.setColor            ( sf::Color (200,200,200) );
    m_texte.setFont             ( app::Config::ms_polices.get( app::Config::Polices::police_1 ) );

    actualiser ();
}

/////////////////////////////////////////////////
Label::~Label ( ) { }


/////////////////////////////////////////////////
void Label::setTexte (std::string texte)
{
    m_texte.setString( texte );
    actualiser ();
}


/////////////////////////////////////////////////
void Label::setTaille (float taille)
{
    m_texte.setCharacterSize( taille );
    actualiser ();
}


/////////////////////////////////////////////////
void Label::setCouleur ( sf::Color couleur )
{
    m_texte.setColor( couleur );
}


/////////////////////////////////////////////////
void Label::setStyle ( sf::Text::Style style )
{
    m_texte.setStyle( style );
    actualiser ();
}


/////////////////////////////////////////////////
void Label::setPolice (sf::Font& police)
{
    m_texte.setFont( police );
    actualiser ();
}




/////////////////////////////////////////////////
void Label::actualiser () {
    // on actualise la taille du gadget (m_taille) avec la taille du texte.
//    setSize( { m_texte.getGlobalBounds().width, m_texte.getGlobalBounds().height } );

    m_size = { m_texte.getGlobalBounds().width, m_texte.getGlobalBounds().height };
    Gadget::actualiser();
}



/////////////////////////////////////////////////
void Label::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    //On applique la transformation
    states.transform *= getTransform();

    // On dessine le texte
    target.draw ( m_texte , states );
}


} // fin namespace gui

