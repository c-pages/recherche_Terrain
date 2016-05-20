/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/Calque.h>



namespace gui {

/////////////////////////////////////////////////
Calque::Calque ()
{

}

/////////////////////////////////////////////////
Gadget* Calque::testerSurvol (sf::Vector2i posSouris)
//std::shared_ptr<Gadget> Calque::testerSurvol (sf::Vector2i posSouris)
{
    // on regarde dans les enfants
    for ( auto enfant : m_enfants )
        if ( enfant->testerSurvol ( posSouris ) != nullptr )
            return enfant->testerSurvol ( posSouris );

    // sinon renvois rien
    return nullptr;

}



} // fin namespace gui

