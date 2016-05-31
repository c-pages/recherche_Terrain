/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "jeu/Etage.h"
#include "jeu/Terrain.h"

#include <iostream>

namespace jeu {

/////////////////////////////////////////////////
Etage::Etage ( Terrain* terrain, sf::Vector2i taille)
: m_terrain         ( terrain )
, m_mapCollision    ( )
, m_mapPheromones   ( )
, m_estCourant      ( false )
, m_mapSol          ( )
, m_taille          ( taille )

, m_couleurSol      ( sf::Color ( 150, 175, 130 ) )
, m_couleurTerre    ( sf::Color ( 110,  80,  80 ) )
, m_couleurOmbres   ( sf::Color (   0,   0, 100, 100 ) )
, m_couleurAO       ( sf::Color (   0,   0, 100, 150 ) )
{
    /// les shaders ///
    m_shaderAO.loadFromFile         ( "media/shaders/flouTableau.frag" , sf::Shader::Fragment );
    m_shaderAO.setParameter         ( "texture", sf::Shader::CurrentTexture );
    m_shaderAO.setParameter         ( "blur_radius", 0.001f );

    m_shaderOmbre.loadFromFile      ( "media/shaders/flouTableau.frag" , sf::Shader::Fragment );
    m_shaderOmbre.setParameter      ( "texture", sf::Shader::CurrentTexture );
    m_shaderOmbre.setParameter      ( "blur_radius", 0.0005f );

    m_shaderHachures.loadFromFile   ( "media/shaders/hachures&contours.frag" , sf::Shader::Fragment );
    m_shaderHachures.setParameter   ( "texture", sf::Shader::CurrentTexture );

    m_shaderGrille.loadFromFile     ( "media/shaders/grille.frag" , sf::Shader::Fragment );
    m_shaderGrille.setParameter     ( "texture", sf::Shader::CurrentTexture );
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



/////////////////////////////////////////////////
const sf::Texture* Etage::getTexture ()
{ return &m_texture; }


/////////////////////////////////////////////////
sf::RenderTexture* Etage::getRenderTexture ()
{ return &m_renderTexture; }

/////////////////////////////////////////////////
void Etage::appliquerTexture ( )
{
    m_texture  = m_renderTexture.getTexture();

    m_shapeTerre.setTexture         ( &m_texture );
    m_shapeOmbreTerre.setTexture    ( &m_texture );
    m_shapeAO.setTexture            ( &m_texture );

}


/////////////////////////////////////////////////
void Etage::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    // le sol
//    states.shader = &m_shaderGrille;
//    target.draw ( m_shapesol , states );
    // l'ombre de la terre
    auto shaderTmp = states.shader;

    states.shader = &m_shaderAO;
    target.draw ( m_shapeAO , states );
    states.shader = &m_shaderOmbre;
    target.draw ( m_shapeOmbreTerre , states );

/*

    // la terre
    if ( estCourant() )
        states.shader = &m_shaderHachures;
    else
        states.shader = &m_shaderGrille;
*/
    states.shader = shaderTmp;
    target.draw ( m_shapeTerre , states );

}


} // fin namespace jeu

