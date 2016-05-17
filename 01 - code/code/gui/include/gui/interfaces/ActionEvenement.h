#ifndef ACTIONEVENEMENT__H
#define ACTIONEVENEMENT__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <map>
#include <functional>

#include "Gadget.h"

#include <Enums.h>

namespace gui {


/////////////////////////////////////////////////
/// \brief Classe abstraite qui g�re les �venements claviers et souris
///
/////////////////////////////////////////////////
class ActionEvenement : public Gadget {


/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////
public:
    using FctnAction = std::function<void()>;    ///< le type de fonction associ� aux declenchements des evenements.


/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////
public:


    ActionEvenement();


    /////////////////////////////////////////////////
    /// \brief Cr�er une nouvelle liaison entre un evenement souris  et une fonction lambda.
    ///
    /// \param evenement		 evenement souris
    /// \param fonction		 Le fonction � d�clencher.
    /////////////////////////////////////////////////
    void lier  (Evenement evenement, FctnAction fonction);

    /////////////////////////////////////////////////
    /// \brief Supprime une liaison entre un evenement souris  et une fonction lambda.
    ///
    /// \param evenement		 L'�venement � supprimer
    /////////////////////////////////////////////////
    void delier (Evenement evenement);

    /////////////////////////////////////////////////
    /// \brief D�clencher un �venement souris (les �venement claviers sont g�rer.
    ///
    /// \param evenement
    /////////////////////////////////////////////////
    virtual void declencher (Evenement evenement);

protected:
    bool    existe ( Evenement evenement );

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    std::map < Evenement , FctnAction > m_evenementsSouris;    ///< la liste des evenements souris enregistr�s.

}; // fin class ActionEvenement

} // fin namespace gui

#endif
