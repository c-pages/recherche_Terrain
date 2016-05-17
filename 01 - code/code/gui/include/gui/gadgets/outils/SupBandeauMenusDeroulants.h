#ifndef SUPBANDEAUMENUSDEROULANTS__H
#define SUPBANDEAUMENUSDEROULANTS__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "SupBandeau.h"
#include "gadgets/BtnTexte.h"
//#include "gui.h"
#include <SFML/Graphics.hpp>
#include <memory>



namespace gui {

class BtnMenu;
class Interface;

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
class SupBandeauMenusDeroulants : public gui::SupBandeau {


/////////////////////////////////////////////////
// structs internes
/////////////////////////////////////////////////
struct ElementMenu {
    std::string                 nom;
    std::shared_ptr<BtnTexte>   bouton;
    std::shared_ptr<BtnMenu>    menu;
};


/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    SupBandeauMenusDeroulants ();

    std::shared_ptr<BtnMenu> ajouterMenu    (std::string nom);
    void supprimerMenu  (std::string nom);

    void ajouterElement ( std::string nom, FctnAction fonction = [](){} , std::string dansMenu = ms_menuBack );

    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param id
    /////////////////////////////////////////////////
    void supprimerElement (unsigned int id);


    /////////////////////////////////////////////////
    void actualiserGeometrie();

    static void fermerMenu();
private:
    static   std::string            ms_menuBack;
    static   bool                   ms_menuActif;
    static   bool                   ms_init;

    std::vector <ElementMenu*>      m_elements;

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:


}; // fin class SupBandeauMenusDeroulants

} // fin namespace gui

#endif
