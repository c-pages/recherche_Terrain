#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <memory>
#include <windows.h>
#include "SFML/Graphics.hpp"

using namespace std;

#define logOut( txt )  cout <<  txt ;

namespace gui {
class Gadget;


class Log {

public :

    Log();

    void logTitre   ( std::string txt );
    void logAlerte   ( std::string txt );

    void log ( std::string txt );
    void log ( std::string nomDuVariable , std::string     variable );
    void log ( std::string nomDuVariable , float           variable );
    void log ( std::string nomDuVariable , sf::Vector2f    variable );
    void log ( std::string nomDuVariable , sf::Vector2i    variable );
    void log ( std::string nomDuVariable , sf::Color       couleur  );
    void log ( std::string nomDuVariable , bool&           variable );
    void log ( std::string nomDuVariable , std::shared_ptr<Gadget> gadget );
    void log ( std::string nomDuVariable , Gadget*          gadget );

    void logEvt ( std::string txt );
    void logEvt ( std::string nomDuVariable , std::string     variable );
    void logEvt ( std::string nomDuVariable , float           variable );
    void logEvt ( std::string nomDuVariable , sf::Vector2f    variable );
    void logEvt ( std::string nomDuVariable , sf::Vector2i    variable );
    void logEvt ( std::string nomDuVariable , sf::Color       couleur  );
    void logEvt ( std::string nomDuVariable , bool&           variable );
    void logEvt ( std::string nomDuVariable , std::shared_ptr<Gadget> gadget );
    void logEvt ( std::string nomDuVariable , Gadget*          gadget );

    void setLogActif     ( bool val , bool appliquerAuxComposants = false );

    void resetLog   ( );

private:
    bool        checkAffichage();
    bool        checkAffichageEvent();

    std::string getHierarchieGadget();
    std::string getNomGadget();
    std::string getCalqueGadget();

    void        checkGadget ( );
    bool        estUnCalque();
    bool        estInterface();

private:
    static  bool            ms_debugLog;
    static  std::string     ms_hierarchieBack;

    HANDLE                  m_console = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string             m_preLigne_hierarchie;
    std::string             m_preLigne_courant;
    std::string             m_preLigne_variable;
    std::string             m_preLigne_interface;
    std::string             m_preLigne_titre;

    std::string             m_preLigne_event;

    std::string             m_ligneInterface;

    WORD                    m_couleur_calque;
    WORD                    m_couleur_hierarchie;
    WORD                    m_couleur_nomGadget;

    WORD                    m_couleur_nomInterface;

    WORD                    m_couleur_titre;
    WORD                    m_couleur_courant;
    WORD                    m_couleur_variable;
    WORD                    m_couleur_event_1;
    WORD                    m_couleur_event_2;
    WORD                    m_couleur_alert;


    bool m_styleFondEnCouleur ;

    bool m_afficher_bureau ;
    bool m_afficher_panneau_G ;
    bool m_afficher_panneau_D ;
    bool m_afficher_bandeaux ;
    bool m_afficher_bandeauMenuDeroulants ;
    bool m_afficher_fenetres ;
    bool m_afficher_menuDeroulants ;
    bool m_afficher_infos ;
    bool m_afficher_souris ;

    bool m_afficher_event ;
    bool m_afficher_eventGUI ;

    bool m_afficher_GUI ;

    bool m_afficher_horsCalques ;

protected:
    bool m_mute;


};  // fin log

}; // fin namesapce gui

#endif // LOG_H


















