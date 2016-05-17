/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/BtnRectangle.h>



namespace gui {

/////////////////////////////////////////////////
BtnRectangle::BtnRectangle ()
: Bouton ()
{
    creerNomUnique( "BtnRectangle" );

    m_taille= {25,25};

    // initialiser les composants herités
    CmpFond::initialiserComposants ( this );

}


/////////////////////////////////////////////////
void BtnRectangle::actualiserGeometrie ()
{
    log ("actualiserGeometrie  ");

    m_fond->setTaille ( {m_taille.x, m_taille.y} );

    // Focus
    if ( aLeFocus () ){
        m_focusRect->setVisible();
        m_focusRect->setTaille ( m_taille );
    } else
        m_focusRect ->setVisible( false );

    demanderActuaBounds();
}

/////////////////////////////////////////////////
void BtnRectangle::actualiserStyle ()
{
    // Debuggage
    log ("ActualiserStyle");

    // on applique le style correspondant à l'état
    CmpFond::appliquerEtat( this->etat() );


}


} // fin namespace gui

