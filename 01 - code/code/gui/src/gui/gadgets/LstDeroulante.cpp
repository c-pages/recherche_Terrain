/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/LstDeroulante.h>
#include <gui.h>



namespace gui {

/////////////////////////////////////////////////
LstDeroulante::LstDeroulante ()
: m_liste       ( std::make_shared<LstSimple>())
, m_boutonLabel ( std::make_shared<BtnTexte>())
, m_fleche      ( std::make_shared<AffIcone>())
{


    creerNomUnique( "ListeDeroulante");

    m_selection = 0;

    m_taille = {150,200};
    m_marge = { 1 , 1 };

    ajouterComposant ( m_boutonLabel );
    ajouterComposant ( m_fleche );
    ajouterComposant ( m_liste );

    m_btnCouleurs.set   ( sf::Color( 0,0,0, 20 )  , Etat::desactive );
    m_btnCouleurs.set   ( sf::Color( 255,255, 255 )  , Etat::repos );
    m_btnCouleurs.set   ( sf::Color( 220,220,220 ) , Etat::survol );
    m_btnCouleurs.set   ( sf::Color( 200,200,200 ) , Etat::press );
    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0 )   );
//    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0 )  , Etat::repos );
//    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0) , Etat::survol );
//    m_btnLignesCouleurs.set   ( sf::Color( 0,0,0 ) , Etat::press );
    m_btnLignesEpaisseurs   = 1;

    m_fndCouleur            = sf::Color( 255 , 255 , 255 , 150);
    m_fndLignesCouleur      = sf::Color( 0 , 0 , 0);
    m_fndLignesEpaisseur    = 1;

    m_textCouleur           = sf::Color( 50 , 50 , 50 );
    m_textCouleur.set   ( sf::Color( 0, 0, 0, 0 )  , Etat::desactive );
    m_textCouleur.set   ( sf::Color( 0,0,0, 255 )  , Etat::repos );
    m_textCouleur.set   ( sf::Color( 0,0,0, 255 ) , Etat::survol );
    m_textCouleur.set   ( sf::Color( 0,0,0, 255 ) , Etat::press );
    m_textStyle             = sf::Text::Style::Regular;
    m_textTaille            = 10;
    m_textPolice            = Interface::ms_polices.get ( "Defaut" );

    m_liste->setAjustement( true );
    m_liste->lier (Evenement::on_valeurChange , [this](){
                       std::cout <<" ListeChange selection: " << m_liste->getSelection() << "\n";
                       m_deroule = false;
                       demanderActuaGeom();
                   });
    m_liste->setVisible ( false );

    m_boutonLabel->setAutoAjuster ( false );
    m_boutonLabel->lier ( Evenement::onBtnG_presser, [this](){
                        m_deroule = !m_deroule;
                        demanderActuaGeom();
                    });
    m_boutonLabel->lier ( Evenement::onBtnG_relacherDehors, [this](){
                        if (m_deroule) {
                            m_deroule = false;
                            demanderActuaGeom();
                        }
                    });
    m_boutonLabel->setTaille    ( { m_taille.x , 16 });

    m_fleche->setImage( &Interface::ms_icones.get( "ico_fleches" )) ;
    m_fleche->setIndex ( 2 );
    m_fleche->setFondCouleur (sf::Color::Black);
}



/////////////////////////////////////////////////
void LstDeroulante::ajouterElement ( std::string nouvelElement )
{
    int index = m_elements.size();

    m_elements.push_back( nouvelElement );

    m_liste->ajouterElement ( nouvelElement );
    demanderActualisation();

};


/////////////////////////////////////////////////
void LstDeroulante::actualiserGeometrie ()
{


    m_fleche->setPosition       ( m_taille.x - m_marge.x - m_fleche->getTaille().x , m_marge.y);
    m_fleche->alignerSur        ( m_boutonLabel , Alignement::Droite, Alignement::Droite );

    if (m_deroule) {
        m_liste->setVisible ( true );
        m_taille = { m_boutonLabel->getTaille().x, m_boutonLabel->getTaille().y + m_liste->getTaille().y };
    }
    else {
        m_liste->setVisible ( false );
        m_taille = m_boutonLabel->getTaille();
    }

    m_liste->setPosition ( 0 , m_boutonLabel->getTaille ().y );
    if ( m_elements.size() > 0 )
        m_boutonLabel->setTexte ( m_elements[m_liste->getSelection()] );
    else m_boutonLabel->setTexte ( "...");

    demanderActuaBounds();
}


/////////////////////////////////////////////////
void LstDeroulante::actualiserStyle ()
{
    m_boutonLabel->setFondCouleur         ( m_btnCouleurs );
    m_boutonLabel->setFondLigneCouleur      ( m_btnLignesCouleurs );
    m_boutonLabel->setFondLigneEpaisseur  ( m_btnLignesEpaisseurs );
   // bouton->setTexteTaille       ( m_textTaille.press );
    m_boutonLabel->setTexteCouleur      ( m_textCouleur );
    //bouton->setTextePolice            ( m_textPolice.press );
   // bouton->setTexteStyle        ( m_textStyle.press );*/
}

/*
/////////////////////////////////////////////////
void LstDeroulante::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

}
*/

} // fin namespace gui

