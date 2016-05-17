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

    // initialiser les composants herit�s
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

    // on applique le style correspondant � l'�tat
    CmpFond::appliquerEtat( this->etat() );


}


} // fin namespace gui

