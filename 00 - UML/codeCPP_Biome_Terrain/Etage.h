#ifndef ETAGE__H
#define ETAGE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>



namespace jeu {



/////////////////////////////////////////////////
/// \brief Un seul �tage est visible � la fois. Compos� de sol, terre et vide. Chaque �tage g�re les collisions. 

///
/////////////////////////////////////////////////
class Etage : public sf::NonCopyable, public sf::Drawable {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par d�faut.
    ///
    /////////////////////////////////////////////////
    Etage ();



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    sf::Image m_mapCollision;    ///< Image N&B representant l'occupation de l'�tage.     
    sf::Image m_mapPheromones;    ///< La map de ph�romones, les fourmis     
    sf::Image m_mapSol;    ///< La map du sol, 3 couleurs : couleur sol (case libre), couleur terre(pixel occup�), transparent( case vide, vue sur �tage du dessous).    
    sf::RectangleShape m_shapeSol;    ///< Le shape � dessiner pour repr�senter l'�tage.    

}; // fin class Etage

} // fin namespace jeu

#endif
