/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gui/Gadget.h"
#include "gui/Gui.h"

#include <iostream>

namespace gui {

/////////////////////////////////////////////////
Gadget::Gadget ()
: m_visible         ( true )
, m_parent          ( nullptr )
, m_enfants         (  )
, m_size            ( {0,0} )
, m_globalBounds    ( {0,0,0,0} )
, m_localBounds     ( {0,0,0,0} )
, m_marge           ( { 5,5 })
, m_shaderClip      ( )
, m_shaderClipImage ( )
{

    /// Initialisation du shader SANS le ressource manager !! ATTENTION a corriger !!
    if (! m_shaderClip.loadFromFile( "media/shaders/clippingMask.frag", sf::Shader::Fragment ) )
        std::cout << "PROBLEME CHARGEMENT SHADER\n";
    if (! m_shaderClipImage.loadFromFile( "media/shaders/clippingMask.frag", sf::Shader::Fragment ) )
        std::cout << "PROBLEME CHARGEMENT SHADER\n";

    m_shaderClip.setParameter("texture", sf::Shader::CurrentTexture);
    m_shaderClipImage.setParameter("texture", sf::Shader::CurrentTexture);
    m_shaderClipImage.setParameter("aTexture", true );

}





////////////////////////////////////////////////////////////
void Gadget::setPosition(int x, int y)
{
    Transformable::setPosition ( (int)(x) , (int)(y) );
    actualiser();
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
    Transformable::setPosition ( (int)(position.x) , (int)(position.y) );
    actualiser();
}

////////////////////////////////////////////////////////////
void Gadget::setPosition(const sf::Vector2i& position)
{
    Transformable::setPosition ( position.x , position.y );
    actualiser();
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
void Gadget::setSize( int x , int y )
{
     m_size = { x , y };
    actualiser();
}



/////////////////////////////////////////////////
void Gadget::setSize( sf::Vector2i val ){
    m_size = val;
    actualiser();
};


/////////////////////////////////////////////////
sf::IntRect  Gadget::getEnfantsLocalBounds()
{
    sf::IntRect result;
    if ( m_enfants.size() == 0 )
        return result;

    int minX = 90000;
    int minY = 90000;
    int maxX = -90000;
    int maxY = -90000;


    for ( auto enfant : m_enfants )
    {
        auto LB = enfant->getLocalBounds();

        if (LB.left < minX) minX = LB.left;
        if (LB.top  < minY) minY = LB.top;
        if (LB.left + LB.width > maxX ) maxX = LB.left + LB.width;
        if (LB.top  + LB.height> maxY ) maxY = LB.top  + LB.height;

    }

    result  = { minX, minY, maxX, maxY };

    return result;
}


/////////////////////////////////////////////////
void Gadget::ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement ){

    // on retire l'enfant de son ancien parent si besoin
    if ( nouvelElement->getParent() != nullptr )
        nouvelElement->getParent()->retirerEnfant( nouvelElement ) ;

    // puis on l'ajoute
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
    // si non visible on sort
    if (! estVisible () ) return;

    // on traite les évènement des enfants
    for ( auto enfant : m_enfants )
        enfant->traiterEvenements ( evenement );
}


/////////////////////////////////////////////////
void Gadget::actualiser ()
{

    // on actualise les positions des bounds
    m_globalBounds.left     = getPosAbs().x;
    m_globalBounds.top      = getPosAbs().y;
    m_localBounds.left      = getPosition().x;
    m_localBounds.top       = getPosition().y;

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
void Gadget::actualiserClipping ( sf::IntRect bounds )
{

//    std::cout << "actualiserClipping : " << bounds.left << " , " << bounds.top << " , " << bounds.width << " , " << bounds.height << "\n";
    m_shaderClip.setParameter( "rectMasque" , bounds.left
                                            , Gui::getFenetreSFML()->getSize().y - bounds.top
                                            , bounds.width
                                            , bounds.height );
    m_shaderClipImage.setParameter( "rectMasque"    , bounds.left
                                                    , Gui::getFenetreSFML()->getSize().y - bounds.top
                                                    , bounds.width
                                                    , bounds.height );

    for ( auto enfant : m_enfants )
        enfant->actualiserClipping ( bounds );

}



/////////////////////////////////////////////////
void Gadget::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    // si non visible on sort
    if (! estVisible () ) return;

    //On applique la transformation
    states.transform *= getTransform();

    // on dessine les enfants
    for ( auto enfant : m_enfants )
        target.draw ( *enfant, states );
}


} // fin namespace gui

