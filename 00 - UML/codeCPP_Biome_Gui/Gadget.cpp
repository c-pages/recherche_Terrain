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


/////////////////////////////////////////////////
std::shared_ptr<Gadget> Gadget::testerSurvol () const
{
    
}


} // fin namespace gui

