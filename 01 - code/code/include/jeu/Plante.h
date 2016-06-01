#ifndef PLANTE__H
#define PLANTE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>



namespace jeu {



/////////////////////////////////////////////////
/// \brief Une plante verte apporte de la nourriture aux fourmis et autres insectes du biome.
///
/////////////////////////////////////////////////
class Plante    : public sf::Transformable
                , public sf::NonCopyable
                , public sf::Drawable {

public:

    Plante();


    /////////////////////////////////////////////////
    /// \brief La fonction de dessin SFML. Dessine l'étage courant.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

/////////////////////////////////////////////////
/// les membres
/////////////////////////////////////////////////
private:


    sf::CircleShape     m_graine;


}; // fin class Plante

} // fin namespace jeu

#endif
