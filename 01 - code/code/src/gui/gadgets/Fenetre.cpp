/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Fenetre.h>
#include <appli/Config.h>

#include "gui/Gui.h"


namespace gui {
/////////////////////////////////////////////////
// Glissiere
/////////////////////////////////////////////////

/////////////////////////////////////////////////
Fenetre::Glissiere::Glissiere ( Glissiere::Orientation orientation , Fenetre* fenetre )
: m_fenetre             ( fenetre )
, m_orientation         ( orientation )
, m_dragEnCours         ( false )
, m_dragPosOrigin       ( {0,0} )
, m_dragPosSourisOrigin ( {0,0} )
, m_btnFond             ( )
, m_btnGlissiere        ( )
, m_largeur             ( 7 )
{

    /// Initialisation bouton du fond ////////////////////
    m_btnFond.setRemplissageCouleur    ( { 255, 255, 255 } );
    m_btnFond.setContourCouleur        ( { 150, 150, 150 } );
    m_btnFond.setContourEpaisseur      ( 0 );
    m_btnFond.setParent                ( this );
    m_btnFond.setAlphaEtats            ( 0,20,30 );


    /// Initialisation bouton glissiere ////////////////////
    m_btnGlissiere.setRemplissageCouleur    ( { 255, 255, 255 } );
    m_btnGlissiere.setContourCouleur        ( { 150, 150, 150 } );
    m_btnGlissiere.setContourEpaisseur      ( 0 );
    m_btnGlissiere.setParent                ( this );
    m_btnGlissiere.setAlphaEtats            ( 100,150,200 );


    /// Interactions Fonctions ////////////////////
    auto fctDebutDrag = [this](){
        std::cout << "debut drag\n";
        m_dragEnCours = true;
        m_dragPosOrigin         = { m_btnGlissiere.getPosition ().x, m_btnGlissiere.getPosition ().y } ;
        m_dragPosSourisOrigin   = Gui::getSourisPosition ();
    };
    auto fctFinDrag = [this](){
        if ( m_dragEnCours ){
            std::cout << "fin drag\n";
            m_dragEnCours = false;
            m_dragPosOrigin         = { 0, 0 } ;
            m_dragPosSourisOrigin   = { 0, 0 } ;
        }
    };
    auto fctRouletteHaut = [this](){
            std::cout << "fctRouletteHaut\n";
    };
    auto fctRouletteBas = [this](){
            std::cout << "fctRouletteBas\n";
    };

    /// Interactions Laisons ////////////////////
    m_btnFond.lier      ( Evenement::onBtnM_roulerHaut      , fctRouletteHaut );
    m_btnFond.lier      ( Evenement::onBtnM_roulerBas       , fctRouletteBas );

    m_btnGlissiere.lier ( Evenement::onBtnG_presser         , fctDebutDrag );
    m_btnGlissiere.lier ( Evenement::onBtnG_relacher        , fctFinDrag );
    m_btnGlissiere.lier ( Evenement::onBtnG_relacherDehors  , fctFinDrag );
    m_btnGlissiere.lier ( Evenement::onBtnM_roulerHaut      , fctRouletteHaut );
    m_btnGlissiere.lier ( Evenement::onBtnM_roulerBas       , fctRouletteBas );

    actualiser();

}


/////////////////////////////////////////////////
void Fenetre::Glissiere::setLongueur ( int longueur ){
    switch ( m_orientation ){
        case Horizontal:
            m_size = { longueur, m_largeur };
            break;
        case Vertical:
            m_size = { m_largeur, longueur };
            break;
    }
    actualiser();
}


/////////////////////////////////////////////////
void Fenetre::Glissiere::setRapport ( float rapport )
{
    switch ( m_orientation ){
        case Horizontal:
            m_btnGlissiere.setSize( { rapport * m_size.x , m_largeur } );
            break;
        case Vertical:
            m_btnGlissiere.setSize( { m_largeur , m_size.y * rapport } );
            break;
    }
    actualiser();
}

/////////////////////////////////////////////////
void Fenetre::Glissiere::actualiser (){

    m_btnFond.setSize ( m_size );

    m_btnGlissiere.actualiser();

    Gadget::actualiser();

}

/////////////////////////////////////////////////
Gadget* Fenetre::Glissiere::testerSurvol (sf::Vector2i posSouris)
{

    // si non visible on renvois nullptr
    if (! estVisible () )
        return nullptr;

    // Si on survol pas la fenetre on sort direct
    if ( ! getGlobalBounds().contains( posSouris.x, posSouris.y ) )
        return nullptr;

    // Si on survol les glissieres
    if ( m_btnGlissiere.testerSurvol ( posSouris ) != nullptr )
        return m_btnGlissiere.testerSurvol ( posSouris );

    if ( m_btnFond.testerSurvol ( posSouris ) != nullptr )
        return m_btnFond.testerSurvol ( posSouris );


    // finalement on renvois nullptr mais normalement on devrait pas pouvoir arriver là
    return nullptr;

}


/////////////////////////////////////////////////
void Fenetre::Glissiere::traiterEvenements (sf::Event evenement)
{
    if ( m_dragEnCours ){

        auto posSouris = Gui::getSourisPosition ();

        switch ( m_orientation ){
            case Horizontal: {      // la destination du drag
                                    float destH = m_dragPosOrigin.x + posSouris.x - m_dragPosSourisOrigin.x;

                                    // limitation du drag
                                    if ( destH < 0 ) destH = 0;
                                    if ( destH > m_size.x - m_btnGlissiere.getSize().x ) destH = m_size.x - m_btnGlissiere.getSize().x;

                                    // placement de la glisserre
                                    m_btnGlissiere.setPosition  ( destH ,  m_btnGlissiere.getPosition().y );

                                    // placement du calque de la fenêtre parent
                                    m_fenetre->defilerHorizontal( destH / ( m_size.x - m_btnGlissiere.getSize().x ) );
                break;
            }
            case Vertical: {        // la destination du drag
                                    float destV = m_dragPosOrigin.y + posSouris.y - m_dragPosSourisOrigin.y;

                                    // limitation du drag
                                    if ( destV <0 ) destV = 0;
                                    if ( destV > m_size.y - m_btnGlissiere.getSize().y ) destV = m_size.y - m_btnGlissiere.getSize().y;

                                    // placement de la glisserre
                                    m_btnGlissiere.setPosition  (  m_btnGlissiere.getPosition().x , destV);

                                    // placement du calque de la fenêtre parent
                                    m_fenetre->defilerVertical( destV / ( m_size.y - m_btnGlissiere.getSize().y ) );
                break;
            }
        } // fin switch
    }

}



/////////////////////////////////////////////////
void Fenetre::Glissiere::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    // si non visible on sort
    if (! estVisible () ) return;

