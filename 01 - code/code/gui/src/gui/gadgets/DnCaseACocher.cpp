/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/DnCaseACocher.h>
#include <gui.h>



namespace gui {

/////////////////////////////////////////////////
DnCaseACocher::DnCaseACocher ()
: m_bouton ( std::make_shared<BtnRectangle>() )
, m_coche  ( std::make_shared<AffRectangle>() )

{
    creerNomUnique( "BoutonACocher" );

    // initialiser quelques valeurs
    m_marge.x = m_marge.y = 3;
    m_taille.x = 15;
    m_taille.y = 15;
    m_valeur = true;

    // initialiser les composants herités
    CmpTexte::initialiserComposants ( this );

    // ajout des composants locaux
    ajouterComposant( m_bouton );
    ajouterComposant( m_coche );


    // valeurs par defaut
    m_btnCouleurs.set       ( sf::Color( 0, 0, 0, 50 )  , Etat::desactive );
    m_btnCouleurs.set       ( sf::Color( 255,255,255, 50 )  , Etat::repos );
    m_btnCouleurs.set       ( sf::Color( 255,255,255, 100 ) , Etat::survol );
    m_btnCouleurs.set       ( sf::Color( 255,255,255, 150 ) , Etat::press );
    m_btnLgnCouleurs.set    ( sf::Color( 255,255,255, 100 ) );
    m_btnLgnepaisseurs.set  ( 0 );

    m_cocheCouleurs          = sf::Color(255,255,255,200) ;
    m_cocheCouleurs.set      ( sf::Color( 70, 70, 70 )  , Etat::desactive );
    m_cocheLgnCouleurs       = sf::Color( 255,255,0, 255 ) ;
    m_cocheLgnepaisseurs     = 0 ;

    m_textCouleur.set( sf::Color( 150,150,150) );
    m_textCouleur.set( sf::Color( 200,200,200 ) , Etat::survol );
    m_textTaille.set ( 12 ) ;
    m_textPolice.set ( Interface::ms_polices.get( "Defaut" ) ) ;
    m_textStyle.set  ( sf::Text::Style::Regular ) ;

    CmpTexte::appliquerEtat ( m_bouton->etat() );

    // Declaration des fonctions de fonctionnement de l'interface interne du gadget.
    fn_basculerValeur = [this](){
        // On inverse le boolean valeur
        m_valeur = !m_valeur;

        // Déclechements des evenements
        declencher(Evenement::on_valeurChange);
        if (m_valeur)   declencher(Evenement::onBool_allume);
        else            declencher(Evenement::onBool_eteind);

        m_coche->setVisible( m_valeur );

    };

    // Action du bouton
    m_bouton->lier ( Evenement::onBtnG_relacher , fn_basculerValeur );
    m_bouton->lier ( Evenement::on_entrer , [this](){
        CmpTexte::appliquerEtat ( m_bouton->etat() );
    } );
    m_bouton->lier ( Evenement::on_sortir , [this](){
        CmpTexte::appliquerEtat ( m_bouton->etat() );
                    } );


}




/////////////////////////////////////////////////
void DnCaseACocher::actualiserGeometrie ()
{
    log ("actualiserGeometrie");


    m_bouton->setTaille  ( m_taille );

    m_label->setPosition ( m_taille.x + 2*m_marge.x , 0 );

    m_coche->setTaille   ( { m_taille.x - 2*m_marge.x , m_taille.y - 2*m_marge.y } );
    m_coche->setPosition ( m_marge.x , m_marge.y );

    demanderActuaBounds();
}


/////////////////////////////////////////////////
void DnCaseACocher::actualiserStyle ()
{
    log ("actualiserStyle ICI LA");

    // on actualise la coche
    m_coche->setFondCouleur         ( m_cocheCouleurs.repos );
    m_coche->setFondLigneCouleur    ( m_cocheLgnCouleurs.repos);
    m_coche->setFondLigneEpaisseur  ( m_cocheLgnepaisseurs.repos );

    // le fond
    m_bouton->setFondCouleur        ( m_btnCouleurs ) ;
    m_bouton->setFondLigneCouleur   ( m_btnLgnCouleurs  ) ;
    m_bouton->setFondLigneEpaisseur ( m_btnLgnepaisseurs  );


}



/////////////////////////////////////////////////
void DnCaseACocher::actualiserBounds() {
    log ("actualiserBounds");
    m_globalBounds.left = getPosAbs().x;
    m_globalBounds.top = getPosAbs().y;
    m_globalBounds.width = m_taille.x + m_label->getTaille().x + 2*m_marge.x;
    m_globalBounds.height = m_taille.y;
};



/////////////////////////////////////////////////
std::shared_ptr<Gadget>  DnCaseACocher::testerSurvol ( sf::Vector2i position )
{
    // on test sur le bouton et le texte
    if ( m_globalBounds.contains( { position.x , position.y} ) )
        return m_bouton;

    return nullptr;
}


} // fin namespace gui

