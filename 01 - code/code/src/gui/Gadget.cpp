/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gui/Gadget.h"
#include "gui/Gui.h"
#include "appli/Config.h"

#include <iostream>*

namespace gui {

/////////////////////////////////////////////////
Gadget::Gadget ()
: m_visible         ( true )
, m_parent          ( nullptr )
, m_enfants         (  )
, m_enfantsASupprimer ( )
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

//    m_shaderClip        =    app::Config::ms_shaders.get ( app::Config::Shaders::clipping );
//    m_shaderClipImage   =    app::Config::ms_shaders.get ( app::Config::Shaders::clipping );



    m_shaderClip.setParameter       ("texture"  , sf::Shader::CurrentTexture);
    m_shaderClipImage.setParameter  ("texture"  , sf::Shader::CurrentTexture);
    m_shaderClipImage.setParameter  ("aTexture" , true );

    m_enfantsASupprimer.clear();
}





////////////////////////////////////////////////////////////
void Gadget::setPosition( std::shared_ptr<Gadget> cible )
{
    setPosition ( cible->getPosition() );
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
    setPosition ( (int)(x) , (int)(y) );

}

////////////////////////////////////////////////////////////
void Gadget::setPosition(const sf::Vector2f& position)
{
    setPosition ( (int)(position.x) , (int)(position.y) );
}

////////////////////////////////////////////////////////////
void Gadget::setPosition(const sf::Vector2i& position)
{
    setPosition ( (int)( position.x) , (int)(position.y) );
}

/////////////////////////////////////////////////
void Gadget::move(float offsetX, float offsetY)
{
    Transformable::move( offsetX,  offsetY);
    actualiser();
}

////////////////////////////////////////////////////////////
void Gadget::move(const sf::Vector2f& offset)
{
    move( offset.x, offset.y );
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
void Gadget::aligner ( std::shared_ptr<Gadget> cible, Alignement alignementThis, Alignement alignementCible)
{
    if ( cible == nullptr ) return;

    sf::Vector2i pt_origine;
    sf::Vector2i pt_cible;
    sf::Vector2f pt_destination;

    // l'origine //////

    // la ligne vert. de gauche du gadget a bouger
    if ( alignementThis == Alignement::GaucheHaut
    ||   alignementThis == Alignement::Gauche
    ||   alignementThis == Alignement::GaucheBas )
        pt_origine.x = getPosAbs().x ;

    // la ligne vert. du milieu du gadget a bouger
    else if ( alignementThis == Alignement::Haut
         ||   alignementThis == Alignement::Centre
         ||   alignementThis == Alignement::Bas )
        pt_origine.x = getPosAbs().x + getSize().x/2;

    // la ligne vert. de droite du gadget a bouger
    else
        pt_origine.x = getPosAbs().x  + getSize().x;


    // la ligne horiz. du haut du gadget a bouger
    if ( alignementThis == Alignement::GaucheHaut
    ||   alignementThis == Alignement::Haut
    ||   alignementThis == Alignement::DroiteHaut )
        pt_origine.y = getPosAbs().y;

    // la ligne horiz. du milieu du gadget a bouger
    else if ( alignementThis == Alignement::Gauche
         ||   alignementThis == Alignement::Centre
         ||   alignementThis == Alignement::Droite )
        pt_origine.y = getPosAbs().y + getSize().y/2;

    // la ligne horiz. du bas du gadget a bouger
    else
        pt_origine.y = getPosAbs().y + getSize().y;





    // la destination //////

    // la ligne vert. de gauche du gadget a bouger
    if ( alignementCible == Alignement::GaucheHaut
    ||   alignementCible == Alignement::Gauche
    ||   alignementCible == Alignement::GaucheBas )
        pt_cible.x = cible->getPosAbs().x ;

    // la ligne vert. du milieu du gadget a bouger
    else if ( alignementCible == Alignement::Haut
         ||   alignementCible == Alignement::Centre
         ||   alignementCible == Alignement::Bas )
        pt_cible.x = cible->getPosAbs().x + cible->getSize().x/2;

    // la ligne vert. de droite du gadget a bouger
    else
        pt_cible.x = cible->getPosAbs().x  + cible->getSize().x;


    // la ligne horiz. du haut du gadget a bouger
    if ( alignementCible == Alignement::GaucheHaut
    ||   alignementCible == Alignement::Haut
    ||   alignementCible == Alignement::DroiteHaut )
        pt_cible.y = cible->getPosAbs().y;

    // la ligne horiz. du milieu du gadget a bouger
    else if ( alignementCible == Alignement::Gauche
         ||   alignementCible == Alignement::Centre
         ||   alignementCible == Alignement::Droite )
        pt_cible.y = cible->getPosAbs().y + cible->getSize().y/2;

    // la ligne horiz. du bas du gadget a bouger
    else
        pt_cible.y = cible->getPosAbs().y + cible->getSize().y;


    // et on deplace le gadget sur le point de destination
    pt_destination = { pt_cible.x - pt_origine.x ,  pt_cible.y - pt_origine.y };

    move ( pt_destination );

    actualiser();

}









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
        nouvelElement->getParent()->supprimerEnfant( nouvelElement ) ;

    // puis on l'ajoute
    m_enfants.push_back( nouvelElement );
    nouvelElement->setParent ( this );

    nouvelElement->actualiser();
    actualiser();

}

/////////////////////////////////////////////////
void Gadget::supprimerEnfant ( std::shared_ptr<Gadget> cible ) {

    for ( auto enfant : m_enfants )
        if ( enfant == cible )  {
            m_enfantsASupprimer.push_back( enfant );
            return;
        }

}



void Gadget::actuaListeSuppression (){

     // on gere la liste des enfants a supprimer
     if ( m_enfantsASupprimer.size() > 0 ) {
        for ( auto enfantASuppr : m_enfantsASupprimer ){
            int i=0;
            for ( auto enfant : m_enfants )    {
                if ( enfant == enfantASuppr ) {
                    m_enfants.erase( m_enfants.begin() + i );
                    break;
                }
                i++;
            }
        }
        m_enfantsASupprimer.clear();
    }

    // on fait pareil pour les enfants qui restent
    for ( auto enfant : m_enfants )
        enfant->actuaListeSuppression ();

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
   supprimerEnfant ( gadget );

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

