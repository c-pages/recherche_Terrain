/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/BtnTexte.h>
#include <gui.h>




namespace gui {

/////////////////////////////////////////////////
BtnTexte::BtnTexte ()
: BtnRectangle ()
//, m_label       ( std::make_shared<AffLabel>())
{
    creerNomUnique ( "BtnTexte");

    m_marge = { 5, 5 };
    m_texte = "Bouton";

    // initialiser les composants herités
    CmpTexte::initialiserComposants ( this );

    m_label->setTexte ( m_texte );

}

/////////////////////////////////////////////////
void BtnTexte::actualiserGeometrie ()
{
    // Debuggage
    log ( "actualiserGeometrie" );

    m_label->setPosition( int( m_marge.x ) , int ( m_marge.y/3 ) );

    if ( m_autoAjust ){
        m_label->actualiserBounds();
        m_taille = { m_label->getTaille().x + m_marge.x*2 , m_label->getTaille().y + m_marge.y*2 } ;
    }

    m_fond->setTaille ( {m_taille.x, m_taille.y} );

    demanderActuaBounds();
}

/////////////////////////////////////////////////
void BtnTexte::actualiserStyle ()
{
    // Debuggage
    log ("actualiserStyle");

    // on actualise le label
    CmpTexte::appliquerEtat ( this->etat() );

    // on actualise le rectangle
    CmpFond::appliquerEtat ( this->etat() );

}


} // fin namespace gui

