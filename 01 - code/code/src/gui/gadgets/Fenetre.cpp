/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/gadgets/Fenetre.h>
#include <appli/Config.h>

#include "gui/Gui.h"


namespace gui {

/////////////////////////////////////////////////
Fenetre::Glissiere::Glissiere ( Glissiere::Orientation orientation )
{

}





/////////////////////////////////////////////////
Fenetre::Fenetre ( )
: m_fermable            ( true )
, m_resizable           ( true )
, m_draggable           ( true )
, m_dragEnCours         ( false )
, m_dragPosOrigin       ( {0,0} )
, m_dragPosSourisOrigin ( {0,0} )
, m_shaderClip          ( )
, m_fond                ( )
, m_titre               ( )
, m_boutonFermer        ( )
, m_sliderH             ( Glissiere::Orientation::Horizontal  )
, m_sliderV             ( Glissiere::Orientation::Horizontal  )
, m_calque              ( std::make_shared<Calque>() )
{

    /// Initialisation du shader SANS le ressource manager !! ATTENTION a corriger !!
    if (! m_shaderClip.loadFromFile( "media/shaders/clippingMask.frag", sf::Shader::Fragment ) )
        std::cout << "PROBLEME CHARGEMENT SHADER\n";
    else    m_shaderClip.setParameter("texture", sf::Shader::CurrentTexture);

    m_marge = { 8,8 };

    /// Initialisation du titre SFML ////////////////////
    m_titre.setCharacterSize    ( 12 );
    m_titre.setColor            ( sf::Color (200,200,200) );
    m_titre.setStyle            ( sf::Text::Bold );
    m_titre.setFont             ( app::Config::ms_polices.get( app::Config::Polices::police_1 ) );

    /// Initialisation du fond SFML. ////////////////////
    m_fond.setFillColor        ( { 50, 70, 50 , 255 } );
    m_fond.setOutlineColor     ( { 150, 150, 150 } );
    m_fond.setOutlineThickness ( 1 );

    /// Initialisation du bouton fermeture. ////////////////////
    m_boutonFermer.setRemplissageCouleur    ( { 255, 255, 255 } );
    m_boutonFermer.setContourCouleur        ( { 150, 150, 150 } );
    m_boutonFermer.setContourEpaisseur      ( 0 );
    m_boutonFermer.setTexte                 ( "X" );
    m_boutonFermer.setParent                ( this );
    m_boutonFermer.setAlphaEtats            ( 0,50,100 );

    /// Initialisation du calque des enfants. ////////////////////
    Gadget::ajouterEnfant ( m_calque );




    /// les interactions ////////////////////
    // les fonctions
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

    // les liaisons
    lier ( Evenement::onBtnG_presser, fn_dragDebut );
    lier ( Evenement::onBtnG_relacher, fn_dragFin );
    lier ( Evenement::onBtnG_relacherDehors, fn_dragFin );
    m_boutonFermer.lier ( Evenement::onBtnG_relacher, fn_fermeture );



    actualiser();

}

/////////////////////////////////////////////////
void Fenetre::ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement ){

    // on l'ajoute normalement
    m_calque->ajouterEnfant( nouvelElement );


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
void Fenetre::actualiserClipping ()
{
    auto bounds = m_calque->getGlobalBounds();
    std::cout << "actualiserClipping : " << bounds.left << " , " << bounds.top << " , " << bounds.width << " , " << bounds.height << "\n";
    m_shaderClip.setParameter( "rectMasque" , bounds.left
                                            , bounds.top
                                            , bounds.width
                                            , bounds.height );
    m_shaderClip.setParameter( "aTexture" , true );
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
    m_boutonFermer.setSize      ( { hauteurTitre , hauteurTitre } );
    m_boutonFermer.setPosition  ( m_size.x - hauteurTitre - m_marge.x, m_marge.y );

    // on replace le calque enfants dans la fenetre
    m_calque->setPosition       ( m_marge.x, 2*m_marge.y + hauteurTitre );
    m_calque->setSize           ( { m_size.x - 2*m_marge.x , m_size.y - ( 2*m_marge.y + hauteurTitre ) } );

    // le shader
    actualiserClipping ();


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
    if ( m_boutonFermer.testerSurvol ( posSouris ) != nullptr )
        return m_boutonFermer.testerSurvol ( posSouris );

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
    if (! estVisible () ) return;

    //On applique la transformation
    states.transform *= getTransform();

    // On dessine le fond
    target.draw ( m_fond , states );

    // on dessine le bouton fermeture si besoin
    if ( m_fermable )
        target.draw ( m_boutonFermer , states );

    // On dessine le titre
    target.draw ( m_titre , states );

    // on dessine les enfants
    states.shader = &m_shaderClip;
    target.draw ( *m_calque , states );




}



} // fin namespace gui

