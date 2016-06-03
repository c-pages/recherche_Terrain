/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "jeu/vegetation/Plante.h"
#include "jeu/terrain/Etage.h"
#include "appli/Config.h"
#include "outils/Utilitaires.h"

#include <iostream>


namespace jeu {

/////////////////////////////////////////////////
Plante::Plante  ( std::shared_ptr<Etage>  etage )
: m_etageParent ( etage )
, m_age         ( 0 )
//, m_age         ( rand()% 1000 )
{
    int rayon = 6;
    m_shape.setRadius      ( rayon );
    m_shape.setOrigin      ( rayon,rayon );
    m_shape.setFillColor   ( sf::Color( 150, 80,50) );

    m_texte.setCharacterSize    ( 10 );
    m_texte.setColor            ( sf::Color( 255 , 255, 255, 100 ) );
    m_texte.setFont             ( app::Config::ms_polices.get ( app::Config::Polices::police_1 ) );

    actualiser();

}


/////////////////////////////////////////////////
int Plante::getAge()
{
//    return (int)(m_age / 10);
    return (int)(m_age / 1);
}


/////////////////////////////////////////////////
void Plante::creerNouvelleRacine ()
{



    if ( m_racines.size() != 0)
        return;

    float val = ( rand()% 10000 ) / 100. ;
    bool test = ( val < 0.5 );


    if ( test ) {
        std::shared_ptr<Racine> racine = std::make_shared<Racine> (this);
        m_racines.push_back( racine );

        int randX = rand()% int ( m_shape.getRadius() ) * 2 - m_shape.getRadius();
        int randY = rand()% int ( m_shape.getRadius() ) * 2 - m_shape.getRadius();

    }

}


/////////////////////////////////////////////////
void Plante::actualiser (sf::Time deltaT )
{
    m_ageBack = getAge();
    m_age += deltaT.asSeconds();

    for (auto racine : m_racines )
        racine->pousser();

    // chaque 1 secondes
    if ( m_ageBack == getAge() )
        return;

    creerNouvelleRacine ();

}



/////////////////////////////////////////////////
void Plante::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    if ( ! m_etageParent->estCourant() )
        return;

    //On applique la transformation
    states.transform *= getTransform();



    for (auto racine : m_racines )
        target.draw ( *racine , states );


    target.draw ( m_shape , states );
    target.draw ( m_texte , states );

}









/////////////////////////////////////////////////
Plante::Racine::Racine ( Plante* plante )
: m_parent  ( plante )
, m_angle    ( rand()% 360 )
{
    int rayon = 1;

    m_shape.setRadius      ( rayon );
    m_shape.setOrigin      ( rayon,rayon );
    m_shape.setFillColor   ( sf::Color ( 78, 193, 68) );

    actualiser();

}


/////////////////////////////////////////////////
void Plante::Racine::pousser ( )
{
    float   val     = ( rand()% 10000 ) / 100. ;
    float   max     = 2. / m_shape.getRadius ();
    bool    test    = ( val < max );
    float   increment = 0.1;

    std::string txtTmp ="test : " + toString( test ) +   "\nrayon : " + toString(  m_shape.getRadius ()  ) +    "\nmax : " + toString( max  ) +    "\nval : " + toString( val );
    m_parent->m_texte.setString( txtTmp );

    if (test) {
        m_shape.setRadius      ( m_shape.getRadius () + increment );
        actualiser();
    }
}


/////////////////////////////////////////////////
void Plante::Racine::actualiser (sf::Time deltaT )
{
    double rad = m_angle*PI/180;
    float  rayonParent = m_parent->m_shape.getRadius();
    sf::Vector2f   vecNorm ((float)cos( rad ), (float)sin( rad ));
    sf::Vector2f   pos ( vecNorm.x * rayonParent, vecNorm.y * rayonParent );

    m_shape.setOrigin( m_shape.getRadius(), m_shape.getRadius() );
    setPosition ( pos.x, pos.y );

}

/////////////////////////////////////////////////
void Plante::Racine::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    //On applique la transformation
    states.transform *= getTransform();

    target.draw ( m_shape , states );

}




















} // fin namespace jeu

