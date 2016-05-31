#ifndef TERRAIN__H
#define TERRAIN__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>



namespace jeu {

class Etage;


/////////////////////////////////////////////////
/// \brief Le terrain est le champs d'�volution des fourmis et autres �l�ments du biome. Compos� de plusieurs �tages ( 2? ou 3? ), il est repr�sent� en 2D avec une profondeur repr�sentant les �tages. Le "tilemap' est au niveau du pixel.
///
/////////////////////////////////////////////////
class Terrain : public sf::NonCopyable, public sf::Drawable {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
    ///< Definir m_indexEtageCourant
    void setIndexEtageCourant( std::size_t val ){ m_indexEtageCourant = val; };

    ///< Acceder � m_indexEtageCourant
    std::size_t getIndexEtageCourant () const { return m_indexEtageCourant; };

    ///< Definir m_taille
    void setTaille( sf::Vector2i val ){ m_taille = val; };

    ///< Acceder � m_taille
    sf::Vector2i getTaille () const { return m_taille; };

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par d�faut.
    ///
    /////////////////////////////////////////////////
    Terrain ();

    /////////////////////////////////////////////////
    /// \brief Gen�re les differents �tages du terrain.
    ///
    /// \param seed		 Le seed avec lequel generer le terrain.
    /// \param nbrEtages		 le nombre d'�tage que comportera le terrain.
    /////////////////////////////////////////////////
    void generer (int seed, unsigned int nbrEtages = 3);

    /////////////////////////////////////////////////
    /// \brief Vide la liste des �tages, vide le terrain.
    ///
    /////////////////////////////////////////////////
    void vider ();

    /////////////////////////////////////////////////
    /// \brief La fonction de dessin SFML. Dessine l'�tage courant.
    ///
    /// \param target		 
    /// \param states		 
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    std::vector<std::unique_ptr<Etage>> m_etages;    ///< Les diff�rents etages composants le terrain.    
    std::size_t m_indexEtageCourant;    ///< L'index dans m_etages de l'�tage actuellement affich�.     
    sf::Vector2i m_taille;    ///< La taille du terrain, en pixels.     
    sf::Shader m_shaderGrille;    ///< Le shader dessinant la grille sur les parties 'sol' du terrain.    
    sf::Shader m_shaderHachures;    ///< Le shader dessinant les hachures sur les parties 'terre' du terrain.    
    sf::Shader m_shaderOmbre;    ///< Le shader dessinant les ombres ('terre', v�g�tation ...)  sur les parties 'sol' du terrain. /todo voir pour g�rer �a en fonction du mouvement d'un soleil, pour repr�senter un cycle jour/nuit)    
    sf::Shader m_shaderAO;    ///< Le shader simulant un AO ('terre', v�g�tation ...) sur les parties 'sol' du terrain.    
    sf::Color m_couleurSol;    ///< La couleur du sol.    
    sf::Color m_couleurTerre;    ///< La couleur de la terre    
    sf::Color m_couleurOmbres;    ///< La couleur des ombres.    
    sf::Color  m_couleurAO;    ///< La couleur de l'Ambient occlusion.    

}; // fin class Terrain

} // fin namespace jeu

#endif