    // On applique la transformation
    states.transform *= getTransform();

//    // On dessine le fond
//    target.draw ( m_btnFond , states );

    // on dessine la glissiere
    target.draw ( m_btnGlissiere , states );


}










/////////////////////////////////////////////////
// Redimensionnement
/////////////////////////////////////////////////

/////////////////////////////////////////////////
Fenetre::Redimensionnement::Redimensionnement ( Fenetre* fenetre )
: m_fenetre                 ( fenetre )
, m_largeur                 ( 5 )
, m_redimTailleOrigin       ( { 0,0} )
, m_redimPosOrigin          ( { 0,0} )
, m_redimPosSourisOrigin    ( { 0,0} )
, m_redimH                  ( false )
, m_redimB                  ( false )
, m_redimG                  ( false )
, m_redimD                  ( false )
{
    /// on remplie la liste des boutons
    m_boutons.push_back( &m_btn_H );
    m_boutons.push_back( &m_btn_D );
    m_boutons.push_back( &m_btn_G );
    m_boutons.push_back( &m_btn_B );
    m_boutons.push_back( &m_btn_HG );
    m_boutons.push_back( &m_btn_HD );
    m_boutons.push_back( &m_btn_BG );
    m_boutons.push_back( &m_btn_BD );

    /// on initialise les boutons
    for ( auto bouton : m_boutons) {
        bouton->setParent               ( m_fenetre );
        bouton->setRemplissageCouleur   ( sf::Color::White );
        bouton->setContourCouleur       ( sf::Color::Transparent );
        bouton->setContourEpaisseur     ( 0 );
        bouton->setAlphaEtats           ( 0, 50 , 100 );
    }

    /// les interactions

    auto fctInitRedim   = [this](){
        m_redimPosOrigin        = { m_fenetre->getPosition().x  , m_fenetre->getPosition().y };
        m_redimTailleOrigin     = { m_fenetre->getSize().x      , m_fenetre->getSize().y };
        m_redimPosSourisOrigin  = Gui::getSourisPosition();
    };
    auto fctRedimFin    = [ this](){
        m_redimH = false;
        m_redimB = false;
        m_redimG = false;
        m_redimD = false;
    };


    auto fctRedimHaut   = [this, fctInitRedim](){
        fctInitRedim ();
        m_redimH = true;
    };
    auto fctRedimBas    = [this, fctInitRedim](){
        fctInitRedim ();
        m_redimB = true;
    };
    auto fctRedimGauche = [this, fctInitRedim](){
        fctInitRedim ();
        m_redimG = true;
    };
    auto fctRedimDroite = [this, fctInitRedim](){
        fctInitRedim ();
        m_redimD = true;
    };
    auto fctRedimHautGauche = [ this, fctInitRedim ](){
        fctInitRedim ();
        m_redimH = true;
        m_redimG = true;
    };
    auto fctRedimHautDroite = [ this, fctInitRedim ](){
        fctInitRedim ();
        m_redimH = true;
        m_redimD = true;
    };
    auto fctRedimBasGauche  = [ this, fctInitRedim ](){
        fctInitRedim ();
        m_redimB = true;
        m_redimG = true;
    };
    auto fctRedimBasDroite  = [ this, fctInitRedim ](){
        fctInitRedim ();
        m_redimB = true;
        m_redimD = true;
    };

    /// les liaisons
    m_btn_HG.lier ( Evenement::onBtnG_presser           , fctRedimHautGauche );
    m_btn_HG.lier ( Evenement::onBtnG_relacher          , fctRedimFin );
    m_btn_HG.lier ( Evenement::onBtnG_relacherDehors    , fctRedimFin );
    m_btn_H.lier  ( Evenement::onBtnG_presser           , fctRedimHaut );
    m_btn_H.lier  ( Evenement::onBtnG_relacher          , fctRedimFin );
    m_btn_H.lier  ( Evenement::onBtnG_relacherDehors    , fctRedimFin );
    m_btn_HD.lier ( Evenement::onBtnG_presser           , fctRedimHautDroite );
    m_btn_HD.lier ( Evenement::onBtnG_relacher          , fctRedimFin );
    m_btn_HD.lier ( Evenement::onBtnG_relacherDehors    , fctRedimFin );
    m_btn_D.lier  ( Evenement::onBtnG_presser           , fctRedimDroite );
    m_btn_D.lier  ( Evenement::onBtnG_relacher          , fctRedimFin );
    m_btn_D.lier  ( Evenement::onBtnG_relacherDehors    , fctRedimFin );
    m_btn_G.lier  ( Evenement::onBtnG_presser           , fctRedimGauche );
    m_btn_G.lier  ( Evenement::onBtnG_relacher          , fctRedimFin );
    m_btn_G.lier  ( Evenement::onBtnG_relacherDehors    , fctRedimFin );
    m_btn_BG.lier ( Evenement::onBtnG_presser           , fctRedimBasGauche );
    m_btn_BG.lier ( Evenement::onBtnG_relacher          , fctRedimFin );
    m_btn_BG.lier ( Evenement::onBtnG_relacherDehors    , fctRedimFin );
    m_btn_B.lier  ( Evenement::onBtnG_presser           , fctRedimBas );
    m_btn_B.lier  ( Evenement::onBtnG_relacher          , fctRedimFin );
    m_btn_B.lier  ( Evenement::onBtnG_relacherDehors    , fctRedimFin );
    m_btn_BD.lier ( Evenement::onBtnG_presser           , fctRedimBasDroite);
    m_btn_BD.lier ( Evenement::onBtnG_relacher          , fctRedimFin );
    m_btn_BD.lier ( Evenement::onBtnG_relacherDehors    , fctRedimFin );

}










