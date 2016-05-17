#include "Log.h"
#include "interfaces/Gadget.h"
#include "Patch.h"


namespace gui {

bool        Log::ms_debugLog = true;
std::string Log::ms_hierarchieBack = "";



/////////////////////////////////////////////////////
Log::Log()

// les filtres d'affichage
: m_afficher_bureau                 ( true )
, m_afficher_panneau_G              ( true )
, m_afficher_panneau_D              ( true )
, m_afficher_bandeaux               ( true )
, m_afficher_bandeauMenuDeroulants  ( true )
, m_afficher_fenetres               ( true )
, m_afficher_menuDeroulants         ( true )
, m_afficher_infos                  ( false )
, m_afficher_souris                 ( true )

, m_afficher_event                  ( true )
, m_afficher_eventGUI               ( true )

, m_afficher_GUI                    ( false )
, m_afficher_horsCalques            ( false )


// le style
//, m_styleFondEnCouleur              ( false )
, m_styleFondEnCouleur              ( true )

// le mute du gadget pour savoir si on affiche les log en lien avec ce gadget
, m_mute                            ( true )

{
    m_preLigne_hierarchie   = "";
    m_preLigne_courant      = "";
    m_preLigne_variable     = "    ";
    m_preLigne_interface    = "";
    m_preLigne_event        = "            # Evenement #     ";

    m_ligneInterface        = "-";


    m_couleur_alert = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY */
                    /*| FOREGROUND_GREEN | FOREGROUND_BLUE |*/ FOREGROUND_RED | FOREGROUND_INTENSITY ;


    if ( m_styleFondEnCouleur )
    {
          // version fond couleur qui fait deconner la console ... //
        m_couleur_calque    = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | */BACKGROUND_INTENSITY /*|
                                FOREGROUND_GREEN | FOREGROUND_BLUE |  FOREGROUND_RED |  FOREGROUND_INTENSITY */;
        m_couleur_hierarchie    = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED |*/ BACKGROUND_INTENSITY
                                | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY /**/  ;
        m_couleur_nomGadget     = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | */BACKGROUND_INTENSITY
                                | FOREGROUND_GREEN | /*FOREGROUND_BLUE |*/ FOREGROUND_RED | FOREGROUND_INTENSITY  ;

        m_couleur_nomInterface  = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED /*| BACKGROUND_INTENSITY */
                                | FOREGROUND_GREEN | /*FOREGROUND_BLUE |*/ FOREGROUND_RED | FOREGROUND_INTENSITY ;

        m_couleur_titre         = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
        m_couleur_courant       = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED /*| FOREGROUND_INTENSITY*/;
        m_couleur_variable       = /*FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED|*/ FOREGROUND_INTENSITY;

        m_couleur_event_1    = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY|
                                FOREGROUND_GREEN |  */ FOREGROUND_BLUE | FOREGROUND_RED/**/ | FOREGROUND_INTENSITY   ;
        m_couleur_event_2    = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY|
                                FOREGROUND_GREEN |  */ FOREGROUND_BLUE | FOREGROUND_RED/**/ | FOREGROUND_INTENSITY   ;
    }

    else
    {

        // version fond noir qui fait pas deconner la console ... //
        m_couleur_calque    = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY |
                               */ /*FOREGROUND_GREEN | FOREGROUND_BLUE |  FOREGROUND_RED | */ FOREGROUND_INTENSITY ;

        m_couleur_hierarchie    = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY
                                | */FOREGROUND_GREEN | FOREGROUND_BLUE |  FOREGROUND_RED |FOREGROUND_INTENSITY /**/  ;
        m_couleur_nomGadget     = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY
                                | */FOREGROUND_GREEN | /*FOREGROUND_BLUE |  */FOREGROUND_RED | FOREGROUND_INTENSITY ;

        m_couleur_nomInterface  = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY
                                | */FOREGROUND_GREEN | /* */FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY ;

        m_couleur_titre         = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
        m_couleur_courant       = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED /*| FOREGROUND_INTENSITY*/;
        m_couleur_variable       = /*FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED|*/ FOREGROUND_INTENSITY;

        m_couleur_event_1    = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY|
                                FOREGROUND_GREEN |  */ FOREGROUND_BLUE | FOREGROUND_RED/**/ | FOREGROUND_INTENSITY   ;
        m_couleur_event_2    = /*BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY|
                                FOREGROUND_GREEN |  */ FOREGROUND_BLUE | FOREGROUND_RED/**/ | FOREGROUND_INTENSITY   ;
    }

};


/////////////////////////////////////////////////
void  Log::setLogActif ( bool val , bool appliquerAuxComposants ){

    m_mute = ! val ;

    if ( appliquerAuxComposants )
        for (auto composant : static_cast<Gadget*>(this)->getComposants() )
            composant->setLogActif ( val );

};

/////////////////////////////////////////////////
void  Log::resetLog ( ){
    ms_hierarchieBack = "";
};

/////////////////////////////////////////////////
std::string Log::getHierarchieGadget()
{
    return static_cast<Gadget*>(this)->getHierarchie();
};
/////////////////////////////////////////////////
std::string Log::getNomGadget()
{
    return static_cast<Gadget*>(this)->getNom();
};
/////////////////////////////////////////////////
std::string Log::getCalqueGadget()
{
    return static_cast<Gadget*>(this)->getCalqueNom();
};
/////////////////////////////////////////////////
bool    Log::estUnCalque()    {

    // debug
//    return false;




    return ( static_cast<Gadget*>(this)->getNom()[0] == '_' );



};
/////////////////////////////////////////////////
bool    Log::estInterface()    {
    static_cast<Gadget*>(this)->estInterface();
};





/////////////////////////////////////////////////
bool Log::checkAffichage()
{

    auto nomCalque = getCalqueGadget();
    if ( !ms_debugLog || estUnCalque()) return false;
    // l'interface
    else if ( estInterface() )          return m_afficher_GUI ;
    // les calques
    else if ( nomCalque == "Bureau")    return m_afficher_bureau ;
    else if ( nomCalque == "Fenetres")  return m_afficher_fenetres ;
    else if ( nomCalque == "PanneauG")  return m_afficher_panneau_G ;
    else if ( nomCalque == "PanneauD")  return m_afficher_panneau_D ;
    else if ( nomCalque == "Bandeaux")  return m_afficher_bandeaux ;
    else if ( nomCalque == "BandeauMD") return m_afficher_bandeauMenuDeroulants ;
    else if ( nomCalque == "Menus")     return m_afficher_menuDeroulants ;
    else if ( nomCalque == "Infos")     return m_afficher_infos ;
    else if ( nomCalque == "Souris")    return m_afficher_souris ;
    // sinon
    else    return m_afficher_horsCalques;
}



/////////////////////////////////////////////////
bool Log::checkAffichageEvent()
{
    if ( ! checkAffichage() || ! m_afficher_event )
        return false;
    if ( estInterface() )
        return m_afficher_eventGUI;
    if ( m_mute )
        return false;

    return true;
}

/////////////////////////////////////////////////
void Log::checkGadget ( ){

    int largeurMax = 77;
    int compteurCharac = 0;

    int posNomCalque;
    int posNomGadget;
    int posNomInterface;

    if ( m_styleFondEnCouleur ) {
        posNomCalque = 0;
        posNomGadget = 12;
        posNomInterface = 12;

        m_preLigne_titre        = "    ";
        m_preLigne_hierarchie   = "";
        m_preLigne_courant      = "    ";
        m_preLigne_variable     = "    ";
        m_preLigne_interface    = "";
        m_ligneInterface        = " ";

    } else {

        posNomCalque = 55;
        posNomGadget = 0;
        posNomInterface = 0;

        m_preLigne_titre        = "    ";
        m_preLigne_hierarchie   = "    ";
        m_preLigne_courant      = "    ";
        m_preLigne_variable     = "    ";
        m_preLigne_interface    = "    ";
        m_ligneInterface        = "-";

    }


    std::string txtManip;
    std::string txtHierarchie = getHierarchieGadget()+ getNomGadget();


    if ( ms_hierarchieBack !=  txtHierarchie )
    {
        ms_hierarchieBack = txtHierarchie;


//        if ( ! m_styleFondEnCouleur )
//            logOut (  "\n");

        // le nom du gadget
        if ( estInterface() ) {
//
//            logOut (  "\n\n" );

            logOut (  "\n");
            SetConsoleTextAttribute( m_console , m_couleur_nomInterface );

//            // ligne horizontale
//            for ( int i = 0; i< largeurMax; i++)  logOut (  m_ligneInterface );
//            logOut (  "\n");


            for ( int i = compteurCharac; i< posNomInterface-1; i++) {
                logOut (  m_ligneInterface );
                compteurCharac ++;
            }
            logOut (  " " );
            compteurCharac ++;

//            // le nom
//            txtManip = " -- ";
//            compteurCharac += txtManip.size();
//            logOut ( txtManip );

            // le nom
            txtManip = getNomGadget();
            compteurCharac += txtManip.size();
            logOut ( txtManip );

            // le nom
//            txtManip = " -- ";
//            compteurCharac += txtManip.size();
//            logOut ( txtManip );

        } else {
            /*
            // le decallage
            txtManip = m_preLigne_courant;
            compteurCharac += txtManip.size();
            logOut ( txtManip );
            */

            SetConsoleTextAttribute( m_console , m_couleur_calque );

            // le calque si on est en style fond couleur
            if ( getCalqueGadget() != "" && m_styleFondEnCouleur ) {

                SetConsoleTextAttribute( m_console , m_couleur_hierarchie );
                for ( int i = compteurCharac; i< posNomCalque; i++) {
                        logOut (  m_ligneInterface );
                        compteurCharac ++;
                }
                SetConsoleTextAttribute( m_console , m_couleur_calque );
                logOut("<");
                compteurCharac++;

                // le nom du calque
                SetConsoleTextAttribute( m_console , m_couleur_calque );
                txtManip = getCalqueGadget();
                compteurCharac += txtManip.size();
                logOut ( txtManip );


                SetConsoleTextAttribute( m_console , m_couleur_calque );
                logOut("> ");
                compteurCharac++;

            }





            // On rejoind la pos du nom du gadget
            for ( int i = compteurCharac; i< posNomGadget; i++) {
                logOut (  m_ligneInterface );
                compteurCharac ++;
            }



            // on ecrit la hierarchie
            if ( m_styleFondEnCouleur )
                SetConsoleTextAttribute( m_console , m_couleur_hierarchie );
            else
                SetConsoleTextAttribute( m_console , FOREGROUND_INTENSITY );

            txtManip = getHierarchieGadget();
            compteurCharac += txtManip.size();
            logOut ( txtManip );

            SetConsoleTextAttribute( m_console    , m_couleur_nomGadget  );

            // le nom
            txtManip = getNomGadget() + " ";
            compteurCharac += txtManip.size();
            logOut ( txtManip );
        }







        // la fin de la ligne (pour un fond autre que noir)
        if ( estInterface() ) {
            SetConsoleTextAttribute( m_console , m_couleur_nomInterface );
            logOut (  " " );
            compteurCharac++;
            for ( int i = compteurCharac; i< largeurMax; i++) logOut (  m_ligneInterface );



//            // ligne horizontale
//            logOut (  "\n");
//            for ( int i = 0; i< largeurMax; i++)  logOut (  m_ligneInterface );

            SetConsoleTextAttribute( m_console , m_couleur_calque );
        } else {


                        // le calque si on est en style fond couleur
            if ( getCalqueGadget() != "" && ! m_styleFondEnCouleur ) {

                SetConsoleTextAttribute( m_console , m_couleur_hierarchie );
                for ( int i = compteurCharac; i< posNomCalque; i++) {
                        logOut (  m_ligneInterface );
                        compteurCharac ++;
                }
                SetConsoleTextAttribute( m_console , m_couleur_hierarchie );
                logOut("<");
                compteurCharac++;

                // le nom du calsue
                SetConsoleTextAttribute( m_console , m_couleur_hierarchie );
                txtManip = getCalqueGadget();
                compteurCharac += txtManip.size();
                logOut ( txtManip );


                SetConsoleTextAttribute( m_console , m_couleur_hierarchie );
                logOut("> ");
                compteurCharac+=2;

                SetConsoleTextAttribute( m_console , m_couleur_hierarchie );
            }




            for ( int i = compteurCharac; i< largeurMax ; i++) logOut (  m_ligneInterface );
            //for ( int i = compteurCharac; i< largeurMax; i++) logOut (  "-" );
        }


        logOut (  "\n");




//        if ( txtHierarchie == "GUI"){
//            for ( int i = 0; i< largeurMax; i++) logOut (  " " );
//            logOut("\n");
//        }
    }

}




/////////////////////////////////////////////////
void Log::logAlerte   ( std::string txt ){
//    if ( m_mute || ! checkAffichage() ) return;

    // on regarde si on a changé de gadget
    checkGadget ( );

    SetConsoleTextAttribute( m_console , m_couleur_alert );
    std::string  preLigne = "        ALERT - ";
    logOut ( preLigne  +  txt  + " - ALERT\n" );

}




/////////////////////////////////////////////////
void Log::logTitre ( std::string txt ){
    if ( m_mute || ! checkAffichage() ) return;

    // on regarde si on a changé de gadget
    checkGadget ( );

    SetConsoleTextAttribute( m_console , m_couleur_titre );
    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface : m_preLigne_titre;
    logOut ( preLigne  +  txt  + "\n" );

}





/////////////////////////////////////////////////
void Log::log ( std::string txt ){
    if ( m_mute || ! checkAffichage() ) return;

    // on regarde si on a changé de gadget
    checkGadget ( );

    SetConsoleTextAttribute( m_console , m_couleur_courant );
    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface : m_preLigne_courant;
    logOut ( preLigne + txt  + "\n" );

}

/////////////////////////////////////////////////
void Log::log (  std::string nomDuVariable , float variable ){
    if ( m_mute || ! checkAffichage() ) return;

    checkGadget ( );

    std::string valVar = patch::to_string(variable);

    SetConsoleTextAttribute( m_console , m_couleur_variable );

    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface + m_preLigne_variable : m_preLigne_courant + m_preLigne_variable;
    logOut ( preLigne +  nomDuVariable + " = "  + valVar + "\n" );

}

/////////////////////////////////////////////////
void Log::log (  std::string nomDuVariable , sf::Vector2f variable ){
    log (  nomDuVariable , sf::Vector2i (variable) );
}

/////////////////////////////////////////////////
void Log::log (  std::string nomDuVariable , sf::Vector2i variable ){
    if ( m_mute || ! checkAffichage() ) return;

    checkGadget ( );

    std::string valVar1 = patch::to_string(variable.x);
    std::string valVar2 = patch::to_string(variable.y);

    SetConsoleTextAttribute( m_console , m_couleur_variable );


    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface + m_preLigne_variable : m_preLigne_courant + m_preLigne_variable;
    logOut ( preLigne +  nomDuVariable + " = ( "  + valVar1 + " , "  + valVar2 + " )\n" );

}

/////////////////////////////////////////////////
void Log::log (  std::string nomDuVariable , std::string variable ){
    if ( m_mute || ! checkAffichage() ) return;

    checkGadget ( );

    SetConsoleTextAttribute( m_console , m_couleur_variable );

    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface + m_preLigne_variable : m_preLigne_courant + m_preLigne_variable;
    logOut ( preLigne +  nomDuVariable + " = \""  + variable + "\"\n" );

}

/////////////////////////////////////////////////
void Log::log (  std::string nomDuVariable , sf::Color couleur ){
    if ( m_mute || ! checkAffichage() ) return;

    checkGadget ( );
//    sf::Color couleur2 = sf::Color::White;
//    couleur2.r = 123;
//    std::cout << "----------> couleur2" << int(couleur2.r) << "\n";
    std::string valVar1 = patch::to_string( int(couleur.r) );
    std::string valVar2 = patch::to_string( int(couleur.g) );
    std::string valVar3 = patch::to_string( int(couleur.b) );
    std::string valVar4 = patch::to_string( int(couleur.a) );

    SetConsoleTextAttribute( m_console , m_couleur_variable );

    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface + m_preLigne_variable : m_preLigne_courant + m_preLigne_variable;
    logOut ( preLigne +  nomDuVariable + " = ("  + valVar1 + ","  + valVar2 + ","  + valVar3 + ","  + valVar4 + ")\n" );

}

/////////////////////////////////////////////////
void Log::log (  std::string nomDuVariable , bool &variable ){
    if ( m_mute || ! checkAffichage() ) return;

    checkGadget ( );

    std::string valVar1 = variable ? "true" : "false" ;

    SetConsoleTextAttribute( m_console , m_couleur_variable );


    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface + m_preLigne_variable : m_preLigne_courant + m_preLigne_variable;
    logOut ( preLigne +  nomDuVariable + " = "  + valVar1 + "\n" );

}

/////////////////////////////////////////////////
void Log::log (  std::string nomDuVariable , std::shared_ptr<Gadget> gadget ){
    if ( m_mute || ! checkAffichage() ) return;

    checkGadget ( );

    std::string valVar1 = gadget->getNom();

    SetConsoleTextAttribute( m_console , m_couleur_variable );
    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface + m_preLigne_variable : m_preLigne_courant + m_preLigne_variable;
    logOut ( preLigne +  nomDuVariable + " = "  + valVar1 + "\n" );

}





/////////////////////////////////////////////////
void Log::log (  std::string nomDuVariable , Gadget* gadget ){
    if ( m_mute || ! checkAffichage() ) return;

    checkGadget ( );

    std::string valVar1 = gadget->getNom();

    SetConsoleTextAttribute( m_console , m_couleur_variable );
    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface + m_preLigne_variable : m_preLigne_courant + m_preLigne_variable;
    logOut ( preLigne +  nomDuVariable + " = "  + valVar1 + "\n" );

}















/////////////////////////////////////////////////
void Log::logEvt ( std::string txt )
{
    if ( ! checkAffichageEvent() ) return;

    // on regarde si on a changé de gadget
    checkGadget ( );

    SetConsoleTextAttribute( m_console , m_couleur_event_1 );
    std::string  preLigne = m_preLigne_event;
    logOut ( preLigne  );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( txt  + "\n" );
}

/////////////////////////////////////////////////
void Log::logEvt (  std::string nomDuVariable , float variable )
{
    if ( ! checkAffichageEvent() ) return;

    checkGadget ( );

    std::string valVar = patch::to_string(variable);

    SetConsoleTextAttribute( m_console , m_couleur_event_1 );
    std::string  preLigne = m_preLigne_event;
    logOut ( preLigne  );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( nomDuVariable + " : "  );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( valVar + "\n" );
}

/////////////////////////////////////////////////
void Log::logEvt (  std::string nomDuVariable , sf::Vector2f variable ){
    log (  nomDuVariable , sf::Vector2i (variable) );
}

/////////////////////////////////////////////////
void Log::logEvt (  std::string nomDuVariable , sf::Vector2i variable )
{
    if ( ! checkAffichageEvent() ) return;

    checkGadget ( );

    std::string valVar1 = patch::to_string(variable.x);
    std::string valVar2 = patch::to_string(variable.y);

    SetConsoleTextAttribute( m_console , m_couleur_event_1 );
    std::string  preLigne = m_preLigne_event;
    logOut ( preLigne  );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( nomDuVariable + " : " );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( "( "  + valVar1 + " , "  + valVar2 + " )\n" );
}

/////////////////////////////////////////////////
void Log::logEvt (  std::string nomDuVariable , std::string variable )
{
    if ( ! checkAffichageEvent() ) return;

    checkGadget ( );

    SetConsoleTextAttribute( m_console , m_couleur_event_1 );
    std::string  preLigne = m_preLigne_event;
    logOut ( preLigne  );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( nomDuVariable + " : " );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( "\""  + variable + "\"\n" );
}

/////////////////////////////////////////////////
void Log::logEvt (  std::string nomDuVariable , sf::Color couleur )
{
    if ( ! checkAffichageEvent() ) return;

    checkGadget ( );

    std::string valVar1 = patch::to_string(couleur.r);
    std::string valVar2 = patch::to_string(couleur.g);
    std::string valVar3 = patch::to_string(couleur.b);
    std::string valVar4 = patch::to_string(couleur.a);

    SetConsoleTextAttribute( m_console , m_couleur_event_1 );
    std::string  preLigne = m_preLigne_event;

    logOut ( preLigne  );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( nomDuVariable + " : "   );


    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( valVar1 + " "  + valVar2 + " "  + valVar3 + " "  + valVar4 + "\n" );
}

/////////////////////////////////////////////////
void Log::logEvt (  std::string nomDuVariable , bool &variable )
{
    if ( ! checkAffichageEvent() ) return;

    checkGadget ( );

    std::string valVar1 = variable ? "true" : "false" ;

    SetConsoleTextAttribute( m_console , m_couleur_event_1 );
    std::string  preLigne = m_preLigne_event;
//    logOut ( preLigne +  nomDuVariable + " : "  + valVar1 + "\n" );

    logOut ( preLigne  );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( nomDuVariable + " : "   );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( valVar1 + "\n"  );
}

/////////////////////////////////////////////////
void Log::logEvt (  std::string nomDuVariable , std::shared_ptr<Gadget> gadget )
{
    // si le gadget concerné est mué on zappe
    if ( gadget != nullptr )
        if ( gadget->m_mute )  return;

    if ( ! checkAffichageEvent() ) return;

    checkGadget ( );
    std::string valVar1 ;
    if ( gadget != nullptr )
        valVar1 = gadget->getNom();
    else
        valVar1 = " - ";

    SetConsoleTextAttribute( m_console , m_couleur_event_1 );
    std::string  preLigne = m_preLigne_event;

    logOut ( preLigne  );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( nomDuVariable   );

    SetConsoleTextAttribute( m_console , m_couleur_event_2 );
    logOut ( " : "  + valVar1 + "\n"  );
}



/////////////////////////////////////////////////
void Log::logEvt (  std::string nomDuVariable , Gadget* gadget ){
    if ( m_mute || ! checkAffichage() ) return;

    checkGadget ( );

    std::string valVar1 = gadget->getNom();

    SetConsoleTextAttribute( m_console , m_couleur_variable );
    std::string  preLigne = ( estInterface() ) ? m_preLigne_interface + m_preLigne_variable : m_preLigne_courant + m_preLigne_variable;
    logOut ( preLigne +  nomDuVariable + " = "  + valVar1 + "\n" );

}

} // fin namespace gui







































