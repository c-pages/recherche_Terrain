/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/outils/AffInfoBulle.h>
#include <gui.h>



namespace gui {

/////////////////////////////////////////////////
AffInfoBulle::AffInfoBulle ()
: Affiche ()
{

    // Creation du nom unique du gadget
    creerNomUnique( "InfoBulle" );

    m_marge     = {4,4};
    m_visible   = false;

    // initialiser les composants herités
    CmpOmbre::initialiserComposants ( this );
    CmpFond::initialiserComposants  ( this );
    CmpTexte::initialiserComposants ( this );

    // DEBUG (a suppr.)
    setTexte( "InfoBulle" );


    setFondCouleur ( sf::Color::White );
    setFondLigneCouleur ( sf::Color::Black );
    setFondLigneEpaisseur ( 1 );

    setTexteCouleur( sf::Color::Black );
    setTexteTaille( 10 );

//    m_chronoDeclenchementInfo;

}


/////////////////////////////////////////////////
void AffInfoBulle::actualiserGeometrie ()
{
    // Debuggage
    log ("actualiserGeometrie");

    m_label->setPosition( int( m_marge.x ) , int ( m_marge.y/2 ) );
    m_label->actualiserBounds();

    m_taille = { m_label->getTaille().x + m_marge.x*2 , m_label->getTaille().y + m_marge.y*2 } ;

    m_fond->setTaille ( {m_taille.x, m_taille.y} );
    m_ombre->setTaille ( {m_taille.x, m_taille.y} );

    demanderActuaBounds();
}

/////////////////////////////////////////////////
void AffInfoBulle::actualiserStyle ()
{
    // Debuggage
    log ("actualiserStyle");

    // on actualise le label
    CmpTexte::appliquerEtat ( this->etat() );

    // on actualise le rectangle
    CmpFond::appliquerEtat ( this->etat() );
}






} // fin namespace gui

