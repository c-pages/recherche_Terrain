/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Bouton.h>
#include <appli/Config.h>
#include <iostream>

namespace gui {

/////////////////////////////////////////////////
Bouton::Bouton ( std::string texte , sf::Vector2i taille )
: m_etat ( Repos )
//, m_couleurRepos    ( {  50,  50,  50 } );
//, m_couleurSurvol   ( {  70,  70,  70 } );
//, m_couleurPresse   ( { 100, 100, 100 } );
{

    sf::Vector2i marge = { 5, 5 };

    /// Initialisation du texte SFML.
    m_texte.setString           ( texte );
    m_texte.setCharacterSize    ( 10 );
    m_texte.setColor            ( sf::Color (200,200,200) );
    m_texte.setFont             ( app::Config::ms_polices.get( app::Config::Polices::police_1 ) );

    /// Initialisation du rectangle SFML.
    m_shape.setFillColor        ( { 150, 150, 150 } );
    m_shape.setOutlineColor     ( { 150, 150, 150 } );
    m_shape.setOutlineThickness ( 1 );

    /// Si on a défini une taille on l'applique et on centre le texte, sinon on l'ajuste au texte.
    auto tailleTexte = m_texte.getGlobalBounds();
    if ( taille != sf::Vector2i( -1,-1 ) ) {
        m_shape.setSize     ( { taille.x , taille.y } );
        m_texte.setPosition ( (int)(taille.x/2 - tailleTexte.width/2), (int)(taille.y/2 - tailleTexte.height/2) );

    } else {
        m_shape.setSize ( { tailleTexte.width + 2*marge.x , tailleTexte.height + 2*marge.y } );
        m_texte.setPosition ( (int)(m_shape.getSize().x/2 - tailleTexte.width/2), (int)(m_shape.getSize().y/2 - tailleTexte.height/2) );
    }

    m_size = {m_shape.getSize().x, m_shape.getSize().y };
    setEtat (m_etat);
    actualiser();
}


/////////////////////////////////////////////////
void Bouton::setEtat (Etat etat)
{
    m_etat = etat;
    sf::Color couleurFond = m_shape.getFillColor();
    switch ( m_etat ) {
        case Etat::Repos:
            couleurFond.a = 50;
            m_shape.setFillColor(couleurFond);
            break;
        case Etat::Survol:
            couleurFond.a = 100;
            m_shape.setFillColor(couleurFond);
            break;
        case Etat::Presse:
            couleurFond.a = 150;
            m_shape.setFillColor(couleurFond);
            break;
    }

}


/////////////////////////////////////////////////
void Bouton::traiterEvenements (sf::Event evenement)
{

}


/////////////////////////////////////////////////
void Bouton::actualiser ()
{
    // on actualise les bases du gadget (Bounds)
    Gadget::actualiser();
}


/////////////////////////////////////////////////
void Bouton::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    //On applique la transformation
    states.transform *= getTransform();

    // On dessine le rectangle
    target.draw ( m_shape , states );

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

