/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gadgets/outils/BtnMenu.h"
#include "gui.h"
#include "gadgets/outils/SupBandeauMenusDeroulants.h"



namespace gui {
std::shared_ptr<BtnMenu>        BtnMenu::ms_menuOuvert = nullptr;

/////////////////////////////////////////////////
BtnMenu::BtnMenu ()
: m_elements    ( 0 )
, m_tailleMenu  ( { 150 , 15 } )
, m_ecart       ( 0 )
{

    creerNomUnique ( "Menu");
    m_texte = "Menu";

    m_marge = { 0, 0 };

    // initialiser les composants herités
    CmpOmbre::initialiserComposants ( this );
    CmpFond::initialiserComposants ( this );

    // initialiser les params graphiques
    m_btnCouleurs.set   ( sf::Color( 0, 0, 0, 0 )  , Etat::desactive );
    m_btnCouleurs.set   ( sf::Color( 0,0,0, 0 )  , Etat::repos );
    m_btnCouleurs.set   ( sf::Color( 0,0,0, 120 ) , Etat::survol );
    m_btnCouleurs.set   ( sf::Color( 0,0,0, 150 ) , Etat::press );

    m_btnLignesCouleurs.set   ( sf::Color( 0, 0, 0, 0 )  , Etat::desactive );
    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0, 50 )  , Etat::repos );
    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0, 200 ) , Etat::survol );
    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0, 200 ) , Etat::press );

    m_btnLignesEpaisseurs   = 0;

    m_fondCouleur       = sf::Color( 255 , 255 , 255 );
    m_fondLgnCouleur     = sf::Color( 50 , 50 , 50);
    m_fondLgnEpaisseur         = 1;

    m_textCouleur           = sf::Color( 50 , 50 , 50 );

    m_textCouleur.set   ( sf::Color( 0, 0, 0, 0 )       , Etat::desactive );
    m_textCouleur.set   ( sf::Color( 0,0,0, 255 )       , Etat::repos );
    m_textCouleur.set   ( sf::Color( 255,255,255, 255 ) , Etat::survol );
    m_textCouleur.set   ( sf::Color( 255,255,255, 255 ) , Etat::press );

    m_textStyle             = sf::Text::Style::Regular;
    m_textTaille            = 10;
    m_textPolice            = Interface::ms_polices.get ( "Defaut" );

}


/////////////////////////////////////////////////
void BtnMenu::actualiserGeometrie()
{
    int decallage = m_marge.y ;
    for ( auto element : m_elements ) {
        element->bouton->setPosition    ( m_marge.x , decallage );
        element->bouton->setTexte       ( element->nom );
        decallage += element->bouton->getTaille().y + m_ecart;
    }

    m_taille.x = m_tailleMenu.x + 2 * m_marge.x;
    m_taille.y = decallage + m_marge.y;

    m_fond->setTaille( m_taille );
    m_ombre->setTaille( m_taille );

    demanderActuaBounds();

}

/////////////////////////////////////////////////
void BtnMenu::actualiserStyle()
{
    for ( auto element : m_elements ) {

        auto btn = element->bouton;

        btn->setFondCouleur         ( m_btnCouleurs );
        btn->setFondLigneCouleur    ( m_btnLignesCouleurs );
        btn->setFondLigneEpaisseur  ( m_btnLignesEpaisseurs );

        btn->setTexteTaille     ( m_textTaille );
        btn->setTexteCouleur    ( m_textCouleur );
        btn->setTextePolice     ( m_textPolice );
        btn->setTexteStyle      ( m_textStyle );
    }

    m_fond->setFondCouleur         ( m_fondCouleur.repos );
    m_fond->setFondLigneCouleur    ( m_fondLgnCouleur.repos );
    m_fond->setFondLigneEpaisseur  ( m_fondLgnEpaisseur.repos );

}

/////////////////////////////////////////////////
void BtnMenu::ajouterEspace (  )
{

    ElementMenu *    nouvelElement = new ElementAction ();

    std::shared_ptr<BtnTexte>     bouton = std::make_shared<BtnTexte>( );

    bouton->setMarge            ( { 5 , 2 } );
    bouton->setAutoAjuster      ( false );
    bouton->setParent           ( this );
    bouton->setActif(false);
    bouton->setTaille           ( { m_tailleMenu.x , m_tailleMenu.y/3 } );

    nouvelElement->bouton   = bouton;

    m_elements.push_back( nouvelElement );

    demanderActualisation ();
}



/////////////////////////////////////////////////
void BtnMenu::ajouterElement ( std::string nom, FctnAction fonction )
{
    log ("ajouter element" , nom);

    ElementMenu *    nouvelElement = new ElementAction ();

    nouvelElement->nom      = nom;
    nouvelElement->fonction = fonction;

    std::shared_ptr<BtnTexte>     bouton = std::make_shared<BtnTexte>( );

    bouton->setMarge            ( { 5 , 2 } );
    bouton->setTexte            ( nom );
    bouton->setAutoAjuster      ( false );
//    bouton->setParent           ( this );
    bouton->setTaille           ( m_tailleMenu );

    ajouterComposant ( bouton );


    auto fctInterne = [this, fonction](  ){

        fonction();
        SupBandeauMenusDeroulants::fermerMenu();
    };


    bouton->lier            ( Evenement::onBtnG_relacher , fctInterne );
    nouvelElement->bouton   = bouton;

    m_elements.push_back( nouvelElement );

    demanderActualisation ();

}


/////////////////////////////////////////////////
void BtnMenu::ajouterElementCoche ( std::string nom, FctnAction fonction, bool coche  )
{

    ElementMenu *    nouvelElement = new ElementCoche ();

    nouvelElement->nom      = nom;
    nouvelElement->fonction = fonction;

    std::shared_ptr<BtnTexte>     bouton = std::make_shared<BtnTexte>( );

    bouton->setMarge            ( { 5 , 2 } );
    bouton->setTexte            ( nom );
    bouton->setAutoAjuster      ( false );
    bouton->setParent           ( this );

    if ( nom == "" ){
        bouton->setActif(false);
        bouton->setTaille           ( { m_tailleMenu.x , m_tailleMenu.y/3 } );
    } else {
        bouton->setTaille           ( m_tailleMenu );
    }

    bouton->lier            ( Evenement::onBtnG_relacher , fonction );
    nouvelElement->bouton   = bouton;

    m_elements.push_back( nouvelElement );

    actualiser ();

}

/////////////////////////////////////////////////
void BtnMenu::supprimerElement (unsigned int id)
{

}


/*
/////////////////////////////////////////////////
std::shared_ptr<Gadget>  BtnMenu::testerSurvol ( sf::Vector2i position )
{
    if ( ! estVisible() )
        return false;

    if ( m_globalBounds.contains( position.x, position.y ) )
    {
        // Si on survol un bouton on le renvois
        for ( auto element : m_elements )
            if ( element->bouton->testerSurvol ( position ) != nullptr )            {
                std::shared_ptr<Gadget> result = element->bouton;
                return result;
            }

        // Sinon on renvois le menu ? ou rien ?
        return nullptr;
    }

    // Sinon on renvois null
    return nullptr;
}
*/

/////////////////////////////////////////////////
void BtnMenu::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    if ( ! estVisible() )
        return;

    //On applique la transformation
    states.transform *= getTransform();

    // l'ombre
    if ( m_ombreActive )
        target.draw ( *m_ombre , states ) ;

    // le fond
    target.draw ( *m_fond , states ) ;

    // les éléments
    for ( auto element : m_elements )
        target.draw ( *element->bouton , states ) ;
}


} // fin namespace gui