/////////////////////////////////////////////////
Gadget* Fenetre::Redimensionnement::testerSurvol (sf::Vector2i posSouris)
{

    /// si non visible on renvois nullptr
    if (! estVisible () )
        return nullptr;

    /// on test chaque bouton
    for (  int i =  m_boutons.size()-1 ; i>=0 ; i--){
        auto bouton = m_boutons[i];
        if ( bouton->testerSurvol ( posSouris ) != nullptr )
            return bouton->testerSurvol ( posSouris );
    }

    /// sinon on renvois null
    return nullptr;
}




/////////////////////////////////////////////////
void Fenetre::Redimensionnement::traiterEvenements (sf::Event evenement)
{
    /// si caché on zappe
    if ( ! estVisible() ) return;

    /// Redimensionner la fenetre ///////////////
    if ( m_redimB )    {
        int nouvelleTailleY = m_redimTailleOrigin.y + Gui::getSourisPosition ().y - m_redimPosSourisOrigin.y;
        if ( nouvelleTailleY < m_fenetre->getTailleMin ().y )
            nouvelleTailleY = m_fenetre->getTailleMin ().y;
        m_fenetre->setSize  ( m_fenetre->getSize ().x , nouvelleTailleY );
    }
    if ( m_redimD )    {
        int nouvelleTailleX = m_redimTailleOrigin.x + Gui::getSourisPosition ().x - m_redimPosSourisOrigin.x;
        if ( nouvelleTailleX < m_fenetre->getTailleMin ().x )
            nouvelleTailleX = m_fenetre->getTailleMin ().x;
        m_fenetre->setSize  ( nouvelleTailleX ,m_fenetre->getSize ().y );
    }
    if ( m_redimH )    {
        int nouvelleTailleY = m_redimTailleOrigin.y - (  Gui::getSourisPosition ().y - m_redimPosSourisOrigin.y );
        if ( nouvelleTailleY < m_fenetre->getTailleMin ().y )
            nouvelleTailleY = m_fenetre->getTailleMin ().y;
        m_fenetre->setSize      ( m_fenetre->getSize ().x , nouvelleTailleY );
        m_fenetre->setPosition  ( (int)(m_fenetre->getPosition().x) , m_redimPosOrigin.y + (  m_redimTailleOrigin.y - nouvelleTailleY ) );
    }
    if ( m_redimG )    {
        int nouvelleTailleX = m_redimTailleOrigin.x - ( Gui::getSourisPosition ().x - m_redimPosSourisOrigin.x );
        if ( nouvelleTailleX < m_fenetre->getTailleMin ().x )
            nouvelleTailleX = m_fenetre->getTailleMin ().x;
        m_fenetre->setSize  ( nouvelleTailleX ,m_fenetre->getSize ().y );
        m_fenetre->setPosition  ( m_redimPosOrigin.x + (  m_redimTailleOrigin.x - nouvelleTailleX )  , (int)(m_fenetre->getPosition().y ) );
    }

}






