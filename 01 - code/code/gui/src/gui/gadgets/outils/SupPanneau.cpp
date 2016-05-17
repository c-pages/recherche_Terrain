/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/outils/SupPanneau.h>
#include <gui.h>
//#include <CntSliders.h>



namespace gui {

/////////////////////////////////////////////////
SupPanneau::SupPanneau ()
: m_cote        ( Cote::Gauche )
, m_btn_gauche  ( std::make_shared<BtnRectangle>() )
, m_btn_droite  ( std::make_shared<BtnRectangle>() )
, m_contenant   ( std::make_shared<CntSliders>() )
, m_barreDrag   ( std::make_shared<AffRectangle>() )
, m_largeurBtnTaille ( 7 )
, m_largeurMini     ( 150 +  m_marge.x*2 )
{
    m_marge = { m_largeurBtnTaille , m_largeurBtnTaille };

    ajouterComposant ( m_btn_gauche );
    ajouterComposant ( m_btn_droite );
    ajouterComposant ( m_contenant );
    ajouterComposant ( m_barreDrag );

    m_barreDrag->setFondCouleur ( sf::Color ( 255,255,255,50 ));
    m_barreDrag->setFondLigneEpaisseur ( 0 );
    m_barreDrag->setVisible (false);

    m_contenant->setRepartition ( Repartitions::Verticale );


    auto fct_redimStartG = [this](){
//            demander_aEtre_auDessus();
            m_sourisPosOrigin = getPosSouris();
            m_tailleOrigin = m_taille;
            m_posOrigin = getPosition();
            m_redimGauche = true;
            m_barreDrag->setVisible  ( true );
            drag_gauche ();
//            m_interface->demanderActualisation();
        };
    auto fct_redimStartD = [this](){
//            demander_aEtre_auDessus();
            m_sourisPosOrigin = getPosSouris();
            m_tailleOrigin = m_taille;
            m_posOrigin = getPosition();
            m_redimDroite = true;
            m_barreDrag->setVisible  ( true );
            drag_droite ();
//            m_interface->demanderActualisation();
        };
    auto fct_redimStopG = [this](){
            if ( m_redimDroite || m_redimGauche ){
                m_redimDroite = false;
                m_redimGauche = false;
                m_barreDrag->setVisible  ( false );
                redimensionner_gauche();
                actualiserBounds();
                m_interface->demanderActualisation();
                Interface::setCurseur ( Curseurs::Defaut );
            }
        };
    auto fct_redimStopD = [this](){
            if ( m_redimDroite || m_redimGauche ){
                m_redimDroite = false;
                m_redimGauche = false;
                m_barreDrag->setVisible  ( false );
                redimensionner_droite();
                actualiserBounds();
                m_interface->demanderActualisation();
                Interface::setCurseur ( Curseurs::Defaut );
            }
        };
    m_btn_gauche->lier (Evenement::onBtnG_presser , fct_redimStartG );
    m_btn_gauche->lier (Evenement::onBtnG_relacher, fct_redimStopG );
    m_btn_gauche->lier (Evenement::onBtnG_relacherDehors, fct_redimStopG );

    m_btn_droite->lier (Evenement::onBtnG_presser , fct_redimStartD );
    m_btn_droite->lier (Evenement::onBtnG_relacher, fct_redimStopD);
    m_btn_droite->lier (Evenement::onBtnG_relacherDehors, fct_redimStopD);

    m_btn_gauche->setFondCouleur ( sf::Color::Transparent );
    m_btn_gauche->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_horizontal); });
    m_btn_gauche->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });

    m_btn_droite->setFondCouleur ( sf::Color::Transparent );
    m_btn_droite->lier( Evenement::on_entrer , [this](){ Interface::setCurseur ( Curseurs::Redim_horizontal); });
    m_btn_droite->lier( Evenement::on_sortir , [this](){ Interface::setCurseur ( Curseurs::Defaut ); });

    m_btn_gauche->setPosition ( 0,0 );
}


