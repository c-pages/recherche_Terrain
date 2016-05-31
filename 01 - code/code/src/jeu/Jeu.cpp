/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "jeu/Jeu.h"
#include "jeu/Terrain.h"

#include <iostream>


namespace jeu {

/////////////////////////////////////////////////
Jeu::Jeu (app::Ecran::Contexte contexte)
: m_contexte    ( contexte )
, m_tailleCarte ( {4096, 4096 } )
{
}




/////////////////////////////////////////////////
void Jeu::demarrerPartie (int seed)
{
    std::cout << "**** Nouvelle partie ****\n Creation du terrain";
    /// le terrain ///
    m_terrain.generer( seed , m_tailleCarte, 3);

    /// planter la vegetation ///



}


/////////////////////////////////////////////////
void Jeu::quitterPartie ()
{

}


/////////////////////////////////////////////////
void Jeu::chargerPartie ()
{

}


/////////////////////////////////////////////////
void Jeu::sauvegarderPartie ()
{

}












/////////////////////////////////////////////////
void Jeu::etageMonter ()
{
    m_terrain.setEtageCourant( m_terrain.getEtageCourant() + 1 );
}


/////////////////////////////////////////////////
void Jeu::etageDescendre ()
{
    m_terrain.setEtageCourant( m_terrain.getEtageCourant() - 1 );
}




/////////////////////////////////////////////////
void Jeu::actualiser (sf::Time deltaT)
{

}


/////////////////////////////////////////////////
void Jeu::traiterEvenements (sf::Event evenement)
{

}


/////////////////////////////////////////////////
void Jeu::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.clear( sf::Color( 0,50,90));
    target.draw     ( m_terrain, states );
}


} // fin namespace jeu

