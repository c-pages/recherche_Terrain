#ifndef IMAGE__H
#define IMAGE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Gadget.h"



namespace gui {



/////////////////////////////////////////////////
/// \brief Une simple image
///
/////////////////////////////////////////////////
class Image : public gui::Gadget {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////
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


}; // fin class Image

} // fin namespace gui

#endif