/////////////////////////////////////////////////
void    SupPanneau::setCote ( Cote cote ) {
    m_cote = cote;
    /*
    switch ( m_cote ){
        case Cote::Droite:
            m_interface->ms_calque_panneau_D->ajouter ( thisPtr());
            break;
        case Cote::Gauche:
            m_interface->ms_calque_panneau_G->ajouter ( thisPtr());
            break;
    }*/
    m_interface->demanderActualisation();
};


/////////////////////////////////////////////////
void SupPanneau::corrigerTailleMinimum ()
{
    if ( m_taille.x < m_largeurMini )
    {
        switch ( m_cote ) {
            case Cote::Droite:
                m_taille.x = m_largeurMini;
                setPosition ( m_interface->getFenetre()->getSize().x - m_taille.x,  getPosition().y );
                break;
            case Cote::Gauche:
                m_taille.x = m_largeurMini;
                break;
        }
    }

}

/////////////////////////////////////////////////
void    SupPanneau::ajouter ( std::shared_ptr<Gadget> gadget, sf::Vector2i positionEcran )
{

   int i = 0;
    for ( auto enfant : m_contenant->getEnfants() )
    {
        if ( gadget->getPosAbs().y  < enfant->getPosAbs().y  )
        {
            m_contenant->ajouter ( gadget , i );
            gadget->actualiserEtatDeco ( );
            return;
        }
        i++;
    }

    m_contenant->ajouter ( gadget );
    gadget->actualiserEtatDeco ( );

    demanderActualisation();

};


/////////////////////////////////////////////////
sf::Vector2i     SupPanneau::getTaille () const {
    if ( ! m_contenant->aEnfants())
        return { 10, m_taille.y};
    else return m_taille;
}

/////////////////////////////////////////////////
void    SupPanneau::actualiserGeometrie ()
{
//    std::cout << "Actualiser PANNEAU\n";

    auto tailleTmp = m_taille;
    if ( ! m_contenant->aEnfants() )    {
//        std::cout << "Actualiser PANNEAU : a PAS Enfants\n";
        tailleTmp.x = 10;
        switch ( m_cote ) {
            case Cote::Droite:
                m_btn_gauche->setVisible ( false );
                break;
            case Cote::Gauche:
                m_btn_droite->setVisible ( false );
                break;
        }
        if ( m_interface !=nullptr)
            m_interface->demanderActualisation();
    }
   else {
//        std::cout << "Actualiser PANNEAU : a Enfants\n";
        switch ( m_cote ) {
            case Cote::Droite:
                m_btn_gauche->setVisible ( true );
                m_btn_droite->setVisible ( false );
                break;
            case Cote::Gauche:
                m_btn_gauche->setVisible ( false );
                m_btn_droite->setVisible ( true );
                break;
        }
    }

    m_fond->setTaille ( tailleTmp );

    m_barreDrag->setTaille ( 20 , tailleTmp.y );

    m_btn_droite->setPosition ( tailleTmp.x - m_btn_droite->getTaille().x, 0 );
    m_btn_gauche->setTaille ( m_largeurBtnTaille , tailleTmp.y );
    m_btn_droite->setTaille ( m_largeurBtnTaille , tailleTmp.y );

    if ( m_contenant->getTaille ().y !=  tailleTmp.y - 2*m_marge.y )
        m_contenant->setTailleY (  tailleTmp.y - 2*m_marge.y );

    if ( m_contenant->getTaille ().x !=  tailleTmp.x - 2*m_marge.x )
        m_contenant->setTailleX (  tailleTmp.x - 2*m_marge.x );

    m_contenant->setPosition ( m_marge.x , m_marge.y );


}


