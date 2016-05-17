#include "gadgets/DnZoneNum.h"
#include "gadgets/DnZoneTexte.h"
#include "gadgets/BtnIcone.h"

#include "gui.h"

namespace gui {


/////////////////////////////////////////////////
DnZoneNum::DnZoneNum()
: m_zoneTexte       ( std::make_shared<DnZoneTexte>() )
, m_btnPlus         ( std::make_shared<BtnIcone>() )
, m_btnMoins        ( std::make_shared<BtnIcone>() )

{
    creerNomUnique ( "ZoneNum");
    m_taille = { 180 , 20 };

    ajouterComposant ( m_zoneTexte );
    ajouterComposant ( m_btnPlus );
    ajouterComposant ( m_btnMoins );

    m_btnPlus->setImage( &Interface::ms_icones.get( "ico_fleches" ) ) ;
    m_btnPlus->setFix( true );
    m_btnPlus->setAutoAjuster( false );
    m_btnMoins->setImage( &Interface::ms_icones.get( "ico_fleches" ) ) ;
    m_btnMoins->setIndex ( 2 );
    m_btnMoins->setFix( true );
    m_btnMoins->setAutoAjuster( false );

    m_zoneTexte->setNumericOnly (  true );

    auto fct_plus = [this]()  {
        m_valeur = m_valeur + m_pas;
        if ( m_valeur > m_max )
            m_valeur = m_max;
        m_zoneTexte->setTexte ( patch::to_string( m_valeur ) );

    };
    auto fct_moins = [this]()  {
        m_valeur -= m_pas;
        if ( m_valeur < m_min )
            m_valeur = m_min;
        m_zoneTexte->setTexte ( patch::to_string( m_valeur ) );
    };

    m_btnPlus->lier     ( Evenement::onBtnG_relacher , fct_plus );
    m_btnPlus->lier     ( Evenement::onBtnM_roulerHaut , fct_plus );
    m_btnPlus->lier     ( Evenement::onBtnM_roulerBas , fct_moins );
    m_btnMoins->lier    ( Evenement::onBtnG_relacher , fct_moins );
    m_btnMoins->lier     ( Evenement::onBtnM_roulerHaut , fct_plus );
    m_btnMoins->lier     ( Evenement::onBtnM_roulerBas , fct_moins );

    auto fct_valeurChange = [this]()  {
            declencher( Evenement::on_valeurChange );
    };
    auto fct_valeurValide = [this]()  {
        log ("valider");
        m_valeur = patch::to_float( m_zoneTexte->getValeur() ) ;

        if ( m_valeur > m_max ) m_valeur = m_max;
        if ( m_valeur < m_min ) m_valeur = m_min;

        declencher( Evenement::on_valeurValide );
    };

    m_zoneTexte->lier ( Evenement::on_valeurChange , fct_valeurChange );
    m_zoneTexte->lier ( Evenement::on_valeurValide , fct_valeurValide );

    m_zoneTexte->lier ( Evenement::onBtnM_roulerHaut , fct_plus );
    m_zoneTexte->lier ( Evenement::onBtnM_roulerBas , fct_moins );



}



/////////////////////////////////////////////////
void DnZoneNum::actualiserGeometrie ()
{
    m_btnPlus->setTaille    ( { m_taille.y  , m_taille.y/2 } );
    m_btnPlus->setPosition  ( m_taille.x - m_taille.y + m_marge.x, m_marge.y );

    m_btnMoins->setTaille   ( { m_taille.y  , m_taille.y/2 } );
    m_btnMoins->setPosition ( m_taille.x - m_taille.y + m_marge.x, m_marge.y + m_taille.y/2 );

    m_zoneTexte->setTaille  ( { m_taille.x - m_taille.y , m_taille.y } );
    m_zoneTexte->setPosition(  m_marge.x  , m_marge.y );

    m_zoneTexte->setTexte ( patch::to_string( m_valeur ) );
}

/////////////////////////////////////////////////
void DnZoneNum::actualiserStyle ()
{}

/////////////////////////////////////////////////
void DnZoneNum::traiterEvenements (const sf::Event& evenement)
{
    m_zoneTexte->traiterEvenements ( evenement);
}
/////////////////////////////////////////////////
std::shared_ptr<Gadget>  DnZoneNum::testerSurvol ( sf::Vector2i position )
{
    //if ( m_zoneTexte->modeEcritureActif() )
        return testerSurvolComposants ( position );
//    else if ( m_globalBounds.contains( { position.x , position.y } ) )
//        return m_bouton;

   // return nullptr;
}

}; // fin namesapce gui




















