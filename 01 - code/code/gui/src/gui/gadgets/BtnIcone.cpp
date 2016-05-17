/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/BtnIcone.h>



namespace gui {

/////////////////////////////////////////////////
BtnIcone::BtnIcone ()
: BtnRectangle ()
, m_fix ( false )
{
    creerNomUnique( "BtnIcone" );
    m_marge       = { 1 , 1} ;

//    //debug
//    m_mute = false;


    // initialiser les composants herités
    CmpIcone::initialiserComposants ( this );

    m_icone->setIndex ( 1 );

}


/////////////////////////////////////////////////
void BtnIcone::actualiserGeometrie ()
{
    log ( "actualiserGeometrie" );
    log ( "m_autoAjust", m_autoAjust );
    log ( "m_fond", m_fond->getPosAbs() );

    m_fond->setTaille ( {m_taille.x, m_taille.y} );

    m_icone->actualiserGeometrie();

    if ( m_autoAjust ){
        m_taille = { m_icone->getTaille().x + m_marge.x*2 , m_icone->getTaille().y + m_marge.y*2 } ;
        m_icone->setPosition( m_marge.x  , m_marge.y );
    } else {
        m_icone->alignerSur ( m_fond , Alignement::Centre , Alignement::Centre );
    }

    // Focus
    if ( aLeFocus () ){
        m_focusRect->setVisible();
        m_focusRect->setTaille ( m_taille );
    } else
        m_focusRect ->setVisible( false );

    demanderActuaBounds();
}

/////////////////////////////////////////////////
void BtnIcone::actualiserStyle ()
{
    log ("actualiserStyle");

    m_icone->setFondCouleur    ( sf::Color (
                                      255
                                    , 255
                                    , 255
                                    , 255 * m_opacite ) ) ;

    m_icone->setFondLigneEpaisseur ( 0 ) ;

    if ( ! m_fix )    {
        switch ( this->etat() ){
            case Etat::repos:       m_icone->setIndex ( 1 );    break;
            case Etat::survol:      m_icone->setIndex ( 2 );    break;
            case Etat::press:       m_icone->setIndex ( 3 );    break;
            case Etat::desactive:   m_icone->setIndex ( 4 );    break;
            default: break;
        }
    }

    // on applique le style correspondant à l'état au rectangle
    m_fond->setFondCouleur       ( sf::Color ( m_fondCouleur.get( this->etat() ).r
                                                , m_fondCouleur.get( this->etat() ).g
                                                , m_fondCouleur.get( this->etat() ).b
                                                , m_fondCouleur.get( this->etat() ).a * m_opacite ) ) ;
    m_fond->setFondLigneCouleur    ( sf::Color ( m_fondLgnCouleur.get( this->etat() ).r
                                                , m_fondLgnCouleur.get( this->etat() ).g
                                                , m_fondLgnCouleur.get( this->etat() ).b
                                                , m_fondLgnCouleur.get( this->etat() ).a * m_opacite ) ) ;
    m_fond->setFondLigneEpaisseur ( m_fondLgnEpaisseur.get( this->etat() ) ) ;

}



/////////////////////////////////////////////////
void BtnIcone::setFix (bool val) {
    m_fix = val;
};


} // fin namespace gui























