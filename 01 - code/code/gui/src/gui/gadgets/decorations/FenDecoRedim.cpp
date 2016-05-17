#include "gadgets/decorations/FenDecoRedim.h"
#include "gadgets/Fenetre.h"
#include "gadgets/BtnRectangle.h"
#include "gui.h"

namespace gui{

FenDecoRedim::FenDecoRedim( Fenetre* fenetre )
: FenDecoration     ( fenetre )
, m_btn_gauche      ( std::make_shared<BtnRectangle>() )
, m_btn_droite      ( std::make_shared<BtnRectangle>() )
, m_btn_haut        ( std::make_shared<BtnRectangle>() )
, m_btn_bas         ( std::make_shared<BtnRectangle>() )

, m_btn_hautGauche  ( std::make_shared<BtnRectangle>() )
, m_btn_hautDroite  ( std::make_shared<BtnRectangle>() )
, m_btn_basGauche   ( std::make_shared<BtnRectangle>() )
, m_btn_basDroite   ( std::make_shared<BtnRectangle>() )

//, m_fenetre         ( std::make_shared<FenSimple>() )
{
//    std::cout << "Decoration redim : creation\n";
    m_fenetre->setMarge( { 5 , 5 } );

    m_fenetre->ajouterComposant( m_btn_gauche );
    m_fenetre->ajouterComposant( m_btn_droite );
    m_fenetre->ajouterComposant( m_btn_haut );
    m_fenetre->ajouterComposant( m_btn_bas );

    m_fenetre->ajouterComposant( m_btn_hautGauche );
    m_fenetre->ajouterComposant( m_btn_hautDroite );
    m_fenetre->ajouterComposant( m_btn_basGauche );
    m_fenetre->ajouterComposant( m_btn_basDroite );



    m_btn_gauche->setFondCouleur ( sf::Color::Transparent );
    m_btn_droite->setFondCouleur ( sf::Color::Transparent );
    m_btn_haut->setFondCouleur ( sf::Color::Transparent );
    m_btn_bas->setFondCouleur ( sf::Color::Transparent );

    m_btn_hautGauche->setFondCouleur ( sf::Color::Transparent );
    m_btn_hautDroite->setFondCouleur ( sf::Color::Transparent );
    m_btn_basGauche->setFondCouleur ( sf::Color::Transparent );
    m_btn_basDroite->setFondCouleur ( sf::Color::Transparent );

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





    auto fct_redimStartG = [this](){
            initDrag();
            m_redimGauche = true;
        };
    auto fct_redimStartD = [this](){
            initDrag();
            m_redimDroite = true;
        };
    auto fct_redimStartH = [this](){
            initDrag();
            m_redimHaut = true;
        };
    auto fct_redimStartB = [this](){
            initDrag();
            m_redimBas = true;
        };

    auto fct_redimStartHG = [this](){
            initDrag();
            m_redimHaut = true;
            m_redimGauche = true;
        };
    auto fct_redimStartHD = [this](){
            initDrag();
            m_redimHaut = true;
            m_redimDroite = true;
        };
    auto fct_redimStartBG = [this](){
            initDrag();
            m_redimBas = true;
            m_redimGauche = true;
        };
    auto fct_redimStartBD = [this](){
            initDrag();
            m_redimBas = true;
            m_redimDroite = true;
        };
    auto fct_redimStop = [this](){
            m_redimHaut = false;
            m_redimGauche = false;
            m_redimBas = false;
            m_redimDroite = false;
            m_fenetre->actualiserBounds();
            Interface::setCurseur ( Curseurs::Defaut );
    };


    m_btn_gauche->lier (Evenement::onBtnG_presser , fct_redimStartG );
    m_btn_gauche->lier (Evenement::onBtnG_relacher, fct_redimStop );
    m_btn_gauche->lier (Evenement::onBtnG_relacherDehors, fct_redimStop );

    m_btn_droite->lier (Evenement::onBtnG_presser , fct_redimStartD );
    m_btn_droite->lier (Evenement::onBtnG_relacher, fct_redimStop);
    m_btn_droite->lier (Evenement::onBtnG_relacherDehors, fct_redimStop);

    m_btn_haut->lier (Evenement::onBtnG_presser , fct_redimStartH );
    m_btn_haut->lier (Evenement::onBtnG_relacher, fct_redimStop );
    m_btn_haut->lier (Evenement::onBtnG_relacherDehors, fct_redimStop );

    m_btn_bas->lier (Evenement::onBtnG_presser , fct_redimStartB );
    m_btn_bas->lier (Evenement::onBtnG_relacher, fct_redimStop );
    m_btn_bas->lier (Evenement::onBtnG_relacherDehors, fct_redimStop );

    m_btn_hautGauche->lier (Evenement::onBtnG_presser       , fct_redimStartHG );
    m_btn_hautGauche->lier (Evenement::onBtnG_relacher      , fct_redimStop );
    m_btn_hautGauche->lier (Evenement::onBtnG_relacherDehors, fct_redimStop );

    m_btn_hautDroite->lier (Evenement::onBtnG_presser , fct_redimStartHD);
    m_btn_droite->lier (Evenement::onBtnG_relacher, fct_redimStop );
    m_btn_droite->lier (Evenement::onBtnG_relacherDehors, fct_redimStop );

    m_btn_basGauche->lier (Evenement::onBtnG_presser , fct_redimStartBG);
    m_btn_basGauche->lier (Evenement::onBtnG_relacher, fct_redimStop );
    m_btn_basGauche->lier (Evenement::onBtnG_relacherDehors, fct_redimStop );

    m_btn_basDroite->lier (Evenement::onBtnG_presser , fct_redimStartBD);
    m_btn_basDroite->lier (Evenement::onBtnG_relacher, fct_redimStop );
    m_btn_basDroite->lier (Evenement::onBtnG_relacherDehors, fct_redimStop );


    // le curseur souris de redimension
    m_btn_gauche->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_horizontal); });
    m_btn_gauche->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });
    m_btn_droite->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_horizontal); });
    m_btn_droite->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });
    m_btn_haut->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_vertical); });
    m_btn_haut->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });
    m_btn_bas->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_vertical); });
    m_btn_bas->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });

    m_btn_hautGauche->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_diag1); });
    m_btn_hautGauche->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });
    m_btn_hautDroite->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_diag2); });
    m_btn_hautDroite->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });
    m_btn_basGauche->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_diag2); });
    m_btn_basGauche->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });
    m_btn_basDroite->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_diag1); });
    m_btn_basDroite->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });

    // le curseur souris de redimension
    m_btn_gauche->creerNomUnique        ( "BtnRedim_G" );
    m_btn_droite->creerNomUnique        ( "BtnRedim_D" );
    m_btn_haut->creerNomUnique          ( "BtnRedim_H" );
    m_btn_bas->creerNomUnique           ( "BtnRedim_B" );
    m_btn_hautGauche->creerNomUnique    ( "BtnRedim_HG" );
    m_btn_hautDroite->creerNomUnique    ( "BtnRedim_HD" );
    m_btn_basGauche->creerNomUnique     ( "BtnRedim_BG" );
    m_btn_basDroite->creerNomUnique     ( "BtnRedim_BD" );


