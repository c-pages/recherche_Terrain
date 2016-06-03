/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "jeu/terrain/Terrain.h"
#include "jeu/terrain/Etage.h"
#include "outils/noiseutils.h"
#include "outils/Utilitaires.h"


#include <iostream>

namespace jeu {

/////////////////////////////////////////////////
Terrain::Terrain ( )
: m_etages              ( )
, m_ecartMin            ( 10 )
, m_nbreEtages          ( 3 )
, m_etageCourant        ( m_nbreEtages -1 )

, m_couleurBrume          ( sf::Color(255,255,255,30) )
//, m_couleurSol          ( sf::Color ( 180, 205, 160 ) )
//, m_couleurTerre        ( sf::Color ( 110,  80,  80 ) )
//, m_couleurOmbres       ( sf::Color (   0,   0, 100, 100 ) )
//, m_couleurAO           ( sf::Color (   0,   0, 100, 150 ) )
{

    // les shaders
    m_shaderAO.loadFromFile     ( "media/shaders/flouTableau.frag" , sf::Shader::Fragment );
    m_shaderAO.setParameter     ( "texture", sf::Shader::CurrentTexture );
    m_shaderAO.setParameter     ( "blur_radius", 0.002f );

    m_shaderOmbre.loadFromFile  ( "media/shaders/flouTableau.frag" , sf::Shader::Fragment );
    m_shaderOmbre.setParameter  ( "texture", sf::Shader::CurrentTexture );
    m_shaderOmbre.setParameter  ( "blur_radius", 0.001f );

    m_shaderHachures.loadFromFile   ( "media/shaders/hachures&contours.frag" , sf::Shader::Fragment );
    m_shaderHachures.setParameter   ( "texture", sf::Shader::CurrentTexture );
//    m_shaderHachures.setParameter   ( "colorTerre", sf::Color ( 85, 118, 55 ) );

    m_shaderGrille.loadFromFile     ( "media/shaders/grille.frag" , sf::Shader::Fragment );

}




/////////////////////////////////////////////////
void Terrain::generer ( int seed, sf::Vector2i tailleCarte, unsigned int nbrEtages  )
{
//
//    sf::Clock chrono;
//
//    std::cout << "Terrain::generer : seed="<< seed << " nbrEtages=" << nbrEtages << "\n";
//    sf::Clock chrono;
//    std::cout << "genereration du terrain :"<< toString(chrono.getElapsedTime().asSeconds() ) <<"s.\n";
    m_nbreEtages    = nbrEtages;
    m_etageCourant  = m_nbreEtages ;
    m_taille        = tailleCarte;

    m_shapeProfondeur.setSize       ( { m_taille.x, m_taille.y } );
    m_shapeProfondeur.setFillColor  ( m_couleurBrume );

    /// creation du perlin pinpin ///
    module::Perlin              perlinModule;       ///<  module à charger pour bruit de perlin
    perlinModule.SetOctaveCount ( 9 );              ///<  nombre d'octaves ( defaut :6 )
    perlinModule.SetFrequency   ( .7 );             ///<  la frequence ( un peu comme la taille )
    perlinModule.SetPersistence ( .5 );             ///<  la persistence gère la rugosité du bruit( mmm un peu comme le constraste)
    perlinModule.SetSeed        ( seed );

    /// On créer les étages ///
    for (int i = 0; i < m_nbreEtages; i++ ){

        std::cout << "Creation etage " << i << ".\n";

        std::shared_ptr<Etage> etage = std::make_shared<Etage> (this, m_taille, i ) ;
        m_etages.push_back( etage );

        // Dessiner la map avec des ronds
        auto renderTexture = etage->getRenderTexture();
        renderTexture->clear(sf::Color::Transparent);

        double valMin = 2./( m_nbreEtages +1 ) * i        - 1;

        // on dessine les ronds dans le renderTexture en fonction de la map de perlin
        for (  double y = 0; y<=m_taille.y/m_ecartMin; y++  )
            for (  double x = 0; x<=m_taille.x/m_ecartMin; x++ )
                if ( perlinModule.GetValue ( x/100, y/100, 0.5 ) > valMin )
                    dessinerRond( {x*m_ecartMin, y*m_ecartMin} , sf::Color::White , *renderTexture);

        // on l'applique a l'étage
        renderTexture->display();
        etage->appliquerTexture();
    }

    // creation du dernier étage vide
    auto etage = std::make_shared<EtageVide> (this, m_taille, m_etages.size() ) ;
    m_etages.push_back( etage );



//    std::cout << "genereration du terrain :"<< toString(chrono.getElapsedTime().asSeconds() ) <<"s.\n";
 /*   chrono.restart();
    /// Les plantations
    for (int i = 0; i < m_nbreEtages; i++ ){
        auto etage = m_etages[i];
        etage->genererPlantations( 20 / (i+1) );
    }

    std::cout << "plantation du terrain :"<< toString(chrono.getElapsedTime().asSeconds() ) <<"s.\n";

*/








    /// l'étage courant
    setEtageCourant( m_etageCourant );




//
//
//    /// les plantes ///
//    int nbrPlantes = 20;
//    for (int i = 0; i<nbrPlantes; i++){
//        std::shared_ptr<Plante> plante = std::make_shared<Plante> () ;
//        m_plantes.push_back( plante );
//        bool reussi = false;
//        while ( ! reussi  ) {
//            sf::Vector2i posTest =   { rand()% m_taille.x, rand()% m_taille.y };
//            reussi =  estLibre ( {rand()% m_taille.x, rand()% m_taille.y},1 );
//            if ( reussi )
//            {
//                plante->setPosition( posTest.x, posTest.y );
//            }
//        }
//    }


}




/////////////////////////////////////////////////
bool Terrain::estLibre ( sf::Vector2i pos, int etage, int rayon  )
{
    if ( etage<0 || etage>m_nbreEtages )
        return false;

    return m_etages[etage]->estLibre ( pos, rayon );
}




/////////////////////////////////////////////////
void Terrain::setShadersOrigin ( sf::Vector2f pos ){
    m_shaderGrille.setParameter     ( "origin", pos );
    m_shaderHachures.setParameter   ( "origin", pos );
};

/////////////////////////////////////////////////
void Terrain::setEtageCourant( int val ){

    if ( val < 0 )              val = 0;
    if ( val > m_nbreEtages  )  val = m_nbreEtages ;

    m_etages[ m_etageCourant ]->setCourant(false);
    m_etageCourant = val;
    m_etages[ m_etageCourant ]->setCourant();

};



/////////////////////////////////////////////////
void Terrain::dessinerRond ( sf::Vector2i centre, sf::Color couleur, sf::RenderTexture& renderTexture )
{
    int rayon =  rand()% 20 + m_ecartMin;

    sf::CircleShape cercle ( rayon );
    cercle.setPosition( centre.x, centre.y );
    cercle.setFillColor( couleur );
    cercle.setOrigin ( rayon ,rayon );

    renderTexture.draw(cercle);

}




/////////////////////////////////////////////////
void Terrain::vider ()
{

}




/////////////////////////////////////////////////
void Terrain::actualiser (sf::Time deltaT )
{
    for ( auto etage : m_etages)
        etage->actualiser ( deltaT );
}


/////////////////////////////////////////////////
void Terrain::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    for ( int i=0; i<=m_etageCourant; i++ ) {

        states.shader = nullptr;
        target.draw ( m_shapeProfondeur , states );

        if ( i==m_etageCourant)
            states.shader = &m_shaderHachures;
        else //if ( i==m_etageCourant-1)
            states.shader = &m_shaderGrille;
//        else
//            states.shader = nullptr;

        target.draw ( *m_etages[  i  ] , states );
    }

/*
            states.shader = &m_shaderHachures;
            target.draw ( *m_etages[  m_etageCourant  ] , states );

*/
}


} // fin namespace jeu

