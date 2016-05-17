/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gui.h"
#include "gadgets/outils/SupBandeau.h"
#include "gadgets/outils/CntSliders.h"



namespace gui {

/////////////////////////////////////////////////
SupBandeau::SupBandeau (){
    m_marge = { 3 , 3 };
    m_taille = { 150 , 31 };
}


/////////////////////////////////////////////////
void SupBandeau::actualiserGeometrie ()
{
    Support::actualiserGeometrie();
    int posX = m_marge.x;
    for (auto enfant : m_enfants )    {
        enfant->setPosition    ( posX ,  m_marge.y );
        posX += enfant->getTaille().x + m_marge.x;
    }

}




/////////////////////////////////////////////////
void SupBandeau::actualiserStyle ()
{
    Support::actualiserStyle();

}



/*
/////////////////////////////////////////////////
void SupBandeau::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

}
*/

} // fin namespace gui

