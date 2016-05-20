/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <Gadget.h>

#include <Gadget.h>
#include <Gadget.h>


namespace gui {

/////////////////////////////////////////////////
Gadget::Gadget ()
: m_parent ( nullptr )
, m_enfants (  )
, m_size ( {0,0} )
, m_globalBounds ( {0,0,0,0} )
, m_localBounds ( {0,0,0,0} )
{
    
}


/////////////////////////////////////////////////
std::shared_ptr<Gadget> Gadget::thisPtr ()
{
    
}


/////////////////////////////////////////////////
std::shared_ptr<Gadget> Gadget::testerSurvol (sf::Vector2i posSouris) const
{
    
}


/////////////////////////////////////////////////
void Gadget::traiterEvenements (sf::Event evenement)
{
    
}


/////////////////////////////////////////////////
void Gadget::actualiser ()
{
    
}


/////////////////////////////////////////////////
void Gadget::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    
}


} // fin namespace gui

