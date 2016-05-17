#include "interfaces/gadgets/Calque.h"

namespace gui {

Calque::Calque( std::string nom )
{
    //creerNomUnique( "Calque");
    m_nom = nom;
    //ctor
    m_mute=false;
}

Calque::~Calque()
{
    //dtor
}

/////////////////////////////////////////////////
void Calque::actualiser ()
{
    actualiserEnfants();

    if (m_enfantsASupprimer.size()> 0)
        actualiserListes();
}

/////////////////////////////////////////////////
std::shared_ptr<Gadget>  Calque::testerSurvol ( sf::Vector2i position )
{

    // On test le survol des enfants
    auto testEnfants = testerSurvolEnfants( position );
    if ( testEnfants != nullptr )
        return testEnfants;
    else  return nullptr;

}


}
//
