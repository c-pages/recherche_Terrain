/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Calque.h>



namespace gui {

/////////////////////////////////////////////////
Calque::Calque ()
{

}

/////////////////////////////////////////////////
Gadget* Calque::testerSurvol (sf::Vector2i posSouris)
{
    // si non visible on renvois nullptr
    if (! estVisible () )
        return nullptr;

//    // Si on survol pas la fenetre on sort direct
//    if ( ! getGlobalBounds().contains( posSouris.x, posSouris.y ) )
//        return nullptr;



    // on regarde dans les enfants
    for (  int i =  m_enfants.size()-1 ; i>=0 ; i--){
        auto enfant = m_enfants[i];
        if ( enfant->testerSurvol ( posSouris ) != nullptr )
            return enfant->testerSurvol ( posSouris );
    }

    // sinon renvois rien
    return nullptr;

}



} // fin namespace gui

