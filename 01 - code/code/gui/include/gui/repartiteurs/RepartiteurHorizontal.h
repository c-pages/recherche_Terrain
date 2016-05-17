#ifndef REPARTITEURHORIZONTAL__H
#define REPARTITEURHORIZONTAL__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Repartiteur.h"



namespace gui {



class RepartiteurHorizontal : public gui::Repartiteur {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par d�faut.
    ///
    /// \param racine
    /////////////////////////////////////////////////
    RepartiteurHorizontal ( Gadget* racine );

    virtual void repartir (std::vector<std::shared_ptr<Gadget>> groupe);


}; // fin class RepartiteurHorizontal

} // fin namespace gui

#endif
