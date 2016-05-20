#ifndef CALQUE__H
#define CALQUE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Gadget.h"



namespace gui {



/////////////////////////////////////////////////
/// \brief Un calque permet de grouper un ensemble de gadgets et du coup de gérer la position de la profondeur du groupe..
///
/////////////////////////////////////////////////
class Calque : public gui::Gadget {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur.
    ///
    /////////////////////////////////////////////////
    Calque ();

    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    /// \return thisPtr si est survolé, sinon nullptr.
    ///
    /// \param posSouris
    /////////////////////////////////////////////////
//    virtual std::shared_ptr<Gadget> testerSurvol (sf::Vector2i posSouris) ;
    virtual Gadget* testerSurvol (sf::Vector2i posSouris) ;

}; // fin class Calque

} // fin namespace gui

#endif