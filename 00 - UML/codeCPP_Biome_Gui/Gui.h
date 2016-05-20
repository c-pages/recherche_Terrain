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
/// \brief Le Gui g�re l'ensemble des interactions homme-machine du jeu.
/// D'un cot� un syst�me de fen�tre, boutons basique g�rant les diff�rents menus de l'appli.
/// De l'autre, le menu ph�romones, syst�me central de l'interaction du joueur avec ses fourmis.
///
/////////////////////////////////////////////////
class Gui : public gui::Gadget {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
public:
    /////////////////////////////////////////////////
    /// \brief Traitement des �venements clavier ou souris.
    ///
    /// \param evenement		 L'�venemnt � tratier.
    /////////////////////////////////////////////////
    void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualiser les �l�ments de l'interface.
    ///
    /////////////////////////////////////////////////
    void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine tout les �l�ments de l'interface.
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
