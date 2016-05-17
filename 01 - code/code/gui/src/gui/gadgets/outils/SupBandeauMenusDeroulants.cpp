/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/outils/SupBandeauMenusDeroulants.h>
#include <gadgets/outils/BtnMenu.h>
#include <gui.h>


namespace gui {
std::string             SupBandeauMenusDeroulants::ms_menuBack = "";
bool                    SupBandeauMenusDeroulants::ms_menuActif = false;
bool                    SupBandeauMenusDeroulants::ms_init = false;


/////////////////////////////////////////////////
SupBandeauMenusDeroulants::SupBandeauMenusDeroulants ()
{
    m_marge = { 3 , 2 };
    m_taille = { 150 , 20 };
    creerNomUnique ( "BandeauMenu");

}

void SupBandeauMenusDeroulants::fermerMenu()
{

    if ( BtnMenu::ms_menuOuvert != nullptr )
        BtnMenu::ms_menuOuvert->setVisible( false );

    ms_menuActif = false;
}



std::shared_ptr<BtnMenu> SupBandeauMenusDeroulants::ajouterMenu ( std::string nom )
{

    ElementMenu *    nouvelElement = new ElementMenu ();

    nouvelElement->nom      = nom;

    std::shared_ptr<BtnTexte>     bouton = std::make_shared<BtnTexte>( );

    bouton->setMarge            ( { 5 , 5 } );
    bouton->setTexte            ( nom );
    bouton->setAutoAjuster      ( false );
    bouton->setAutoAjuster      ( true );
    bouton->setFondCouleur      ( sf::Color::Transparent);
    bouton->setFondCouleur      ( sf::Color( 255,255,255,50) , Etat::survol);
    bouton->setTexteTaille      ( 10 );

    nouvelElement->menu = std::make_shared<BtnMenu>( );
    nouvelElement->menu->setVisible(false);
    nouvelElement->menu->setOmbreActive ( true );

//    Interface::ms_calque_menuDeroulants->ajouter ( nouvelElement->menu ) ;

    ajouter (bouton);

    bouton->lier                ( Evenement::onBtnG_presser , [this, nouvelElement](){
        if ( ms_menuActif )
        {
            fermerMenu();
        } else {
            if ( nouvelElement->menu->ms_menuOuvert != nullptr )
                nouvelElement->menu->ms_menuOuvert->setVisible( false );

            nouvelElement->menu->setVisible(true);
            nouvelElement->menu->ms_menuOuvert = nouvelElement->menu;
            nouvelElement->menu->setPosition ( nouvelElement->bouton->getPosAbs().x
                                             , nouvelElement->bouton->getPosAbs().y + nouvelElement->bouton->getTaille().y
                                             );

            ms_menuActif = true;
            ms_init = true;
        }
    } );



    bouton->lier                ( Evenement::on_entrer , [nouvelElement](){

        if ( ! ms_menuActif ) return;

        if ( nouvelElement->menu->ms_menuOuvert != nullptr )
            nouvelElement->menu->ms_menuOuvert->setVisible( false );
        nouvelElement->menu->setVisible(true);
        nouvelElement->menu->ms_menuOuvert = nouvelElement->menu;
        nouvelElement->menu->setPosition ( nouvelElement->bouton->getPosAbs().x
                                         , nouvelElement->bouton->getPosAbs().y + nouvelElement->bouton->getTaille().y
                                         );
    } );



    nouvelElement->menu->lier ( Evenement::onBtnG_relacherDehors , [nouvelElement](){

        if ( ms_init){
            ms_init = false;
            return;
        }
        if ( ms_menuActif ) {
            if ( nouvelElement->menu->ms_menuOuvert != nullptr )
                nouvelElement->menu->ms_menuOuvert->setVisible( false );
            ms_menuActif= false;
        }

    } );


    nouvelElement->bouton   = bouton;

    m_elements.push_back( nouvelElement );

    actualiser ();
    ms_menuBack = nom;

    return nouvelElement->menu;
}


void SupBandeauMenusDeroulants::supprimerMenu  (std::string nom)
{

}

void SupBandeauMenusDeroulants::ajouterElement ( std::string nom, FctnAction fonction, std::string menu  )
{


    for ( auto element : m_elements )
        if ( element->nom == menu ) {
            element->menu->ajouterElement ( nom, fonction );
        }

}


/////////////////////////////////////////////////
void SupBandeauMenusDeroulants::supprimerElement (unsigned int id)
{

}

/////////////////////////////////////////////////
void SupBandeauMenusDeroulants::actualiserGeometrie()
{
    SupBandeau::actualiserGeometrie ();

    int decallage = m_marge.x;
    for ( auto element : m_elements ) {

        element->bouton->setPosition    ( decallage, m_marge.y );
        element->bouton->setTexte       ( element->nom );

        decallage += element->bouton->getTaille().x;
    }
    actualiserBounds ();
}



} // fin namespace gui