//    m_fenetre->actualiser();

}

/////////////////////////////////////////////////
void FenDecoRedim::initDrag()
{
    // la fenetre au dessus
    m_fenetre->demander_aEtre_auDessus();

    // init des valeurs pour le drag
    m_sourisPosOrigin   = m_fenetre->getPosSouris();
    m_tailleOrigin      = m_fenetre->getTaille();
    m_posOrigin         = sf::Vector2i( m_fenetre->getPosition() );
    m_posMin            =   { m_fenetre->getPosition().x + m_fenetre->getTaille().x - m_fenetre->getTailleMini().x
                            , m_fenetre->getPosition().y + m_fenetre->getTaille().y - m_fenetre->getTailleMini().y };
}

/////////////////////////////////////////////////
FenDecoRedim::~FenDecoRedim()
{

    m_fenetre->retirerComposant( m_btn_gauche );
    m_fenetre->retirerComposant( m_btn_droite );
    m_fenetre->retirerComposant( m_btn_haut );
    m_fenetre->retirerComposant( m_btn_bas );

    m_fenetre->retirerComposant( m_btn_hautGauche );
    m_fenetre->retirerComposant( m_btn_hautDroite );
    m_fenetre->retirerComposant( m_btn_basGauche );
    m_fenetre->retirerComposant( m_btn_basDroite );

}





/////////////////////////////////////////////////
void FenDecoRedim::actualiserGeometrie ()
{
    //FenSimple::actualiserGeometrie ();

    auto marge = m_fenetre->getMarge();
    auto taille = m_fenetre->getTaille();

    m_btn_gauche->setTaille ( {marge.x , taille.y - 2*marge.y} );
    m_btn_droite->setTaille ( {marge.x , taille.y - 2*marge.y} );
    m_btn_haut->setTaille   ( {taille.x - 2*marge.x , marge.y} );
    m_btn_bas->setTaille    ( {taille.x - 2*marge.x , marge.y} );

    m_btn_hautGauche->setTaille ( {marge.x , marge.y} );
    m_btn_hautDroite->setTaille ( {marge.x , marge.y} );
    m_btn_basGauche->setTaille  ( {marge.x , marge.y} );
    m_btn_basDroite->setTaille  ( {marge.x , marge.y} );


    m_btn_gauche->setPosition ( 0 , marge.y );
    m_btn_droite->setPosition ( taille.x - marge.x , marge.y );
    m_btn_haut->setPosition   ( marge.x , 0  );
    m_btn_bas->setPosition    ( marge.x  , taille.y - marge.y );

    m_btn_hautGauche->setPosition ( 0 , 0 );
    m_btn_hautDroite->setPosition ( taille.x - marge.x , 0 );
    m_btn_basGauche->setPosition  ( 0 , taille.y - marge.y );
    m_btn_basDroite->setPosition  ( taille.x - marge.x , taille.y - marge.y );


}

