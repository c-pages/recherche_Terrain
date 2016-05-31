#ifndef ETAGE__H
#define ETAGE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>



namespace jeu {



/////////////////////////////////////////////////
/// \brief Un seul étage est visible à la fois. Composé de sol, terre et vide. Chaque étage gère les collisions. 

///
/////////////////////////////////////////////////
class Etage : public sf::NonCopyable, public sf::Drawable {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    Etage ();



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    sf::Image m_mapCollision;    ///< Image N&B representant l'occupation de l'étage.     
    sf::Image m_mapPheromones;    ///< La map de phéromones, les fourmis     
    sf::Image m_mapSol;    ///< La map du sol, 3 couleurs : couleur sol (case libre), couleur terre(pixel occupé), transparent( case vide, vue sur étage du dessous).    
    sf::RectangleShape m_shapeSol;    ///< Le shape à dessiner pour représenter l'étage.    

}; // fin class Etage

} // fin namespace jeu

#endif
