/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "jeu/Jeu.h"
#include "jeu/terrain/Terrain.h"
#include "jeu/terrain/Etage.h"

#include "outils/Utilitaires.h"
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
    std::cout << "TEST : " << pos.x << " , " << pos.y << " --> ";
    auto bTmp = m_terrain.estLibre ( pos, m_terrain.getEtageCourant() , 20 );
    std::cout << " est libre ? : " << bTmp << "\n";
}


/////////////////////////////////////////////////
void Jeu::demarrerPartie (int seed)
{
    std::cout << "**** Nouvelle partie ****\n Creation du terrain\n";
    /// le terrain ///

    sf::Clock chrono;

    m_terrain.generer( seed , m_tailleCarte, 5 );
    std::cout << "genereration du terrain :"<< toString(chrono.getElapsedTime().asSeconds() ) <<"s.\n";

    /// planter la vegetation ///
    chrono.restart();
    genererPlantations ( 100 );
    std::cout << "genereration de la vegetation :"<< toString(chrono.getElapsedTime().asSeconds() ) <<"s.\n";

    m_terrain.setEtageCourant( 2 );
}



/////////////////////////////////////////////////
void Jeu::genererPlantations ( int nbrePlantes ) {

    /// les plantes ///
    for (int i = 0; i<nbrePlantes; i++){

        bool reussi = false;
        int rayon = 20;

        while ( ! reussi  ) {
            int             numEtage    = rand()% m_terrain.getNbreEtages();
            sf::Vector2i    posTest     = { rand()% m_tailleCarte.x, rand()% m_tailleCarte.y };
            auto            etage       = m_terrain.getEtage( numEtage );

            reussi = (      etage->estDeLaTerre ( {posTest.x, posTest.y} , rayon )
                    &&      etage->getEtageDessus()->estLibre( {posTest.x, posTest.y} , rayon ) );
//                    &&    ! etage->getEtageDessus()->estDeLaTerre( {posTest.x, posTest.y} , rayon ) );

            if ( reussi ){
                std::shared_ptr<Plante> plante = std::make_shared<Plante> ( etage ) ;
                m_plantes.push_back( plante );
                plante->setPosition( posTest.x, posTest.y );
//                std::cout << "on plante une graine\n";
            }

        } // fin while
    } // fin for

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
    m_terrain.actualiser( deltaT );

    /// les plantes ///
    for ( auto plante : m_plantes )
        plante->actualiser ( deltaT );

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

    /// les plantes ///
//    if ( estCourant( ) ) {
        states.shader = nullptr;
        for (auto plante : m_plantes )
            target.draw ( *plante , states );
//    }

}


} // fin namespace jeu

