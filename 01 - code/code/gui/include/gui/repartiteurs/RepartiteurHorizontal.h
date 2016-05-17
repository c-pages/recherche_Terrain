#ifndef REPARTITEURHORIZONTAL__H
#define REPARTITEURHORIZONTAL__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Repartiteur.h"



namespace gui {



class RepartiteurHorizontal : public gui::Repartiteur {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /// \param racine
    /////////////////////////////////////////////////
    RepartiteurHorizontal ( Gadget* racine );

    virtual void repartir (std::vector<std::shared_ptr<Gadget>> groupe);


}; // fin class RepartiteurHorizontal

} // fin namespace gui

#endif
