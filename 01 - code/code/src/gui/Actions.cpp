/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/Actions.h>
#include <gui/Gadget.h>

#include <iostream>

namespace gui {

/////////////////////////////////////////////////
Actions::Actions ()
{

}


/////////////////////////////////////////////////
void Actions::lier  (Evenement evenement, FctnAction fonction)
{
    m_evenementsSouris.insert( { evenement , fonction } );
}


/////////////////////////////////////////////////
void Actions::lier ( sf::Keyboard::Key  touche, FctnAction fonction)
{

    m_evenementsClavier.insert( { touche , fonction } );
}


/////////////////////////////////////////////////
void Actions::delier (Evenement evenement)
{

}


/////////////////////////////////////////////////
void Actions::delier ( sf::Keyboard::Key  touche)
{
    m_evenementsClavier.erase( touche  );

}


/////////////////////////////////////////////////
void Actions::vider ()
{
    m_evenementsClavier.clear( );
    m_evenementsSouris.clear( );
}


/////////////////////////////////////////////////
void Actions::declencher (Evenement evenement)
{
    if ( ! static_cast<Gadget*>(this)->estVisible() ) return;

    auto cherche = m_evenementsSouris.find( evenement );
    if ( cherche != m_evenementsSouris.end() ) {
        cherche->second();
    }
}



/////////////////////////////////////////////////
void Actions::traiterEvenementsClavier (sf::Event evenement)
{
    for (auto evt : m_evenementsClavier )
        if ( evenement.key.code == evt.first )
            evt.second();
}


} // fin namespace gui

