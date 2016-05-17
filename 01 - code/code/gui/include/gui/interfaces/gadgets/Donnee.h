#ifndef DONNEE__H
#define DONNEE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/ActionEvenement.h"


namespace gui {


/////////////////////////////////////////////////
/// \brief Classe Mod�le permetant de g�rer une valeur (bool, int, float, string)
///  abstraite pour gadgets de type btnACocher, spinner, ...
///
/////////////////////////////////////////////////
template<typename T>
class Donnee : public gui::ActionEvenement {

/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////
public:

    /////////////////////////////////////////////////
    /// \brief Acceder � la valeur
    ///
    /////////////////////////////////////////////////
    virtual T getValeur()
    { return m_valeur; };

    /////////////////////////////////////////////////
    /// \brief D�finir la valeur
    ///
    /////////////////////////////////////////////////
    virtual void setValeur( T val )
    {   m_valeur = val; demanderActualisation(); };

    virtual bool        estInteractif() { return true; }; ///< \todo voir si on peut faire mieux ...

protected:
    T   m_valeur;   ///< La valeur.

}; // fin class Donnee

} // fin namespace gui

#endif
