/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <Style.h>



namespace gui {

/////////////////////////////////////////////////
Style::Style ()
: m_fondCouleur_1 ( sf::Color (  100, 100, 100, 255 ) )
, m_fondCouleur_2 ( sf::Color (  150, 150, 150, 255 ) )
, m_fondCouleur_3 ( sf::Color (  200, 200, 200, 255 ) )
, m_ligneCouleur ( sf::Color (  255, 255, 255, 255 ) )
, m_boutonCouleur_repos ( sf::Color (   50,  50,  50, 255 ) )
, m_boutonCouleur_survol ( sf::Color (   75,  75,  75, 255 ) )
, m_boutonCouleur_press ( sf::Color (  100, 100, 100, 255 ) )
, m_texteCouleur_1 ( sf::Color (  255, 255, 255, 255 ) )
, m_texteCouleur_2 ( sf::Color (  255, 255, 255, 255 ) )
, m_texteCouleur_3 ( sf::Color (  255, 255, 255, 255 ) )
{
    
}


} // fin namespace gui

