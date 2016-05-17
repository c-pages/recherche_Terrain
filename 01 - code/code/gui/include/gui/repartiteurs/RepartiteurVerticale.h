#ifndef REPARTITEURVERTICALE__H
#define REPARTITEURVERTICALE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Repartiteur.h"



namespace gui {



class RepartiteurVerticale : public gui::Repartiteur {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /// \param racine
    /////////////////////////////////////////////////
    RepartiteurVerticale (Gadget* racine);

    virtual void repartir (std::vector<std::shared_ptr<Gadget>> groupe);


}; // fin class RepartiteurVerticale

} // fin namespace gui

#endif