/*
/////////////////////////////////////////////////
void SupPanneau::actualiserEnfants()
{
    sf::Vector2i pos;
    switch ( m_cote ) {
        case Cote::Droite:
            pos = { m_largeurBtnTaille  ,  m_marge.y };
            break;
        case Cote::Gauche:
            pos = { m_marge.x ,  m_marge.y };
            break;
    }
    for ( auto enfant : m_contenant->getEnfants() )
    {

//        if ( enfant->getPosition ().x !=  pos.x && enfant->getPosition().y !=  pos.y )
        enfant->setPosition( pos.x , pos.y );
        if ( enfant->getTaille().x != m_taille.x - m_largeurBtnTaille - 4*m_marge.x )
            enfant->setTailleX( m_taille.x - m_largeurBtnTaille - 4*m_marge.x );

        pos.y += enfant->getTaille().y;
    }
}*/



/////////////////////////////////////////////////
void SupPanneau::traiterEvenements (const sf::Event& evenement)
{


    if ( m_redimGauche ){ drag_gauche (); return; }
    if ( m_redimDroite ){ drag_droite (); return; }

    Support::traiterEvenements (evenement);

//     if ( redimEnCours () )
//        positionnerFenetre ();

}


/////////////////////////////////////////////////
void SupPanneau::redimensionner_gauche ()
{


    auto posSouris = getPosSouris();
    m_taille = { m_tailleOrigin.x - ( posSouris.x - m_sourisPosOrigin.x  ) , m_taille.y };

//    demander_aEtre_auDessus();
    corrigerTailleMinimum ();
//    setTailleX (m_taille.x);

    setPosition ( m_posOrigin.x + ( posSouris.x - m_sourisPosOrigin.x  ),  getPosition().y );

    if ( getPosition().x > m_posOrigin.x + m_tailleOrigin.x - m_largeurMini )
        setPosition ( m_posOrigin.x + m_tailleOrigin.x - m_largeurMini , getPosition().y );



    actualiserGeometrie();




}

/////////////////////////////////////////////////
void SupPanneau::redimensionner_droite ()
{

    auto posSouris = getPosSouris();
    m_taille = { m_tailleOrigin.x + ( posSouris.x - m_sourisPosOrigin.x  ) , m_taille.y };
    corrigerTailleMinimum ();
//    demander_aEtre_auDessus();
    actualiserGeometrie();

}

/////////////////////////////////////////////////
void SupPanneau::drag_gauche ()
{

    auto posSouris = getPosSouris();
    m_barreDrag->setPosAbs ( { posSouris.x , getPosition().y } );

}

/////////////////////////////////////////////////
void SupPanneau::drag_droite ()
{

    auto posSouris = getPosSouris();
    m_barreDrag->setPosAbs ( { posSouris.x - m_barreDrag->getTaille().x , getPosition().y } );

}
/*

/////////////////////////////////////////////////
std::shared_ptr<Gadget>   SupPanneau::testerSurvol ( sf::Vector2i position )
{
    if (! estVisible() )
        return nullptr;

  ///<\todo... a voir si on peut se passer de faire l'actualisation a chaque fois ...(pour l'instant sans ca, ca pose problème a bouton dans fenentre)
    actualiserBounds();

    // Si on survol le gadget
    if ( m_globalBounds.contains( position.x, position.y ) && estActif() )
    {
//        std::cout << "TESTER SURVOL\n";
        // On test le survol des composants
        auto testInterfaceLocal = testerSurvolComposants( position );
        if ( testInterfaceLocal != nullptr )
            return testInterfaceLocal;
        // On test le survol des enfants
        else
        {
            auto testEnfants = testerSurvolEnfants( position );
            if ( testEnfants != nullptr )
                return testEnfants;
            else  return thisPtr();
        }
    }
    else
        return nullptr;

}
*/

/*
/////////////////////////////////////////////////
void SupPanneau::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    if (! estVisible() )
        return;


    //On applique la transformation
    states.transform *= getTransform();

    // on dessine les composants
    dessinerComposant ( target, states);

    // On dessine les enfants (du groupe)
    for ( auto enfant : m_contenant->getEnfants() )
        target.draw ( *enfant , states ) ;

}
*/

} // fin namespace gui



















