/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <interfaces/Composition.h>
#include <interfaces/Gadget.h>



namespace gui {

/////////////////////////////////////////////////
void Composition::traiterEvenementsComposants (const sf::Event& evenement)
{
    for ( auto composant : m_composants )
        composant->traiterEvenements ( evenement );
}


/////////////////////////////////////////////////
void Composition::ajouterComposant ( std::shared_ptr<Gadget> enfant )
{
    m_composants.push_back( enfant );
    enfant->setParent ( dynamic_cast<Gadget*>(this) );
}


/////////////////////////////////////////////////
void Composition::retirerComposant ( std::shared_ptr<Gadget> enfant )
{
    int i =0;
    for ( auto composant : m_composants )
    {
        if ( composant == enfant )
        {
            composant->setParent ( nullptr );
            m_composants.erase( m_composants.begin() + i );
            return;
        }
        i++;
    }
}


/////////////////////////////////////////////////
void Composition::mettre_composantAuDessus (std::shared_ptr<Gadget> gadget)
{

}

/////////////////////////////////////////////////
void Composition::actualiserComposants ()
{
//    static_cast<Gadget*>(this)->log ("actualiserComposants");
    for ( auto composant : m_composants )
        composant->actualiser();
}

///////////////////////////////////////////////////
//void Composition::demanderActuaBoundsComposants ()
//{
////    static_cast<Gadget*>(this)->log ("actualiserComposants");
//    for ( auto composant : m_composants ){
//        composant->demanderActuaBounds();
//        //actualiser les composants des composants ...
//        composant->demanderActuaBoundsComposants ();
//    }
//}



/////////////////////////////////////////////////
std::shared_ptr<Gadget> Composition::testerSurvolComposants (sf::Vector2i position)
{

    for ( int i =0; i< m_composants.size(); i++ )
    {
        int index = m_composants.size() - (i+1);
//        int index = i;
        auto  composant = m_composants[ index ];

        auto testComposant = composant->testerSurvol( position );
        if ( testComposant != nullptr )
            return testComposant;
    }
    return nullptr;
}


/////////////////////////////////////////////////
void Composition::dessinerComposant (sf::RenderTarget& target, sf::RenderStates states) const
{
    for ( auto composant : m_composants )
        target.draw( *composant, states );
}


} // fin namespace gui

