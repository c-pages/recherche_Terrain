/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/DnGlissere.h>
#include <gui.h>



namespace gui {

/////////////////////////////////////////////////
DnGlissere::DnGlissere ()
: m_valeurMax   ( 100 )
, m_valeurMin   ( 0 )
//, m_horizontal  ( true )
, m_drag        ( false )
, m_decalageDragSouris ({0,0})
{

    creerNomUnique( "Glissiere" );

    m_marge = {0,0};

    // creer l'interface locale
    CmpGlissere::initialiserComposants ( this );

    // Declaration des fonctions de l'interface interne du gadget.
    fct_cliqueBtnFond   = [this](){
        if ( m_horizontal ) {
            if ( getLocalPosSouris().x > m_marge.x + m_slider->getTaille().x/2 + m_slider->getPosition().x ){
                incrementer ( );
                if ( m_slider->getPosition().x + ( m_slider->getTaille().x/2  ) > getLocalPosSouris().x )
                    deplacerSlider ();
            } else {
                decrementer ( );
                if ( m_slider->getPosition().x + ( m_slider->getTaille().x/2  ) < getLocalPosSouris().x )
                    deplacerSlider ();
            }
        } else {
            if ( getLocalPosSouris().y > m_marge.y + m_slider->getTaille().y/2 + m_slider->getPosition().y ){
                incrementer ( 20 );
                if ( m_slider->getPosition().y - ( m_slider->getTaille().y/2 + m_marge.y )  > getLocalPosSouris().y )
                    deplacerSlider ();
            } else {
                decrementer ( 20 );
                if ( m_slider->getPosition().y - ( m_slider->getTaille().y/2 + m_marge.y )  < getLocalPosSouris().y )
                    deplacerSlider ();
            }
        }
    };
    fct_dragStart       = [this](){
        m_decalageDragSouris = sf::Vector2i ( getLocalPosSouris().x - m_slider->getPosition().x , getLocalPosSouris().y - m_slider->getPosition().y );
        setDrag( true );
    };
    fct_dragStop        = [this](){
        setDrag( false );
    };
    fct_rouletteH       = [this](){
        if ( m_horizontal )
                incrementer();
        else    decrementer();
    };
    fct_rouletteB       = [this](){
        if ( m_horizontal )
                decrementer();
        else    incrementer();
    };

    // Actions du bouton
    m_boutonFond->lier ( Evenement::onBtnG_presser          , fct_cliqueBtnFond );
    m_boutonFond->lier ( Evenement::onBtnG_relacher         , fct_dragStop );
    m_boutonFond->lier ( Evenement::onBtnG_relacherDehors   , fct_dragStop );
    m_boutonFond->lier ( Evenement::onBtnM_roulerHaut       , fct_rouletteH );
    m_boutonFond->lier ( Evenement::onBtnM_roulerBas        , fct_rouletteB );

    // Actions du slider
    m_slider->lier ( Evenement::onBtnG_presser          , fct_dragStart );
    m_slider->lier ( Evenement::onBtnG_relacher         , fct_dragStop );
    m_slider->lier ( Evenement::onBtnG_relacherDehors   , fct_dragStop );
    m_slider->lier ( Evenement::onBtnM_roulerHaut       , fct_rouletteH );
    m_slider->lier ( Evenement::onBtnM_roulerBas        , fct_rouletteB );

    // Initialisation du slider
    m_slider->setPosition ( m_marge.x, m_marge.y );
    m_slider->setTaille ( { m_largeur - 2*m_marge.x  , m_largeur - 2*m_marge.y });

}

/////////////////////////////////////////////////
void DnGlissere::actualiserGeometrie (){

//    printf ("DnGlissere::actualiserGeometrie\n");
//    printf ("m_horizontal : %d\n" , m_horizontal );
    log ("m_largeur", m_largeur);

    if ( m_horizontal )
        m_taille = { m_longueur,  m_largeur };
     else
        m_taille = { m_largeur ,  m_longueur };

    m_fond->setTaille           ( m_taille );
    m_boutonFond->setTaille     ( { m_taille.x - 2*m_marge.x  , m_taille.y - 2*m_marge.y } );
    m_boutonFond->setPosition   ( m_marge.x , m_marge.y );

//    m_slider->setTaille         ( { m_largeur - 2*m_marge.x  , m_largeur - 2*m_marge.y });
    corrigerPositionSlider();

    demanderActuaBounds();

}

/////////////////////////////////////////////////
void DnGlissere::actualiserStyle ()
{
    log ("actualiserStyle");

    m_boutonFond->setFondCouleur        ( m_btnCouleurs ) ;
    m_boutonFond->setFondLigneCouleur   ( m_btnLgnCouleurs  ) ;
    m_boutonFond->setFondLigneEpaisseur ( m_btnLgnepaisseurs  );

    m_slider->setFondCouleur            ( m_slideCouleurs ) ;
    m_slider->setFondLigneCouleur       ( m_slideLgnCouleurs  ) ;
    m_slider->setFondLigneEpaisseur     ( m_slideLgnepaisseurs  );

    m_fond->setFondCouleur              ( m_fndCouleur ) ;
    m_fond->setFondLigneCouleur         ( m_fndLgnCouleur  ) ;
    m_fond->setFondLigneEpaisseur       ( m_fndLgnepaisseur  );

}


/////////////////////////////////////////////////
void DnGlissere::traiterEvenements (const sf::Event& evenement){
    if ( dragEnCours() ) deplacerSlider ();
}


/////////////////////////////////////////////////
void DnGlissere::incrementer( float inc ){
    sf::Vector2f posBack = m_slider->getPosition();

    if ( m_horizontal )
        m_slider->setPosition ( m_slider->getPosition ( ).x + inc , m_slider->getPosition ( ).y );
    else
        m_slider->setPosition ( m_slider->getPosition ( ).x  , m_slider->getPosition ( ).y + inc);
    corrigerPositionSlider();


    // si on a bouger au final on declenche des trucs
    if ( posBack != m_slider->getPosition() ){
        declencher ( Evenement::on_valeurChange );
        logEvt ( "declencher" , "on_valeurChange" );
    }
}



/////////////////////////////////////////////////
void DnGlissere::decrementer( float inc ){

    sf::Vector2f posBack = m_slider->getPosition();

    if ( m_horizontal )
        m_slider->setPosition ( m_slider->getPosition ( ).x - inc , m_slider->getPosition ( ).y );
    else
        m_slider->setPosition ( m_slider->getPosition ( ).x , m_slider->getPosition ( ).y - inc );
    corrigerPositionSlider();

    // si on a bouger au final on declenche des trucs
    if ( posBack != m_slider->getPosition() ){
        declencher ( Evenement::on_valeurChange );
        logEvt ( "declencher" , "on_valeurChange" );
    }
}



/////////////////////////////////////////////////
void DnGlissere::deplacerSlider (){

    sf::Vector2f posBack = m_slider->getPosition();

    // Definir la nouvelle position avec les coords souris
    if ( m_horizontal )
        m_slider->setPosition ( getLocalPosSouris().x - m_decalageDragSouris.x - m_marge.x , m_marge.y );
    else
        m_slider->setPosition (  m_marge.x , getLocalPosSouris().y - m_marge.y  - m_decalageDragSouris.y );

    corrigerPositionSlider();

    // si on a bouger au final on declenche des trucs
    if ( posBack != m_slider->getPosition() ) {
        declencher ( Evenement::on_valeurChange );

        logEvt ( "declencher" , "on_valeurChange" );

        m_slider->demanderActuaBounds();
    }
}



/////////////////////////////////////////////////
void DnGlissere::corrigerPositionSlider(){

    if ( m_horizontal ) {
        if ( m_slider->getPosition ( ).x < m_marge.x )
            m_slider->setPosition ( m_marge.x, m_marge.y );
        if ( m_slider->getPosition ( ).x > m_taille.x - m_marge.x - m_slider->getTaille().x )
            m_slider->setPosition ( m_taille.x - m_marge.x - m_slider->getTaille().x, m_marge.y );
    } else {
        if ( m_slider->getPosition ( ).y < m_marge.y )
            m_slider->setPosition ( m_marge.x , m_marge.y  );
        if ( m_slider->getPosition ( ).y > m_taille.y - m_marge.y - m_slider->getTaille().y )
            m_slider->setPosition ( m_marge.x,  m_taille.y - m_marge.y - m_slider->getTaille().y );
    }
}





/////////////////////////////////////////////////
float DnGlissere::getValeur(){
    float result, longueurMax,coefPosition, longueurVal;
    if ( m_horizontal ) {
        longueurMax = m_taille.x - 2*m_marge.x - m_slider->getTaille().x;
        coefPosition = ( m_slider->getPosition().x - m_marge.x ) / longueurMax;
        longueurVal = m_valeurMax - m_valeurMin;
        if (longueurMax == 0 )
            result = 0;
        else result =  coefPosition * longueurVal;
    } else {
        longueurMax = m_taille.y - 2*m_marge.y - m_slider->getTaille().y;
        coefPosition = ( m_slider->getPosition().y - m_marge.y ) / longueurMax;
        longueurVal = m_valeurMax - m_valeurMin;
        if (longueurMax == 0 )
            result = 100;
        else result =  m_valeurMax - coefPosition * longueurVal;
    }
    return result;
};

/////////////////////////////////////////////////
void DnGlissere::setValeurMax( float val ){
    m_valeurMax = val;
};

/////////////////////////////////////////////////
float DnGlissere::getValeurMax ( ) const {
    return m_valeurMax;
};

/////////////////////////////////////////////////
void DnGlissere::setValeurMin( float val ){
    m_valeurMin = val;
};

/////////////////////////////////////////////////
float DnGlissere::getValeurMin ( ) const {
    return m_valeurMin;
};


/////////////////////////////////////////////////
bool DnGlissere::dragEnCours( ) {
    return m_drag;
};

/////////////////////////////////////////////////
void DnGlissere::setDrag (bool val ){
    m_drag = val;
};

} // fin namespace gui

































