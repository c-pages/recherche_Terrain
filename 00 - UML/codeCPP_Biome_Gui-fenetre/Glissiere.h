#ifndef GLISSIERE__H
#define GLISSIERE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Gadget.h"



namespace gui {



/////////////////////////////////////////////////
/// \brief Une Glissi�re est un bouton qui permet de deplacer le contenu d'une fenetre.
///
/////////////////////////////////////////////////
class Glissiere : public gui::Gadget {


/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /// \brief l'orientation du slider.
    /////////////////////////////////////////////////
    enum Orientation {
        Horizontal,
        Vertical
    };



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
private:
    /////////////////////////////////////////////////
    /// \brief Constructeur (priv�e, seulement cr�able depuis une fen�tre (pour l(instant).
    ///
    /// \param orientation		 Un slider horizontal ou vertical.
    /////////////////////////////////////////////////
    Glissi�re (Orientation orientation);



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    Orientation m_orientation;    
    Bouton m_btnFond;    ///< Le bouton fix de fond, il permet de d�placer en un clique le m_btnGlissi�re.    
    Bouton m_btnGlissi�re;    ///< Ce bouton est la glissi�re proprement dite, c'est ce bouton qui glisse pour deplacer le contenu de la fenetre.    

}; // fin class Glissiere

} // fin namespace gui

#endif