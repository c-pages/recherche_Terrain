/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/LstSimple.h>
#include <gui.h>



namespace gui {

/////////////////////////////////////////////////

LstSimple::LstSimple ()
: m_fond    ( std::make_shared<AffRectangle>() )
{
    m_ajustement = true;

    creerNomUnique( "ListeSimple");

    ajouterComposant ( m_fond );

    m_selection = 0;

    m_taille = {150,200};
    m_marge = { 1 , 1 };

    m_btnCouleurs.set   ( sf::Color( 0,0,0, 0 )  , Etat::desactive );
    m_btnCouleurs.set   ( sf::Color( 0,0,0, 0 )  , Etat::repos );
    m_btnCouleurs.set   ( sf::Color( 0,0,0, 70 ) , Etat::survol );
    m_btnCouleurs.set   ( sf::Color( 0,0,0, 150 ) , Etat::press );
    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0, 0 )  , Etat::desactive );
    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0, 50 )  , Etat::repos );
    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0, 200 ) , Etat::survol );
    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0, 200 ) , Etat::press );
    m_btnLignesEpaisseurs   = 0;

    m_fndCouleur            = sf::Color( 255 , 255 , 255 );
    m_fndLignesCouleur      = sf::Color( 0 , 0 , 0);
    m_fndLignesEpaisseur    = 1;

    m_textCouleur           = sf::Color( 50 , 50 , 50 );
    m_textCouleur.set   ( sf::Color( 0, 0, 0, 0 )  , Etat::desactive );
    m_textCouleur.set   ( sf::Color( 0,0,0, 255 )  , Etat::repos );
    m_textCouleur.set   ( sf::Color( 255,255,255, 255 ) , Etat::survol );
    m_textCouleur.set   ( sf::Color( 255,255,255, 255 ) , Etat::press );
    m_textStyle             = sf::Text::Style::Regular;
    m_textTaille            = 10;
    m_textPolice            = Interface::ms_polices.get ( "Defaut" );
}




/////////////////////////////////////////////////
void LstSimple::ajouterElement ( std::string nouvelElement )
{
    int index = m_elements.size();

    m_elements.push_back( nouvelElement );

    std::shared_ptr<BtnTexte> nouveauBouton = std::make_shared<BtnTexte>();
    nouveauBouton->setAutoAjuster ( false );
    nouveauBouton->setTexte( nouvelElement );
    nouveauBouton->setTaille            ( { m_taille.x - 2*m_marge.x , 15 } );
    nouveauBouton->setPosition          ( m_marge.x , ( m_elements.size() - 1 )* nouveauBouton->getTaille().y  + m_marge.y );
    nouveauBouton->lier ( Evenement::onBtnG_relacher, [index, this](){
                             this->setSelection( index );
                             demanderActuaStyle();
                         });

    m_boutons.push_back( nouveauBouton );
    ajouter( nouveauBouton );

    demanderActualisation();
};








/////////////////////////////////////////////////
void LstSimple::actualiserGeometrie ()
{
//    std::cout << " LstSimple::actualiserGeometrie : " << m_selection << " \n";



    float decallageY = m_marge.y;
    for ( auto bouton : m_boutons ) {
        bouton->setPosition    ( m_marge.x , decallageY );
        decallageY += bouton->getTaille().y;
    }

    actualiserBounds ();

    if ( m_ajustement )
        m_fond->setTaille ( { m_taille.x, decallageY + m_marge.y } );
    else
        m_fond->setTaille ( m_taille );

}


/////////////////////////////////////////////////
void LstSimple::actualiserStyle () {

    m_fond->setFondCouleur          ( m_fndCouleur );
    m_fond->setFondLigneCouleur     ( m_fndLignesCouleur );
    m_fond->setFondLigneEpaisseur   ( m_fndLignesEpaisseur );

    int index = 0;
    for ( auto bouton : m_boutons ) {
        if ( index == m_selection )        {
            bouton->setFondCouleur          ( m_btnCouleurs.press );
            bouton->setFondLigneCouleur     ( m_btnLignesCouleurs.press );
            bouton->setFondLigneEpaisseur   ( m_btnLignesEpaisseurs.press );
            bouton->setTexteTaille          ( m_textTaille.press );
            bouton->setTexteCouleur         ( m_textCouleur.press );
            bouton->setTextePolice          ( m_textPolice.press );
            bouton->setTexteStyle           ( m_textStyle.press );
        } else {
            bouton->setFondCouleur          ( m_btnCouleurs );
            bouton->setFondLigneCouleur     ( m_btnLignesCouleurs );
            bouton->setFondLigneEpaisseur   ( m_btnLignesEpaisseurs );
            bouton->setTexteTaille          ( m_textTaille );
            bouton->setTexteCouleur         ( m_textCouleur );
            bouton->setTextePolice          ( m_textPolice );
            bouton->setTexteStyle           ( m_textStyle );
        }
        index++;
    }
}

/*
/////////////////////////////////////////////////
void LstSimple::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    Gadget::draw(target,  states);
}
*/

} // fin namespace gui

