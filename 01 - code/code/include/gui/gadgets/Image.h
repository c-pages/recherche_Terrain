﻿#ifndef IMAGE__H
#define IMAGE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gui/Gadget.h"
#include <SFML/Graphics.hpp>



namespace gui {



/////////////////////////////////////////////////
/// \brief Une simple image
///
///
/////////////////////////////////////////////////
class Image : public gui::Gadget {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    Image ( sf::Texture& texture );

    /////////////////////////////////////////////////
    /// \brief Définie l'image à afficher
    ///
    /// \param texure		 La texture à afficher. (bonne pratique : utiliser RAI (un manager de ressources))
    /////////////////////////////////////////////////
    void setTexture (sf::Texture& texture );

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments de l'interface.
    ///
    /// Ajuste la taille du shape à la taille du gadget 'm_taille'
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine tout les éléments de l'interface.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    sf::RectangleShape m_shape;    ///< Le shape à dessiner.

}; // fin class Image

} // fin namespace gui

#endif
