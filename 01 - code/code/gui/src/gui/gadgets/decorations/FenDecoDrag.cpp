#include "gadgets/decorations/FenDecoDrag.h"
#include "gui.h"
#include "gadgets/Fenetre.h"




namespace gui{

/////////////////////////////////////////////////
FenDecoDrag::FenDecoDrag( Fenetre* fenetre )
: FenDecoration ( fenetre )
, m_draggable   ( true )
, m_drag        ( false )
, m_decalageDragSouris ( { 0, 0 } )
{

//    m_btnDragCouleurs       = sf::Color::Transparent;
//    m_btnDragLgnCouleurs    = sf::Color::Transparent;
//    m_btnDragLgnepaisseurs  = 0;

    // Action du bouton drag
    m_fenetre->lier ( Evenement::onBtnG_presser , [this](){
        auto posSouris = m_fenetre->getPosSouris();
        m_decalageDragSouris = sf::Vector2i ( posSouris.x - m_fenetre->getPosAbs().x , posSouris.y - m_fenetre->getPosAbs().y );
        setDrag( true );
/*
        // Si on est pas deja dans le calque fenetres on s'y met
        if ( m_fenetre->getParent()->getNom() != Interface::ms_calque_fenetres->getNom() ){
            auto posAbsBack = m_fenetre->getPosAbs();
            Interface::ms_calque_fenetres->ajouter ( m_fenetre->thisPtr() );

            Interface::ms_calque_panneau_D->actualiser();
            Interface::ms_calque_panneau_G->actualiser();

            m_fenetre->setPosAbs( posAbsBack );
//            m_fenetre->getOmbre()->setVisible(true);
        }
        else*/
            m_fenetre->demander_aEtre_auDessus();
    });




    auto fct_finDuDrag = [this](){

            setDrag( false );

            bool survolPanneau = false;
            /*for ( auto panneau : Interface::ms_calque_panneau_D->getEnfants() )
            {
                panneau->setAbsorbable( false );
                if ( panneau->testerSurvol( m_fenetre->getPosSouris() ) != nullptr) {
                    panneau->ajouter ( m_fenetre->thisPtr() , m_fenetre->getPosSouris() );
                    survolPanneau = true;
                    break;
                }
            }*/
            /*
            if (! survolPanneau )
                for ( auto panneau : Interface::ms_calque_panneau_G->getEnfants() )
                {
                    panneau->setAbsorbable( false );
                    if ( panneau->testerSurvol( m_fenetre->getPosSouris() ) != nullptr) {
                        panneau->ajouter ( m_fenetre->thisPtr() , m_fenetre->getPosSouris());
                        survolPanneau = true;
                        break;
                    }
                }
            if ( survolPanneau )
                entreDansPanneau ();
            else sortDuPanneau ();
                */
    };
    m_fenetre->lier ( Evenement::onBtnG_relacher , fct_finDuDrag );
    m_fenetre->lier ( Evenement::onBtnG_relacherDehors , fct_finDuDrag );

}

/////////////////////////////////////////////////
FenDecoDrag::~FenDecoDrag( )
{
    m_fenetre->delier ( Evenement::onBtnG_presser );
    m_fenetre->delier ( Evenement::onBtnG_relacher );
    m_fenetre->delier ( Evenement::onBtnG_relacherDehors );

}





/////////////////////////////////////////////////
void FenDecoDrag::sortDuPanneau ()
{
    m_fenetre->getOmbre()->setVisible(true);
    m_fenetre->actualiserEtatDeco();
}






/////////////////////////////////////////////////
void FenDecoDrag::entreDansPanneau ()
{
    m_fenetre->getOmbre()->setVisible(false);

    m_fenetre->actualiserEtatDeco();
}





/////////////////////////////////////////////////
// Fonctions du templates decoration
/////////////////////////////////////////////////

/////////////////////////////////////////////////
void FenDecoDrag::actualiserGeometrie()
{
//    // Si on est dans le calque 'fenetres' on affiche l'ombre, sinon on la cache
//    if ( m_fenetre->getParent() != nullptr)    {
//        if ( m_fenetre->getParent()->getNom() == Interface::ms_calque_fenetres->getNom() )
//                m_fenetre->getOmbre()->setVisible(true);
//        else    m_fenetre->getOmbre()->setVisible(false);
//    }
}


/////////////////////////////////////////////////
void FenDecoDrag::traiterEvenements (const sf::Event& evenement){
     if ( dragEnCours() )
        positionnerFenetre ();
}


/////////////////////////////////////////////////
// Fonctions locales
/////////////////////////////////////////////////

/////////////////////////////////////////////////
void FenDecoDrag::positionnerFenetre (){

    // on positionne la fenetre
    m_fenetre->setPosAbs ( { m_fenetre->getPosSouris().x - m_decalageDragSouris.x  , m_fenetre->getPosSouris().y - m_decalageDragSouris.y } );

    m_fenetre->declencher (Evenement::onFen_bouge);

    // on regarde si on survol un panneau dans lequel s'incruster
/*    for ( auto panneau : Interface::ms_calque_panneau_D->getEnfants() )
    {
        if ( panneau->testerSurvol( m_fenetre->getPosSouris() ) != nullptr)
                panneau->setAbsorbable( true );
        else    panneau->setAbsorbable( false );
    }
    for ( auto panneau : Interface::ms_calque_panneau_G->getEnfants() )
    {
        if ( panneau->testerSurvol( m_fenetre->getPosSouris() ) != nullptr)
                panneau->setAbsorbable( true );
        else    panneau->setAbsorbable( false );
    }*/


}


} // fin namespace gui
