#ifndef REPARTITEUR__H
#define REPARTITEUR__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>

#include "interfaces/Gadget.h"


namespace gui {



class Repartiteur {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////


public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    Repartiteur ( Gadget* racine );

    virtual void repartir ( std::vector<std::shared_ptr<Gadget>> groupe ){};

    ///< Definir m_espacement
    void setEspacement( sf::Vector2i val ){ m_espacement = val; };

    ///< Acceder à m_espacement
    sf::Vector2i getEspacement () const { return m_espacement; };


/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:
    sf::Vector2i m_espacement;    ///<
    Gadget*         m_racine;
}; // fin class Repartiteur

} // fin namespace gui

#endif