/////////////////////////////////////////////////
void Fenetre::Redimensionnement::actualiser ()
{

    m_btn_HG.setSize        ( m_largeur , m_largeur );
    m_btn_H.setSize         ( m_size.x , m_largeur );
    m_btn_H.setPosition     ( 0, 0 );
    m_btn_HD.setSize        ( m_largeur, m_largeur );
    m_btn_HD.setPosition    ( m_size.x - m_largeur, 0 );

    m_btn_G.setSize         ( m_largeur, m_size.y  );
    m_btn_G.setPosition     ( 0 , 0 );
    m_btn_D.setSize         ( m_largeur, m_size.y  );
    m_btn_D.setPosition     ( m_size.x - m_largeur , 0 );

    m_btn_BG.setSize        ( m_largeur, m_largeur );
    m_btn_BG.setPosition    ( 0, m_size.y - m_largeur );
    m_btn_B.setSize         ( m_size.x , m_largeur );
    m_btn_B.setPosition     ( 0, m_size.y - m_largeur );
    m_btn_BD.setSize        ( m_largeur, m_largeur );
    m_btn_BD.setPosition    ( m_size.x - m_largeur, m_size.y - m_largeur );
}


/////////////////////////////////////////////////
void Fenetre::Redimensionnement::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    /// si non visible on sort
    if ( ! estVisible () ) return;

