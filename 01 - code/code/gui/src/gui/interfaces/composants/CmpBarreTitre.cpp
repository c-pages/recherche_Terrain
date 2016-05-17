#include "interfaces/composants/CmpBarreTitre.h"
#include "gui.h"
#include "Enums.h"
namespace gui {



CmpBarreTitre::CmpBarreTitre()
: m_titreFond   ( std::make_shared<AffRectangle>() )
, m_titreLabel  ( std::make_shared<AffLabel>() )
, m_titreIcone  ( std::make_shared<AffIcone>() )
, m_btnFermer   ( std::make_shared<BtnIcone>() )
, m_btnReduire  ( std::make_shared<BtnIcone>() )
{

    // valeurs par defaut
    m_titreTaille    = { 200 , 20 };
    m_titreMarge     = { 2 , 2 };
    m_taillebouton   = { m_titreTaille.y, m_titreTaille.y };

    m_titreTextCouleur         = sf::Color( 255,255,255 ) ;
    m_titreTextStyle           = sf::Text::Style::Regular;
    m_titreTextTaille          = 10;
    m_titreTextPolice          = Interface::ms_polices.get ( "Defaut" );

//    m_titreFondCouleur         = sf::Color( 55,55,55 ) ;
    m_titreFondCouleur         = sf::Color::Transparent ;
    m_titreFondLgnCouleur      = sf::Color( 90,90,90 ) ;
    m_titreFondLgnepaisseur    = 0;

    m_titreBtnCouleur           = sf::Color::Transparent ;
    m_titreBtnCouleur.survol    = sf::Color( 255 ,255,255,30 ) ;
    m_titreBtnCouleur.press     = sf::Color( 255 ,255,255,70 ) ;
    m_titreBtnLgnCouleur        = sf::Color::Transparent ;
    m_titreBtnLgnepaisseur      = 0;


    auto fctFermer = [this](){
        m_base->fermer();
    };


    auto fctReduire = [this](){
        m_base->reduire();
    };

    // les boutons
    m_btnFermer->lier ( Evenement::onBtnG_relacher , fctFermer );
    m_btnReduire->lier ( Evenement::onBtnG_relacher , fctReduire );
    m_btnFermer->setInfo ("Fermer");
    m_btnReduire->setInfo ("Réduire");


}


/////////////////////////////////////////////////
void CmpBarreTitre::initialiserComposants ( Gadget*     base ){
    m_base = base ;
    m_base->ajouterComposant    ( m_titreFond );
    m_base->ajouterComposant    ( m_titreLabel );
    m_base->ajouterComposant    ( m_titreIcone );
    m_base->ajouterComposant    ( m_btnReduire );
    m_base->ajouterComposant    ( m_btnFermer );

    m_btnReduire->setAutoAjuster (false );
    m_btnFermer->setAutoAjuster (false );

    m_titreFond->creerNomUnique("Fond");
    m_titreLabel->creerNomUnique("Label");
    m_titreIcone->creerNomUnique("Icone");
    m_btnReduire->creerNomUnique("btnReduire");
    m_btnFermer->creerNomUnique("btnFermer");
};

/////////////////////////////////////////////////
void CmpBarreTitre::actualiserGeometrie(){

    m_titreTaille = { m_base->getTaille().x - 2* m_base->getMarge().x , m_titreTaille.y };

    m_titreFond->setTaille      ( m_titreTaille  );
    m_titreFond->setPosition    ( m_base->getMarge() );

    m_titreIcone->alignerSur ( m_titreFond , Alignement::Gauche , Alignement::Gauche );
    m_titreIcone->move( m_titreMarge.x , 0 );

    m_titreLabel->alignerSur ( m_titreIcone , Alignement::Gauche , Alignement::Droite );
    m_titreLabel->move( m_titreMarge.x , -3 );

    m_btnFermer->setTaille      ( m_taillebouton );
    m_btnFermer->alignerSur ( m_titreFond , Alignement::Droite , Alignement::Droite );

    m_btnReduire->setTaille     ( m_taillebouton );
    m_btnReduire->alignerSur ( m_btnFermer , Alignement::Droite , Alignement::Gauche );


}

/////////////////////////////////////////////////
void CmpBarreTitre::actualiserStyle(){

    m_titreLabel->setTexteTaille     ( m_titreTextTaille );
    m_titreLabel->setTexteCouleur    ( m_titreTextCouleur );
    m_titreLabel->setTextePolice     ( m_titreTextPolice );
    m_titreLabel->setTexteStyle      ( m_titreTextStyle );

    m_titreFond->setFondCouleur        ( m_titreFondCouleur );
    m_titreFond->setFondLigneCouleur   ( m_titreFondLgnCouleur );
    m_titreFond->setFondLigneEpaisseur ( m_titreFondLgnepaisseur );

    m_btnReduire->setFondCouleur        ( m_titreBtnCouleur );
    m_btnReduire->setFondLigneCouleur        ( m_titreBtnLgnCouleur );
    m_btnReduire->setFondLigneEpaisseur        ( m_titreBtnLgnepaisseur );

    m_btnReduire->setImage  ( &Interface::ms_icones.get("ico_fenetre"));
    m_btnReduire->setIndex  ( 2 );
    m_btnReduire->setFix    ( true );

    m_btnFermer->setFondCouleur        ( m_titreBtnCouleur );
    m_btnFermer->setFondLigneCouleur        ( m_titreBtnLgnCouleur );
    m_btnFermer->setFondLigneEpaisseur        ( m_titreBtnLgnepaisseur );

    m_btnFermer->setImage  ( &Interface::ms_icones.get("ico_fenetre"));
    m_btnFermer->setIndex  ( 1 );
    m_btnFermer->setFix    ( true );

}

/////////////////////////////////////////////////
void CmpBarreTitre::setTitre( std::string val ){
    m_base->log("setTitre ", val  );
//    m_texte = val;
    m_titreLabel->setTexte ( val ) ;
    m_base->demanderActuaGeom();
};

/////////////////////////////////////////////////
std::string  CmpBarreTitre::getTitre( ) const{
    return m_titreLabel->getTexte();
};


/////////////////////////////////////////////////
void CmpBarreTitre::setTitreTxtTaille( float val  ){
    m_titreLabel->setTexteTaille ( val ) ;
    m_base->demanderActuaStyle();
};



/////////////////////////////////////////////////
void CmpBarreTitre::setTitreTxtCouleur( sf::Color couleur){
    m_titreTextCouleur = couleur  ;
    m_base->demanderActuaStyle();
};



/////////////////////////////////////////////////
void CmpBarreTitre::setTitreTxtPolice( sf::Font val  ){
    m_titreTextPolice = val  ;
    m_base->demanderActuaStyle();
}



/////////////////////////////////////////////////
void CmpBarreTitre::setTitreTxtStyle( sf::Text::Style val   )  {
    m_titreTextStyle =  val   ;
    m_titreLabel->setTexteStyle    ( val  ) ;
}



/////////////////////////////////////////////////
void CmpBarreTitre::setTitreIcone   (std::string fichier ){
    m_titreIcone->setImage( fichier );
}

/////////////////////////////////////////////////
void CmpBarreTitre::setTitreIcone   (sf::Texture* texture ){
    m_titreIcone->setImage( texture );
}


}



