/////////////////////////////////////////////////
void FenDecoRedim::actualiserStyle ()
{

}



/////////////////////////////////////////////////
void FenDecoRedim::corrigerTailleMinimum ()
{
    // taille minimum
    if ( m_tailleFenetre.x <  m_fenetre->getTailleMini().x  )
        m_tailleFenetre.x =   m_fenetre->getTailleMini().x;

    if ( m_tailleFenetre.y < m_fenetre->getTailleMini().y  )
        m_tailleFenetre.y =  m_fenetre->getTailleMini().y  ;

    // taille maximum
//    if ( m_tailleFenetre.x >  TAILLE_MASK  )
//        m_tailleFenetre.x =   TAILLE_MASK;
//
//    if ( m_tailleFenetre.y > TAILLE_MASK  )
//        m_tailleFenetre.y =  TAILLE_MASK  ;
}

/////////////////////////////////////////////////
void FenDecoRedim::redimmensionner_haut ()
{
    m_fenetre->log ("redim haut");

    auto posSouris = m_fenetre->getPosSouris();
    auto decalage =  posSouris.y - m_sourisPosOrigin.y ;

    // la taille
    m_tailleFenetre = { m_fenetre->getTaille().x , m_tailleOrigin.y - decalage };
    corrigerTailleMinimum ();
    m_fenetre->setTailleY   ( m_tailleFenetre.y  );

    ///< \todo voir si on peut faire mieux que cette actualisation
//    m_fenetre->actualiser();

    // la position
    auto posDest = m_posOrigin.y + decalage;
    if ( posDest > m_posMin.y )
        posDest = m_posMin.y;
    m_fenetre->setPosition  ( m_fenetre->getPosition().x , posDest );

    // declencher evenement
    m_fenetre->declencher ( Evenement::onFen_redim );
}


/////////////////////////////////////////////////
void FenDecoRedim::redimmensionner_bas ()
{
    auto posSouris = m_fenetre->getPosSouris();

    // la taille
    m_tailleFenetre = { m_fenetre->getTaille().x , m_tailleOrigin.y + ( posSouris.y - m_sourisPosOrigin.y  ) };
    corrigerTailleMinimum ();
    m_fenetre->setTailleY( m_tailleFenetre.y  );

    // declencher evenement
    m_fenetre->declencher ( Evenement::onFen_redim );
}


/////////////////////////////////////////////////
void FenDecoRedim::redimmensionner_gauche ()
{
    auto posSouris = m_fenetre->getPosSouris();

    // la taille
    m_tailleFenetre = { m_tailleOrigin.x - ( posSouris.x - m_sourisPosOrigin.x ), m_fenetre->getTaille().y   };
    corrigerTailleMinimum ();
    m_fenetre->setTailleX( m_tailleFenetre.x  );

    ///< \todo voir si on peut faire mieux que cette actualisation brutale
//    m_fenetre->actualiser();


    // la position
    auto posDest = m_posOrigin.x + posSouris.x - m_sourisPosOrigin.x;
    if ( posDest > m_posMin.x )
        posDest = m_posMin.x;
    m_fenetre->setPosition ( posDest,  m_fenetre->getPosition().y );

    // declencher evenement
    m_fenetre->declencher ( Evenement::onFen_redim );

}

/////////////////////////////////////////////////
void FenDecoRedim::redimmensionner_droite ()
{
    // la taille
    auto posSouris = m_fenetre->getPosSouris();
    m_tailleFenetre = { m_tailleOrigin.x + ( posSouris.x - m_sourisPosOrigin.x  ) , m_fenetre->getTaille().y   };
    corrigerTailleMinimum ();
    m_fenetre->setTailleX( m_tailleFenetre.x  );

    // declencher evenement
    m_fenetre->declencher ( Evenement::onFen_redim );

}





/////////////////////////////////////////////////
void FenDecoRedim::traiterEvenements (const sf::Event& evenement)
{
    if ( m_redimGauche ){ redimmensionner_gauche (); }
    if ( m_redimDroite ){ redimmensionner_droite (); }
    if ( m_redimHaut )  { redimmensionner_haut (); }
    if ( m_redimBas )   { redimmensionner_bas (); }

//    if ( m_redimmensionner )
//        m_fenetre->demanderActuaGeom();

}

}; // fin namesapce gui