//    ///On applique la transformation
//    states.transform *= getTransform();

    /// On dessine le fond
    for ( auto bouton : m_boutons )
        target.draw ( *bouton , states );
}














/////////////////////////////////////////////////
// Fenetre
/////////////////////////////////////////////////

/////////////////////////////////////////////////
Fenetre::Fenetre ( )
: m_fermable            ( true )
, m_resizable           ( true )
, m_draggable           ( true )
, m_dragEnCours         ( false )
, m_dragPosOrigin       ( {0,0} )
, m_dragPosSourisOrigin ( {0,0} )
, m_tailleMin           ( {0,0} )
, m_fond                ( )
, m_titre               ( )
, m_btnFermer           ( )
, m_btnSliderH          ( Glissiere::Orientation::Horizontal, this )
, m_btnSliderV          ( Glissiere::Orientation::Vertical, this )
, m_redim               ( this )
, m_contenant           ( std::make_shared<Calque>() )
, m_contenu             ( std::make_shared<Calque>() )
{

    /// la marge pour les fenetres ////////////////////
    m_marge = { 5,5 };


    /// Initialisation du titre SFML ////////////////////
    m_titre.setCharacterSize    ( 20 );
    m_titre.setColor            ( sf::Color ( 200, 200, 200 ) );
    m_titre.setStyle            ( sf::Text::Bold );
    m_titre.setFont             ( app::Config::ms_polices.get( app::Config::Polices::police_2 ) );


    /// Initialisation du fond SFML. ////////////////////
    m_fond.setFillColor         ( { 50, 70, 50  } );
    m_fond.setOutlineColor      ( { 150, 150, 150 } );
    m_fond.setOutlineThickness  ( 1 );


    /// Initialisation du bouton fermeture. ////////////////////
    m_btnFermer.setRemplissageCouleur    ( { 255, 255, 255 } );
    m_btnFermer.setContourCouleur        ( { 150, 150, 150 } );
    m_btnFermer.setContourEpaisseur      ( 0 );
    m_btnFermer.setTexte                 ( "X" );
    m_btnFermer.setParent                ( this );
    m_btnFermer.setAlphaEtats            ( 0,50,100 );
    m_btnFermer.setVisible               ( m_fermable );


    /// Initialisation du calque des enfants. ////////////////////
    Gadget::ajouterEnfant ( m_contenant );
    m_contenant->ajouterEnfant ( m_contenu );

    /// Initialisation des glissières et redim. ////////////////////
    m_btnSliderH.setParent ( this );
    m_btnSliderV.setParent ( this );
    m_redim.setLargeur( m_marge.x );

    /// Initialisation des  interactions ////////////////////
    auto fn_fermeture = [this](){
        declencher ( Evenement::onFen_fermer );
    };
    auto fn_dragDebut = [this](){
        m_dragEnCours           = true;
        m_dragPosOrigin         = { getPosition ().x, getPosition ().y } ;
        m_dragPosSourisOrigin   = Gui::getSourisPosition ();
    };
    auto fn_dragFin = [this](){
        if ( m_dragEnCours ) {
            m_dragEnCours = false;
            m_dragPosOrigin         = { 0,0 } ;
            m_dragPosSourisOrigin   = { 0,0 } ;
        }
    };

    lier ( Evenement::onBtnG_presser, fn_dragDebut );
    lier ( Evenement::onBtnG_relacher, fn_dragFin );
    lier ( Evenement::onBtnG_relacherDehors, fn_dragFin );

    m_btnFermer.lier ( Evenement::onBtnG_relacher, fn_fermeture );

    /// Une tite atualisation ////////////////////
    actualiser();

}


