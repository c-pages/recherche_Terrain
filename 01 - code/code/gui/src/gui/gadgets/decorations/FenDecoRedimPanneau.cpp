#include "gadgets/decorations/FenDecoRedimPanneau.h"
#include "gadgets/Fenetre.h"
#include "gadgets/BtnRectangle.h"
#include "gui.h"

namespace gui{

FenDecoRedimPanneau::FenDecoRedimPanneau( Fenetre* fenetre )
: FenDecoration     ( fenetre )
, m_btn_bas         ( std::make_shared<BtnRectangle>() )
{
    m_fenetre->setMarge( { 6 , 6 } );

    m_fenetre->ajouterComposant( m_btn_bas );


    m_btnDragCouleurs.set       ( sf::Color( 0, 0, 0, 50 )     , Etat::desactive );
    m_btnDragCouleurs.set       ( sf::Color( 0, 0, 0, 50 )     , Etat::desactive );
    m_btnDragCouleurs.set       ( sf::Color( 255,255,255, 0 )  , Etat::repos );
    m_btnDragCouleurs.set       ( sf::Color( 255,255,255, 20 ) , Etat::survol );
    m_btnDragCouleurs.set       ( sf::Color( 255,255,255, 25 ) , Etat::press );
    m_btnDragLgnCouleurs.set    ( sf::Color( 255,255,255, 20 ) );
    m_btnDragLgnepaisseurs.set  ( 0 );

    m_btnDragSlideCouleurs.set       ( sf::Color( 0, 0, 0, 50 )     , Etat::desactive );
    m_btnDragSlideCouleurs.set       ( sf::Color( 255,255,255, 40 ) , Etat::repos );
    m_btnDragSlideCouleurs.set       ( sf::Color( 255,255,255, 60 ) , Etat::survol );
    m_btnDragSlideCouleurs.set       ( sf::Color( 255,255,255, 80 ) , Etat::press );
    m_btnDragSlideLgnCouleurs.set    ( sf::Color( 255,255,255, 20 ) );
    m_btnDragSlideLgnepaisseurs.set  ( 0 );

    m_btnDragFndCouleur            = sf::Color::Transparent;
    m_btnDragFndLgnCouleur         = sf::Color( 255,255,255, 20 );
    m_btnDragFndLgnepaisseur       = 1;


    fct_redimStartB = [this](){
//            m_fenetre->demander_aEtre_auDessus();
            m_sourisPosOrigin = m_fenetre->getPosSouris();
            m_tailleOrigin = m_fenetre->getTaille();
            m_redimensionner = true;
        };
    fct_redimStopB = [this](){
            m_redimensionner = false;
            m_fenetre->actualiserBounds();
            Interface::setCurseur ( Curseurs::Defaut );
        };



    m_btn_bas->setFondCouleur ( sf::Color::Transparent );
    m_btn_bas->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_vertical); });
    m_btn_bas->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });

    m_btn_bas->lier (Evenement::onBtnG_presser , fct_redimStartB );
    m_btn_bas->lier (Evenement::onBtnG_relacher, fct_redimStopB );
    m_btn_bas->lier (Evenement::onBtnG_relacherDehors, fct_redimStopB );



    m_fenetre->actualiser();


}

/////////////////////////////////////////////////
FenDecoRedimPanneau::~FenDecoRedimPanneau()
{
    m_fenetre->retirerComposant( m_btn_bas );
}
/*
/////////////////////////////////////////////////
void FenRedim::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

}*/

/////////////////////////////////////////////////
void FenDecoRedimPanneau::actualiserGeometrie ()
{
    //FenSimple::actualiserGeometrie ();

    auto marge = m_fenetre->getMarge();
    auto taille = m_fenetre->getTaille();

    m_btn_bas->setPosition    ( 0 , taille.y - marge.y );
    m_btn_bas->setTaille    ( {taille.x  , marge.y} );

}

/////////////////////////////////////////////////
void FenDecoRedimPanneau::actualiserStyle ()
{

}

/*
/////////////////////////////////////////////////
void FenRedim::actualiser ()
{

}
*/


/////////////////////////////////////////////////
void FenDecoRedimPanneau::corrigerTailleMinimum ()
{
//    std::cout << "MARGE : " << m_fenetre->getMarge().x << ", " << m_fenetre->getMarge().y << "\n";
    if ( m_tailleFenetre.y < m_fenetre->getTailleMini().y  )
        m_tailleFenetre.y =  m_fenetre->getTailleMini().y  ;
}



/////////////////////////////////////////////////
void FenDecoRedimPanneau::redimensionner ()
{
//    std::cout << "redimensionner\n";
    auto posSouris = m_fenetre->getPosSouris();

    m_tailleFenetre = { m_fenetre->getTaille().x , m_tailleOrigin.y + ( posSouris.y - m_sourisPosOrigin.y  ) };
    corrigerTailleMinimum ();
    m_fenetre->setTailleY( m_tailleFenetre.y  );
//    m_fenetre->m_contenant->actualiserGeometrie ();

//    m_fenetre->getParent()->actualiserGeometrie ();
//    m_fenetre->getParent()->actualiserContenu();

//    m_fenetre->getParent()->getParent()->actualiserContenu();
}




/////////////////////////////////////////////////
void FenDecoRedimPanneau::traiterEvenements (const sf::Event& evenement)
{

    if ( redimEnCours() )   redimensionner ();

}

}; // fin namesapce gui
