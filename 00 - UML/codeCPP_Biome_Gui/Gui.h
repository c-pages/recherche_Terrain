#ifndef GUI__H
#define GUI__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Gadget.h"
#include <memory>
#include  "Fabrique.h"
#include  "Style.h"



namespace gui {



/////////////////////////////////////////////////
/// \brief Le Gui gère l'ensemble des interactions homme-machine du jeu.
/// D'un coté un système de fenêtre, boutons basique gérant les différents menus de l'appli.
/// De l'autre, le menu phéromones, système central de l'interaction du joueur avec ses fourmis.
///
/////////////////////////////////////////////////
class Gui : public gui::Gadget {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
public:
    /////////////////////////////////////////////////
    /// \brief Traitement des évenements clavier ou souris.
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



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
public:
    gui::Fabrique creer;     ///< La fabrique des gadget.
private:
    gui::Style m_style;     ///< Regroupe les couleurs, polices et style de texte de l'interface.

}; // fin class Gui

} // fin namespace gui

#endif