/////////////////////////////////////////////////
void Fenetre::ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement ){

    /// on l'ajoute dans le calque
    m_contenu->ajouterEnfant( nouvelElement );

    actualiser();

}


/////////////////////////////////////////////////
void Fenetre::defilerHorizontal ( float rapport )
{
    int dest = rapport * ( m_contenant->getSize().x - m_contenu->getEnfantsLocalBounds().width );
    m_contenu->setPosition ( dest , int( m_contenu->getPosition().y) );
}


/////////////////////////////////////////////////
void Fenetre::defilerVertical ( float rapport )
{
    int dest = rapport * ( m_contenant->getSize().y - m_contenu->getEnfantsLocalBounds().height );
    m_contenu->setPosition ( int( m_contenu->getPosition().x ) , dest );
}

//
///////////////////////////////////////////////////
//void Fenetre::redimensionnerGauche ( float taille )
//{
//
//        std::cout << "redim gauche\n";
//}
//
//
///////////////////////////////////////////////////
//void Fenetre::redimensionnerDroite ( float taille )
//{
//        std::cout << "redim droite\n";
//
//}
//
//
///////////////////////////////////////////////////
//void Fenetre::redimensionnerHaut ( float taille )
//{
//
//        std::cout << "redim haut\n";
//}
//
//
///////////////////////////////////////////////////
//void Fenetre::redimensionnerBas ( float taille )
//{
//        std::cout << "redim bas\n";
//
//}



/////////////////////////////////////////////////
void Fenetre::actualiser ()
{
    /// les bounds
    Gadget::actualiser();

    /// les éléments graphiques
    auto hauteurTitre = m_titre.getLocalBounds().height;
    m_fond.setSize              ( { m_size.x, m_size.y } );
    m_titre.setPosition         ( m_marge.x , m_marge.y  - hauteurTitre/2 );
    m_btnFermer.setSize         ( { hauteurTitre + m_marge.x , hauteurTitre + m_marge.x } );
    m_btnFermer.setPosition     ( m_size.x - m_btnFermer.getSize().x - m_marge.x, m_marge.y );

    /// on place le calque contenant dans la fenetre
    m_contenant->setSize           ( { m_size.x - 2*m_marge.x - m_btnSliderV.getLargeur (), m_size.y - ( 3*m_marge.y + hauteurTitre ) - m_btnSliderH.getLargeur () } );
    m_contenant->setPosition       ( m_marge.x, 2*m_marge.y + hauteurTitre );

    /// le contenu
    auto boundsEnfants = m_contenu->getEnfantsLocalBounds () ;
    m_contenu->setSize ( { boundsEnfants.width, boundsEnfants.height } );

    /// les glissières si besoin
    m_btnSliderH.setVisible ( boundsEnfants.width  > m_contenant->getSize().x );
    m_btnSliderV.setVisible ( boundsEnfants.height > m_contenant->getSize().y );
    if ( m_btnSliderH.estVisible() ) {
        m_btnSliderH.setPosition  ( m_contenant->getPosition().x
                                  , m_contenant->getPosition().y + m_contenant->getSize().y   );
        m_btnSliderH.setLongueur ( m_contenant->getSize().x );

        m_btnSliderH.setRapport (  (float)(m_contenant->getSize().x ) /  (float)(boundsEnfants.width ));
    }
    if ( m_btnSliderV.estVisible() ) {
        m_btnSliderV.setPosition   ( m_contenant->getPosition().x + m_contenant->getSize().x
                                   , m_contenant->getPosition().y);
        m_btnSliderV.setLongueur ( m_contenant->getSize().y );
        m_btnSliderV.setRapport ( (float)(m_contenant->getSize().y) /  (float)(boundsEnfants.height ));
    }

    /// Le redimensionnement
    m_redim.setSize ( m_size );
    m_tailleMin =   { m_marge.x *3 + m_titre.getLocalBounds().width  + m_btnFermer.getSize().x
                    , m_marge.y *3 + m_titre.getLocalBounds().height + m_btnSliderH.getSize().y };

    /// actualiser les limites du shader de clipping
    actualiserClipping ( m_contenant->getGlobalBounds () );

}


