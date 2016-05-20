/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Bouton.h>
#include <appli/Config.h>
#include <iostream>

namespace gui {

/////////////////////////////////////////////////
Bouton::Bouton ( std::string texte , sf::Vector2i taille )
: m_etat        ( Repos )
, m_alphaRepos  ( 50 )
, m_alphaSurvol ( 200 )
, m_alphaPresse ( 255 )
{

    sf::Vector2i marge = { 5, 5 };

    /// Initialisation du texte SFML.
    m_texte.setString           ( texte );
    m_texte.setCharacterSize    ( 10 );
    m_texte.setColor            ( sf::Color (200,200,200) );
    m_texte.setFont             ( app::Config::ms_polices.get( app::Config::Polices::police_1 ) );

    /// Initialisation du rectangle SFML.
    m_fond.setFillColor        ( { 150, 150, 150 } );
    m_fond.setOutlineColor     ( { 150, 150, 150 } );
    m_fond.setOutlineThickness ( 1 );

    /// Si on a défini une taille on l'applique et on centre le texte, sinon on l'ajuste au texte.
    auto tailleTexte = m_texte.getGlobalBounds();

    if ( taille != sf::Vector2i( -1,-1 ) )
        m_size = { taille.x , taille.y } ;
    else
        m_size = { tailleTexte.width + 2*marge.x , tailleTexte.height + 2*marge.y } ;

    setEtat ( );
    actualiser();
}


/////////////////////////////////////////////////
void Bouton::setEtat (Etat etat)
{

    if ( etat == Etat::Fin ) etat = m_etat;

    m_etat = etat;
    sf::Color couleurFond = m_fond.getFillColor();
    switch ( m_etat ) {
        case Etat::Repos:
            couleurFond.a = m_alphaRepos;
            m_fond.setFillColor(couleurFond);
            break;
        case Etat::Survol:
            couleurFond.a = m_alphaSurvol;
            m_fond.setFillColor(couleurFond);
            break;
        case Etat::Presse:
            couleurFond.a = m_alphaPresse;
            m_fond.setFillColor(couleurFond);
            break;
    }

}









/////////////////////////////////////////////////
void Bouton::setTexte (std::string texte) {
    m_texte.setString( texte );
    actualiser ();
}

/////////////////////////////////////////////////
void Bouton::setTexteTaille (float taille) {
    m_texte.setCharacterSize( taille );
    actualiser ();
}

/////////////////////////////////////////////////
void Bouton::setTexteCouleur ( sf::Color couleur ) {
    m_texte.setColor( couleur );
}

/////////////////////////////////////////////////
void Bouton::setTexteStyle ( sf::Text::Style style ) {
    m_texte.setStyle( style );
    actualiser ();
}

/////////////////////////////////////////////////
void Bouton::setTextePolice (sf::Font& police) {
    m_texte.setFont( police );
    actualiser ();
}





/////////////////////////////////////////////////
void Bouton::setRemplissageCouleur ( sf::Color couleur ) {
    m_fond.setFillColor ( couleur );
    setEtat( m_etat ) ;
}


/////////////////////////////////////////////////
void Bouton::setContourCouleur ( sf::Color couleur ) {
    m_fond.setOutlineColor ( couleur );
}


/////////////////////////////////////////////////
void Bouton::setContourEpaisseur ( float epaisseur ) {
    m_fond.setOutlineThickness ( epaisseur );
}


/////////////////////////////////////////////////
void Bouton::setIcone (sf::Texture& texture ){

    // on applique la texture
    m_icone.setTexture  ( &texture );

    // on reajuste la taille du textureRect à la nouvelle texture
    m_icone.setTextureRect( {0,0,texture.getSize().x, texture.getSize().y} );
    m_icone.setSize ( { texture.getSize().x, texture.getSize().y } );

}


/////////////////////////////////////////////////
void Bouton::setAlphaEtats ( float repos , float survol, float press )
{
    m_alphaRepos    = repos;
    m_alphaSurvol   = survol;
    m_alphaPresse   = press;

    setEtat();
}










/////////////////////////////////////////////////
void Bouton::traiterEvenements (sf::Event evenement)
{

}


/////////////////////////////////////////////////
void Bouton::actualiser ()
{

    // la taille du fond
    m_fond.setSize     ( {m_size.x, m_size.y}  );

    // on centre le texte sur le fond
    auto tailleTexte = m_texte.getGlobalBounds();
    m_texte.setPosition ( (int)(m_fond.getSize().x/2 - tailleTexte.width/2), (int)(m_fond.getSize().y/2 - tailleTexte.height/2) );

    // on centre l'icone sur le fond
    m_icone.setPosition ( (int)(m_fond.getSize().x/2 - m_icone.getSize().x/2 ), (int)(m_fond.getSize().y/2 - m_icone.getSize().y/2 ) );

    // on actualise les bases du gadget (Bounds)
    Gadget::actualiser();
}


/////////////////////////////////////////////////
void Bouton::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    //On applique la transformation
    states.transform *= getTransform();

    // On dessine le rectangle
    target.draw ( m_fond , states );

    // on dessine l'icone si besoin
    if ( m_icone.getTexture() != nullptr )
        target.draw ( m_icone , states );

    // On dessine le texte
    target.draw ( m_texte , states );


}


/////////////////////////////////////////////////
Gadget* Bouton::testerSurvol (sf::Vector2i posSouris)
//std::shared_ptr<Gadget> Bouton::testerSurvol (sf::Vector2i posSouris)
{

//    std::cout << "testerSurvol\n";
    // Si on survol pas le gadget on sort
    if ( ! getGlobalBounds().contains( posSouris.x, posSouris.y ) ) return nullptr;


//    // On test le survol des composants
//    auto testInterfaceLocal = testerSurvolComposants( position );
//    if ( testInterfaceLocal != nullptr )
//        return testInterfaceLocal;
//
//    // On test le survol des enfants
//    auto testEnfants = testerSurvolEnfants( position );
//    if ( testEnfants != nullptr )
//        return testEnfants;

    // si on a rien survolé on renvois nous-même
    else  return this;
}


} // fin namespace gui

