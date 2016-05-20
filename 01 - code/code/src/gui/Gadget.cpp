/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/Gadget.h>

#include <iostream>

namespace gui {

/////////////////////////////////////////////////
Gadget::Gadget ()
: m_parent          ( nullptr )
, m_enfants         (  )
, m_size            ( {0,0} )
, m_globalBounds    ( {0,0,0,0} )
, m_localBounds     ( {0,0,0,0} )
, m_marge           ( { 5,5 })
{

}





////////////////////////////////////////////////////////////
void Gadget::setPosition(float x, float y)
{
    Transformable::setPosition ( (int)(x) , (int)(y) );
    actualiser();
}


////////////////////////////////////////////////////////////
void Gadget::setPosition(const sf::Vector2f& position)
{
    setPosition ( (int)(position.x) , (int)(position.y) );
}

////////////////////////////////////////////////////////////
void Gadget::setPosition(const sf::Vector2i& position)
{
    setPosition ( position.x , position.y );
}





/////////////////////////////////////////////////
sf::Vector2f Gadget::getPosAbs () const
{
    if (m_parent != nullptr)
        return getPosition() + m_parent->getPosAbs();
    else
        return getPosition();
}



/////////////////////////////////////////////////
void Gadget::setSize( sf::Vector2i val ){
    m_size = val;
    actualiser();
};





/////////////////////////////////////////////////
void Gadget::ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement ){
    m_enfants.push_back( nouvelElement );
    nouvelElement->setParent ( this );
}

/////////////////////////////////////////////////
void Gadget::retirerEnfant ( std::shared_ptr<Gadget> cible ) {
    int i =0;
    for ( auto enfant : m_enfants )    {
        if ( enfant == cible )        {
            m_enfants.erase( m_enfants.begin() + i );
            return;
        }
        i++;
    }
}



/////////////////////////////////////////////////
void Gadget::demander_etreDevant ()
{
    m_parent->mettreDevant ( thisPtr() );
}

/////////////////////////////////////////////////
void Gadget::mettreDevant ( std::shared_ptr<Gadget> gadget )
{
    std::cout << "mettreDevant : " << m_enfants.size() << "\n";

    // on supprime le gadget de sa place dans le tableau
   retirerEnfant ( gadget );


    // puis on le replace à la fin du tableau
    m_enfants.push_back( gadget );

}






/////////////////////////////////////////////////
Gadget* Gadget::testerSurvol (sf::Vector2i posSouris)
//std::shared_ptr<Gadget> Gadget::testerSurvol (sf::Vector2i posSouris)
{
    return nullptr;
}


/////////////////////////////////////////////////
void Gadget::traiterEvenements (sf::Event evenement)
{
    // on traite les évènement des enfants
    for ( auto enfant : m_enfants )
        enfant->traiterEvenements ( evenement );
}


/////////////////////////////////////////////////
void Gadget::actualiser ()
{

    // on actualise les positions des bounds
    if (m_parent != nullptr) {
        m_globalBounds.left = getPosition().x + m_parent->getPosAbs().x;
        m_globalBounds.top  = getPosition().y + m_parent->getPosAbs().y;
    } else {
        m_globalBounds.left = getPosition().x;
        m_globalBounds.top  = getPosition().y;
    }
    m_localBounds.width     = getPosition().x;
    m_localBounds.height    = getPosition().y;

    // on actualise les tailles des bounds
    m_globalBounds.width    = m_size.x;
    m_globalBounds.height   = m_size.y;
    m_localBounds.width     = m_size.x;
    m_localBounds.height    = m_size.y;

    // on actualise les enfants
    for ( auto enfant : m_enfants )
        enfant->actualiser ( );

}


/////////////////////////////////////////////////
void Gadget::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    //On applique la transformation
    states.transform *= getTransform();

    // on dessine les enfants
    for ( auto enfant : m_enfants )
        target.draw ( *enfant, states );
}


} // fin namespace gui