/////////////////////////////////////////////////
void Fenetre::traiterEvenements (sf::Event evenement)
{
    /// si caché on zappe
    if ( ! estVisible() ) return;

    /// Drag de la fenetre ///////////////
    if ( m_dragEnCours )
    {
        auto posSouris = Gui::getSourisPosition ();
        setPosition ( m_dragPosOrigin + posSouris - m_dragPosSourisOrigin );
    }

    /// Les sliders, pour le drag aussi ///////////////
    m_btnSliderH.traiterEvenements( evenement );
    m_btnSliderV.traiterEvenements( evenement );

    /// le redimensionnement
    m_redim.traiterEvenements( evenement );

}


/////////////////////////////////////////////////
Gadget* Fenetre::testerSurvol (sf::Vector2i posSouris)
{

    /// si non visible on renvois nullptr
    if (! estVisible () )
        return nullptr;

    /// Si on survol pas la fenetre on sort direct
    if ( ! getGlobalBounds().contains( posSouris.x, posSouris.y ) )
        return nullptr;

    /// Si on survol le bouton fermeture
    if ( m_btnFermer.testerSurvol ( posSouris ) != nullptr )
        return m_btnFermer.testerSurvol ( posSouris );

    /// Si on survol les glissieres
    if ( m_btnSliderH.testerSurvol ( posSouris ) != nullptr )
        return m_btnSliderH.testerSurvol ( posSouris );
    if ( m_btnSliderV.testerSurvol ( posSouris ) != nullptr )
        return m_btnSliderV.testerSurvol ( posSouris );

    /// Si on survol les redims
    if ( m_redim.testerSurvol ( posSouris ) != nullptr )
        return m_redim.testerSurvol ( posSouris );



    /// on test les enfants
    if ( m_contenu->testerSurvol ( posSouris ) != nullptr )
        return m_contenu->testerSurvol ( posSouris );


    /// finalement on renvois la fenetre (pour le drag)
    return this;

}

/////////////////////////////////////////////////
void Fenetre::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    /// si non visible on sort
    if ( ! estVisible () ) return;

    ///On applique la transformation
    states.transform *= getTransform();

    /// On dessine le fond
    target.draw ( m_fond , states );

    /// on dessine le bouton fermeture si besoin
    if ( m_fermable ) target.draw ( m_btnFermer , states );

    /// on dessine les glissieres
    target.draw ( m_btnSliderH , states );
    target.draw ( m_btnSliderV , states );
    target.draw ( m_redim , states );


    /// On dessine le titre
    target.draw ( m_titre , states );

    /// on dessine les enfants
    target.draw ( *m_contenant , states );


}



} // fin namespace gui

