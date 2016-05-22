/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Fenetre.h>
#include <appli/Config.h>

#include "gui/Gui.h"


namespace gui {

/////////////////////////////////////////////////
Fenetre::Glissiere::Glissiere ( Glissiere::Orientation orientation )
: m_orientation     ( orientation )
, m_btnFond         ( )
, m_btnGlissiere    ( )
, m_largeur         ( 7 )
{
    m_btnFond.setRemplissageCouleur    ( { 255, 255, 255 } );
    m_btnFond.setContourCouleur        ( { 150, 150, 150 } );
    m_btnFond.setContourEpaisseur      ( 0 );
    m_btnFond.setParent                ( this );
    m_btnFond.setAlphaEtats            ( 50,75,100 );

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
void Fenetre::Glissiere::setLargeur ( int largeur )
{
    m_largeur = largeur;
}


/////////////////////////////////////////////////
int Fenetre::Glissiere::getLargeur ( )
{
    return m_largeur;
}


/////////////////////////////////////////////////
void Fenetre::Glissiere::actualiser (){

    m_btnFond.setSize ( m_size );

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
    if ( m_btnFond.testerSurvol ( posSouris ) != nullptr )
        return m_btnFond.testerSurvol ( posSouris );

    if ( m_btnGlissiere.testerSurvol ( posSouris ) != nullptr )
        return m_btnGlissiere.testerSurvol ( posSouris );




    // finalement on renvois la fenetre (pour le drag par exemple)
    return this;

}

/////////////////////////////////////////////////
void Fenetre::Glissiere::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    // si non visible on sort
    if (! estVisible () ) return;

    // On applique la transformation
    states.transform *= getTransform();

    // On dessine le fond
    target.draw ( m_btnFond , states );

    // on dessine la glissiere
    target.draw ( m_btnGlissiere , states );


}






















/////////////////////////////////////////////////
Fenetre::Fenetre ( )
: m_fermable            ( true )
, m_resizable           ( true )
, m_draggable           ( true )
, m_dragEnCours         ( false )
, m_dragPosOrigin       ( {0,0} )
, m_dragPosSourisOrigin ( {0,0} )
, m_fond                ( )
, m_titre               ( )
, m_btnFermer           ( )
, m_btnSliderH          ( Glissiere::Orientation::Horizontal )
, m_btnSliderV          ( Glissiere::Orientation::Vertical )
, m_calque              ( std::make_shared<Calque>() )
{

    /// la marge pour les fenetres ////////////////////
    m_marge = { 8,8 };


    /// Initialisation du titre SFML ////////////////////
    m_titre.setCharacterSize    ( 12 );
    m_titre.setColor            ( sf::Color (200,200,200) );
    m_titre.setStyle            ( sf::Text::Bold );
    m_titre.setFont             ( app::Config::ms_polices.get( app::Config::Polices::police_1 ) );


    /// Initialisation du fond SFML. ////////////////////
    m_fond.setFillColor        ( { 50, 70, 50  } );
    m_fond.setOutlineColor     ( { 150, 150, 150 } );
    m_fond.setOutlineThickness ( 1 );


    /// Initialisation du bouton fermeture. ////////////////////
    m_btnFermer.setRemplissageCouleur    ( { 255, 255, 255 } );
    m_btnFermer.setContourCouleur        ( { 150, 150, 150 } );
    m_btnFermer.setContourEpaisseur      ( 0 );
    m_btnFermer.setTexte                 ( "X" );
    m_btnFermer.setParent                ( this );
    m_btnFermer.setAlphaEtats            ( 0,50,100 );
    m_btnFermer.setVisible               ( m_fermable );


    /// Initialisation du calque des enfants. ////////////////////
    Gadget::ajouterEnfant ( m_calque );


    /// Initialisation des glissières. ////////////////////
    m_btnSliderH.setParent ( this );
    m_btnSliderV.setParent ( this );


    /// Initialisation des  interactions ////////////////////
    auto fn_fermeture = [this](){
        std::cout <<"Fermer la fenetre\n";
    };
    auto fn_dragDebut = [this](){
        std::cout <<"Debut du drag\n";
        m_dragEnCours           = true;
        m_dragPosOrigin         = { getPosition ().x, getPosition ().y } ;
        m_dragPosSourisOrigin   = Gui::getSourisPosition ();
    };
    auto fn_dragFin = [this](){
        std::cout <<"Fin du drag\n";
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

    // on l'ajoute normalement
    m_calque->ajouterEnfant( nouvelElement );

    actualiser();

}

/////////////////////////////////////////////////
void Fenetre::setTitre (std::string titre)
{
    m_titre.setString ( titre );
}


/////////////////////////////////////////////////
void Fenetre::setTitreCouleur (sf::Color couleur)
{
    m_titre.setColor ( couleur );
}


/////////////////////////////////////////////////
void Fenetre::setTitreTaille (float taille)
{
    m_titre.setCharacterSize( taille );
    actualiser();
}


/////////////////////////////////////////////////
void Fenetre::setTitreStyle (sf::Text::Style style)
{
    m_titre.setStyle( style );
    actualiser();
}


/////////////////////////////////////////////////
void Fenetre::setTitrePolice (sf::Font& police)
{
    m_titre.setFont( police );
    actualiser();
}


/////////////////////////////////////////////////
void Fenetre::setFondTexture (sf::Texture& texture)
{
    m_fond.setTexture( &texture );
}


/////////////////////////////////////////////////
void Fenetre::setFondCouleur (sf::Color couleur)
{
    m_fond.setFillColor( couleur );
}


/////////////////////////////////////////////////
void Fenetre::setContourCouleur (sf::Color couleur)
{
    m_fond.setOutlineColor( couleur );
}


/////////////////////////////////////////////////
void Fenetre::setContourEpaisseur (float epaisseur)
{
    m_fond.setOutlineThickness( epaisseur );
}








/////////////////////////////////////////////////
void Fenetre::actualiser ()
{
    // les bounds
    Gadget::actualiser();

    // les éléments graphiques
    auto hauteurTitre = m_titre.getLocalBounds().height;
    m_fond.setSize              ( { m_size.x, m_size.y } );
    m_titre.setPosition         ( m_marge.x , m_marge.y  - hauteurTitre/3 );
    m_btnFermer.setSize         ( { hauteurTitre , hauteurTitre } );
    m_btnFermer.setPosition     ( m_size.x - hauteurTitre - m_marge.x, m_marge.y );

    // on replace le calque enfants dans la fenetre
    m_calque->setSize           ( { m_size.x - 2*m_marge.x - m_btnSliderV.getLargeur (), m_size.y - ( 3*m_marge.y + hauteurTitre ) - m_btnSliderH.getLargeur () } );
    m_calque->setPosition       ( m_marge.x, 2*m_marge.y + hauteurTitre );

    // les glissières si besoin
    auto boundsEnfants = m_calque->getEnfantsLocalBounds () ;
    m_btnSliderH.setVisible ( boundsEnfants.width  > m_calque->getSize().x );
    m_btnSliderV.setVisible ( boundsEnfants.height > m_calque->getSize().y );
    if ( m_btnSliderH.estVisible() ) {
        m_btnSliderH.setPosition  ( m_calque->getPosition().x
                                  , m_calque->getPosition().y + m_calque->getSize().y   );
        m_btnSliderH.setLongueur ( m_calque->getSize().x );
    }
    if ( m_btnSliderV.estVisible() ) {
        m_btnSliderV.setPosition   ( m_calque->getPosition().x + m_calque->getSize().x
                                   , m_calque->getPosition().y);
        m_btnSliderV.setLongueur ( m_calque->getSize().y );
    }



    // actualiser les bounds du shader
    actualiserClipping ( m_calque->getGlobalBounds () );


}


/////////////////////////////////////////////////
void Fenetre::traiterEvenements (sf::Event evenement)
{
    if ( ! estVisible() )
        return;

    /// gestion du drag /////
    if ( m_dragEnCours )
    {
        auto posSouris = Gui::getSourisPosition ();
        setPosition ( m_dragPosOrigin + posSouris - m_dragPosSourisOrigin );
    }


}


/////////////////////////////////////////////////
Gadget* Fenetre::testerSurvol (sf::Vector2i posSouris)
{

    // si non visible on renvois nullptr
    if (! estVisible () )
        return nullptr;

    // Si on survol pas la fenetre on sort direct
    if ( ! getGlobalBounds().contains( posSouris.x, posSouris.y ) )
        return nullptr;

    // Si on survol le bouton fermeture
    if ( m_btnFermer.testerSurvol ( posSouris ) != nullptr )
        return m_btnFermer.testerSurvol ( posSouris );

    // Si on survol les glissieres
    if ( m_btnSliderH.testerSurvol ( posSouris ) != nullptr )
        return m_btnSliderH.testerSurvol ( posSouris );
    if ( m_btnSliderV.testerSurvol ( posSouris ) != nullptr )
        return m_btnSliderV.testerSurvol ( posSouris );


    // on test les enfants
    if ( m_calque->testerSurvol ( posSouris ) != nullptr )
        return m_calque->testerSurvol ( posSouris );


    // finalement on renvois la fenetre (pour le drag par exemple)
    return this;

}

/////////////////////////////////////////////////
void Fenetre::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    // si non visible on sort
    if ( ! estVisible () ) return;

    //On applique la transformation
    states.transform *= getTransform();

    // On dessine le fond
    target.draw ( m_fond , states );

    // on dessine le bouton fermeture si besoin
    if ( m_fermable ) target.draw ( m_btnFermer , states );

    // on dessine les glissieres
    target.draw ( m_btnSliderH , states );
    target.draw ( m_btnSliderV , states );

    // On dessine le titre
    target.draw ( m_titre , states );

    // on dessine les enfants
    target.draw ( *m_calque , states );


}



} // fin namespace gui

