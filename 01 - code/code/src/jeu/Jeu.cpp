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
//, m_tailleCarte ( {4096, 4096 } )
, m_tailleCarte ( {2048, 2048 } )
//, m_tailleCarte ( {1920, 1920 } )
//, m_tailleCarte ( {1280, 720 } )
{
}


/////////////////////////////////////////////////
void Jeu::test ( sf::Vector2i pos )
{
    std::cout << "TEST : " << pos.x << " , " << pos.y << "\n";
    auto bTmp = m_terrain.estLibre ( pos, m_terrain.getEtageCourant()  );
    std::cout << "est libre ? : " << bTmp << "\n";
}


/////////////////////////////////////////////////
void Jeu::demarrerPartie (int seed)
{
    std::cout << "**** Nouvelle partie ****\n Creation du terrain\n";
    /// le terrain ///
    m_terrain.generer( seed , m_tailleCarte, 3 );

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
    target.clear    ( sf::Color( 0,50,90,50));
    target.draw     ( m_terrain, states );
}


} // fin namespace jeu

