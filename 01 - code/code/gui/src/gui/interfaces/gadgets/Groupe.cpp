#include "interfaces/gadgets/Groupe.h"

namespace gui {

Groupe::Groupe()
{
    creerNomUnique( "Groupe");
    //ctor
}

Groupe::~Groupe()
{
    //dtor
}


/////////////////////////////////////////////////
sf::Vector2i Groupe::getTaille () const{
    int posXmin =  1000000;
    int posYmin =  1000000;
    int posXmax = -1000000;
    int posYmax = -1000000;

    for ( auto enfant : m_enfants )    {
        if (enfant->getPosition().x<posXmin) posXmin = enfant->getPosition().x;
        if (enfant->getPosition().y<posYmin) posYmin = enfant->getPosition().y;
        if (enfant->getPosition().x + enfant->getTaille().x >posXmax ) posXmax = enfant->getPosition().x + enfant->getTaille().x;
        if (enfant->getPosition().y + enfant->getTaille().y >posYmax ) posYmax = enfant->getPosition().y + enfant->getTaille().y;
    }

    return { posXmax - posXmin, posYmax - posYmin };
}

/////////////////////////////////////////////////
std::shared_ptr<Gadget>  Groupe::testerSurvol ( sf::Vector2i position )
{
    // On test le survol des enfants
    auto testEnfants = testerSurvolEnfants( position );
    if ( testEnfants != nullptr )
        return testEnfants;
    else  return nullptr;

}










} // namespace gui
