/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <interfaces/ActionEvenement.h>

#include <iostream>

namespace gui {
/////////////////////////////////////////////////
ActionEvenement::ActionEvenement  ()
: m_evenementsSouris( )
{

}

/////////////////////////////////////////////////
void ActionEvenement::lier  (Evenement evenement, FctnAction fonction)
{
    m_evenementsSouris.insert( { evenement , fonction } );
}


/////////////////////////////////////////////////
void ActionEvenement::delier ( Evenement evenement )
{

    auto cherche = m_evenementsSouris.find( evenement );
    if ( cherche != m_evenementsSouris.end() )
        m_evenementsSouris.erase ( evenement );

}

/////////////////////////////////////////////////
bool ActionEvenement::existe ( Evenement evenement ){
    auto cherche = m_evenementsSouris.find( evenement );
    return cherche != m_evenementsSouris.end();
}


/////////////////////////////////////////////////
void ActionEvenement::declencher ( Evenement evenement )
{
//    if ( existe ( evenement ) )
        switch ( evenement ){
            case Evenement::onBtnG_dblCliquer:      logEvt ( "declencher" , "onBtnG_dblCliquer" );      break;
            case Evenement::onBtnG_relacher:        logEvt ( "declencher" , "onBtnG_relacher" );        break;
            case Evenement::onBtnG_relacherDehors:  logEvt ( "declencher" , "onBtnG_relacherDehors" );  break;
            case Evenement::onBtnG_presser:         logEvt ( "declencher" , "onBtnG_presser" );         break;
            case Evenement::onBtnG_presserDehors:   logEvt ( "declencher" , "onBtnG_presserDehors" );   break;

            case Evenement::onBtnD_relacher:        logEvt ( "declencher" , "onBtnD_relacher" );        break;
            case Evenement::onBtnD_relacherDehors:  logEvt ( "declencher" , "onBtnD_relacherDehors" );  break;
            case Evenement::onBtnD_presser:         logEvt ( "declencher" , "onBtnD_presser" );         break;

            case Evenement::onBtnM_relacher:        logEvt ( "declencher" , "onBtnM_relacher" );        break;
            case Evenement::onBtnM_relacherDehors:  logEvt ( "declencher" , "onBtnM_relacherDehors" );  break;
            case Evenement::onBtnM_presser:         logEvt ( "declencher" , "onBtnM_presser" );         break;
            case Evenement::onBtnM_roulerHaut:      logEvt ( "declencher" , "onBtnM_roulerHaut" );      break;
            case Evenement::onBtnM_roulerBas:       logEvt ( "declencher" , "onBtnM_roulerBas" );       break;

            case Evenement::on_valeurChange:        logEvt ( "declencher" , "on_valeurChange" );        break;
            case Evenement::on_valeurValide:        logEvt ( "declencher" , "on_valeurValide" );        break;

            case Evenement::onBool_allume:          logEvt ( "declencher" , "onBool_allume" );          break;
            case Evenement::onBool_eteind:          logEvt ( "declencher" , "onBool_eteind" );          break;

            case Evenement::on_entrer:              logEvt ( "declencher" , "on_entrer" );              break;
            case Evenement::on_sortir:              logEvt ( "declencher" , "on_sortir" );              break;

            case Evenement::onFen_fermer:           logEvt ( "declencher" , "onFen_fermer" );           break;
            case Evenement::onFen_ouvrir:           logEvt ( "declencher" , "onFen_ouvrir" );           break;
        }

    if ( estVisible() && estActif() ) {
        auto cherche = m_evenementsSouris.find( evenement );
        if ( cherche != m_evenementsSouris.end() )
            cherche->second();
    }
}



} // fin namespace gui

