/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Fenetre.h>



namespace gui {

/////////////////////////////////////////////////
Fenetre::Glissiere::Glissiere ( Glissiere::Orientation orientation )
{

}






/////////////////////////////////////////////////
Fenetre::Fenetre (std::string titre, sf::Vector2i taille, bool draggable, bool resizable)
: m_draggable       ( draggable )
, m_dragEnCours     ( false )
, m_dragPosOrigin   ( {0,0} )
, m_resizable       ( resizable )
, m_shaderClip      (  )
, m_fond            (  )
, m_boutonFermer    (  )
, m_sliderH         (  Glissiere::Orientation::Horizontal  )
, m_sliderV         (  Glissiere::Orientation::Horizontal  )
{

}


/////////////////////////////////////////////////
void Fenetre::setTitre (std::string titre)
{

}


/////////////////////////////////////////////////
void Fenetre::setTitreCouleur (sf::Color couleur)
{

}


/////////////////////////////////////////////////
void Fenetre::setTitreTaille (float taille)
{

}


/////////////////////////////////////////////////
void Fenetre::setTitreStyle (sf::Text::Style style)
{

}


/////////////////////////////////////////////////
void Fenetre::setTitrePolice (sf::Font& police)
{

}


/////////////////////////////////////////////////
void Fenetre::setFondTexture (sf::Texture& texture)
{

}


/////////////////////////////////////////////////
void Fenetre::setFondCouleur (sf::Color couleur)
{

}


/////////////////////////////////////////////////
void Fenetre::setContourCouleur (sf::Color couleur)
{

}


/////////////////////////////////////////////////
void Fenetre::setContourEpaisseur (float epaisseur)
{

}


/////////////////////////////////////////////////
void Fenetre::actualiser ()
{

}


/////////////////////////////////////////////////
void Fenetre::traiterEvenements (sf::Event evenement)
{

}


/////////////////////////////////////////////////
void Fenetre::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

}


/////////////////////////////////////////////////
void Fenetre::actualiserClipping ()
{

}


} // fin namespace gui

