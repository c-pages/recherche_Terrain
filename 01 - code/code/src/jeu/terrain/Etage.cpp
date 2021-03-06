/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "jeu/terrain/Etage.h"
#include "jeu/terrain/Terrain.h"

#include <iostream>

namespace jeu {

/////////////////////////////////////////////////
Etage::Etage ( Terrain* terrain, sf::Vector2i taille, int index )
: m_index           ( index )
, m_terrain         ( terrain )
//, m_mapCollision    ( )
//, m_mapPheromones   ( )
, m_estCourant      ( false )
, m_imageTerre          ( )
, m_taille          ( taille )

//, m_couleurSol      ( sf::Color ( 150, 175, 130 ) )
, m_couleurSol      ( sf::Color ( 85, 118, 55 ) )
, m_couleurTerre    ( sf::Color ( 70,  60,  60 ) )

, m_couleurOmbres   ( sf::Color (   0,   0, 100, 100 ) )
, m_couleurAO       ( sf::Color (   0,   0, 100, 150 ) )
{
    /// les shaders ///
    m_shaderAO.loadFromFile         ( "media/shaders/flouTableau.frag" , sf::Shader::Fragment );
    m_shaderAO.setParameter         ( "texture", sf::Shader::CurrentTexture );
    m_shaderAO.setParameter         ( "blur_radius", 0.004f );

    m_shaderOmbre.loadFromFile      ( "media/shaders/flouTableau.frag" , sf::Shader::Fragment );
    m_shaderOmbre.setParameter      ( "texture", sf::Shader::CurrentTexture );
    m_shaderOmbre.setParameter      ( "blur_radius", 0.0005f );

//    m_shaderHachures.loadFromFile   ( "media/shaders/hachures&contours.frag" , sf::Shader::Fragment );
//    m_shaderHachures.setParameter   ( "texture", sf::Shader::CurrentTexture );
//
//    m_shaderGrille.loadFromFile     ( "media/shaders/grille.frag" , sf::Shader::Fragment );
//    m_shaderGrille.setParameter     ( "texture", sf::Shader::CurrentTexture );
//

    /// les shapes ///
    m_shapeTerre.setSize ( { m_taille.x, m_taille.y } );
    m_shapeTerre.setFillColor( m_couleurSol );

    m_shapeOmbreTerre.setSize ( { m_taille.x, m_taille.y } );
    m_shapeOmbreTerre.setPosition (3,3);
    m_shapeOmbreTerre.setFillColor( m_couleurOmbres );

    m_shapeAO.setSize ( { m_taille.x, m_taille.y } );
    m_shapeAO.setPosition (0,0);
    m_shapeAO.setFillColor( m_couleurAO );

    m_shapesol.setSize ( { m_taille.x, m_taille.y } );
//    m_shapesol.setFillColor( m_couleurSol );



    /// les textures ///
    m_renderTexture.create  ( m_taille.x, m_taille.y );
    m_texture.create        ( m_taille.x, m_taille.y );

}

///////////////////////////////////////////////////
//void Etage::genererPlantations ( int nbrePlantes ) {
//
//    /// les plantes ///
//    for (int i = 0; i<nbrePlantes; i++){
//        std::shared_ptr<Plante> plante = std::make_shared<Plante> ( this ) ;
//        m_plantes.push_back( plante );
//        bool reussi = false;
//        int rayon = 0;
//        while ( ! reussi  ) {
//            sf::Vector2i posTest =   { rand()% m_taille.x, rand()% m_taille.y };
//            reussi = ( estDeLaTerre ( {posTest.x, posTest.y} , rayon )
//                    && ! getEtageDessus()->estDeLaTerre( {posTest.x, posTest.y} , rayon ) );
//
//            if ( reussi ){
//                plante->setPosition( posTest.x, posTest.y );
//                std::cout << "on plante une graine\n";
//            }
//        }
//    }
//
//}


/////////////////////////////////////////////////
bool Etage::estLibre ( sf::Vector2i pos, int rayon ) const
{
    /// si pas d'etage en dessous on zappe
    if ( getEtageDessous() == nullptr )
        return false;


    /// on regarde si on tappe dans la terre (si on est pas le dernier etage(vide))
    if ( m_imageTerre.getSize().x != 0 )
        for ( int x = pos.x -rayon; x<= pos.x+rayon; x++ )
            for ( int y = pos.y-rayon; y<= pos.y+rayon; y++ ) {

                // si on sort de l'image on continue
                if ( x<0 || y<0 || x>m_taille.x-1 || y>m_taille.y-1 )
                    continue;

                if ( m_imageTerre.getPixel( x, y).a != 0 )
                    return false;
            }

    /// finalement on regarde si on a du sol (donc de la terre � l'�tage du dessous)
    return getEtageDessous()->estDeLaTerre( pos, rayon );

}


/////////////////////////////////////////////////
bool Etage::estDeLaTerre ( sf::Vector2i pos, int rayon ) const
{

    for ( int x = pos.x -rayon; x<= pos.x+rayon; x++ )
        for ( int y = pos.y-rayon; y<= pos.y+rayon; y++ ) {

            // si on sort de l'image on continue
            if ( x<0 || y<0 || x>m_taille.x-1 || y>m_taille.y-1 )
                continue;

            if ( m_imageTerre.getPixel( x, y).a == 0 )
                return false;
        }

    return  true;

}

/////////////////////////////////////////////////
void Etage::setCourant ( bool val  ) {
    m_estCourant = val;
    if ( m_estCourant )
        m_shapeTerre.setFillColor( m_couleurTerre );
    else
        m_shapeTerre.setFillColor( m_couleurSol );
}


/////////////////////////////////////////////////
bool Etage::estCourant () const
{return m_estCourant;}


/////////////////////////////////////////////////
bool Etage::estCoupe () const
{
    if ( m_index > m_terrain->getNbreEtages() -1 )
        return false;

    return m_terrain->getEtage ( m_index + 1 )->estCourant ();
}


/////////////////////////////////////////////////
const sf::Texture* Etage::getTexture ()
{ return &m_texture; }


/////////////////////////////////////////////////
sf::RenderTexture* Etage::getRenderTexture ()
{ return &m_renderTexture; }



/////////////////////////////////////////////////
std::shared_ptr<Etage> Etage::getEtageDessous() const
{
    if ( m_index == 0)
        return nullptr;
    return m_terrain->getEtage( m_index - 1 );
}

/////////////////////////////////////////////////
std::shared_ptr<Etage> Etage::getEtageDessus()const
{
    if ( m_index == m_terrain->getNbreEtages() )
        return nullptr;
    return m_terrain->getEtage( m_index + 1 );
}



/////////////////////////////////////////////////
void Etage::appliquerTexture ( )
{
    m_texture  = m_renderTexture.getTexture();
    m_imageTerre   = m_texture.copyToImage();

    m_shapeTerre.setTexture         ( &m_texture );
    m_shapeOmbreTerre.setTexture    ( &m_texture );
    m_shapeAO.setTexture            ( &m_texture );

}


/////////////////////////////////////////////////
void Etage::actualiser (sf::Time deltaT )
{
//    for ( auto plante : m_plantes )
//        plante->actualiser ( deltaT );
}



/////////////////////////////////////////////////
void Etage::draw (sf::RenderTarget& target, sf::RenderStates states) const
{


    auto shaderTmp = states.shader;

    states.shader = &m_shaderAO;
    target.draw ( m_shapeAO , states );




    states.shader = &m_shaderOmbre;
    target.draw ( m_shapeOmbreTerre , states );

    states.shader = shaderTmp;
    target.draw ( m_shapeTerre , states );

//    /// les plantes ///
//    if ( estCourant( ) ) {
//        states.shader = nullptr;
//        for (auto plante : m_plantes )
//            target.draw ( *plante , states );
//    }

}


} // fin namespace jeu

