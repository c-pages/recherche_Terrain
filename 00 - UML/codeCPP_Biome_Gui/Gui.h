#ifndef GUI__H
#define GUI__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Gadget.h"
#include <memory>
#include  "Fabrique.h"



namespace gui {

class Gui;
class Calque;
class Calque;


/////////////////////////////////////////////////
/// \brief Le Gui gère l'ensemble des interactions homme-machine du jeu.
/// D'un coté un système de fenêtre, boutons basique gérant les différents menus de l'appli.
/// De l'autre, le menu phéromones, système central de l'interaction du joueur avec ses fourmis.
/// Une seul instance possible ( design pattern :Singleton)
///
/////////////////////////////////////////////////
class Gui : public gui::Gadget {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
public:
    /////////////////////////////////////////////////
    /// \brief Appel à l'instance de l'interface, la créer si par encore appelé.
    ///
    /////////////////////////////////////////////////
    static std::shared_ptr<Gui> getInstance ();

    /////////////////////////////////////////////////
    /// \brief Traitement général des évenements clavier ou souris de tout les gadgets de l'interface.
    ///
    /// \param evenement		 L'évenemnt à tratier.
    /////////////////////////////////////////////////
    void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments de l'interface.
    ///
    /////////////////////////////////////////////////
    void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine tout les éléments de l'interface.
    ///
    /// \param target		 
    /// \param states		 
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

private:
    /////////////////////////////////////////////////
    /// \brief Constructeur privée pour enpêcher les doublons.
    ///
    /////////////////////////////////////////////////
    Gui ();

    /////////////////////////////////////////////////
    /// \brief Constructeur par copie, bloqué car privé.
    ///
    /// \param copie		 
    /////////////////////////////////////////////////
    Gui (const Gui& copie);



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    static std::shared_ptr<Gui> ms_instance;    ///< L'unique instance de l'interface.    
    Calque m_calqueFond;    ///< Le calque regroupant les gadgets les plus au fond de la vue.    
    Calque m_calqueFenetres;    ///< Le calque regroupant les fenetres.    
public:
    gui::Fabrique creer;     ///< La fabrique des gadget.

}; // fin class Gui

} // fin namespace gui

#endif
