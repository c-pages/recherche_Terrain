#ifndef REPARTITEURVERTICALE__H
#define REPARTITEURVERTICALE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Repartiteur.h"



namespace gui {



class RepartiteurVerticale : public gui::Repartiteur {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par d�faut.
    ///
    /// \param racine
    /////////////////////////////////////////////////
    RepartiteurVerticale (Gadget* racine);

    virtual void repartir (std::vector<std::shared_ptr<Gadget>> groupe);


}; // fin class RepartiteurVerticale

} // fin namespace gui

#endif
