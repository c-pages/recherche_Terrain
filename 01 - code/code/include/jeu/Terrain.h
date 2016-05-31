#ifndef TERRAIN__H
#define TERRAIN__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>


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
    void setEtageCourant( int val );

    ///< Acceder � m_indexEtageCourant
    int getEtageCourant () const { return m_etageCourant; };

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
    /// \param tailleCarte		 la taille du terrain en pixels.
    /// \param nbrEtages		 le nombre d'�tage que comportera le terrain.
    /////////////////////////////////////////////////
    void generer ( int seed, sf::Vector2i tailleCarte, unsigned int nbrEtages = 3 );

    /////////////////////////////////////////////////
    /// \brief Vide la liste des �tages, vide le terrain.
    ///
    /////////////////////////////////////////////////
    void vider ();







    /////////////////////////////////////////////////
    /// \brief D�finir l'origin pour les shaders du terrain
    /// Sert � recaller l'origine des hachures et du quadrillage des shaders du terrain.
    ///
    /// \param pos la nouvelle origine des shaders.
    /////////////////////////////////////////////////
    void setShadersOrigin ( sf::Vector2f pos );



    /////////////////////////////////////////////////
    /// \brief Vide la liste des �tages, vide le terrain.
    ///
    /////////////////////////////////////////////////
    void dessinerRond ( sf::Vector2i centre, sf::Color couleur, sf::RenderTexture& renderTexture );






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
    std::vector<std::shared_ptr<Etage>>     m_etages;               ///< Les diff�rents etages composants le terrain.
    std::size_t                             m_nbreEtages;           ///< L'index dans m_etages de l'�tage actuellement affich�.
    int                                     m_etageCourant;         ///< L'index dans m_etages de l'�tage actuellement affich�.
    sf::Vector2i                            m_taille;               ///< La taille du terrain, en pixels.

    int                                     m_ecartMin;             ///< L'ecart entre les ronds pour le dessin


//    sf::Image               m_image;                ///< la bitmap
//    const sf::Texture*      m_texture;              ///< la texture
//    sf::RenderTexture       m_renderTexture;        ///< le render ou dessiner la map
//    sf::RenderTexture       m_renderTextureAO;      ///< le render ou dessiner la map d'AO
//
    /// Les shapes /////
    sf::RectangleShape      m_shapeProfondeur;           ///< le shape qui recoit le terrain
//    sf::RectangleShape      m_shapeTerre;           ///< le shape qui recoit le terrain
//    sf::RectangleShape      m_shapeOmbreTerre;      ///< le shape qui recoit le terrain
//    sf::RectangleShape      m_shapeAO;              ///< le shape qui recoit le terrain
//    sf::RectangleShape      m_shapesol;             ///< le shape qui recoit le terrain

    /// Les shaders /////
    sf::Vector2f    m_posOrigine;
//
    sf::Shader      m_shaderGrille;     ///< Le shader dessinant la grille sur les parties 'sol' du terrain.
    sf::Shader      m_shaderHachures;   ///< Le shader dessinant les hachures sur les parties 'terre' du terrain.
    sf::Shader      m_shaderOmbre;      ///< Le shader dessinant les ombres ('terre', v�g�tation ...)  sur les parties 'sol' du terrain. /todo voir pour g�rer �a en fonction du mouvement d'un soleil, pour repr�senter un cycle jour/nuit)
    sf::Shader      m_shaderAO;         ///< Le shader simulant un AO ('terre', v�g�tation ...) sur les parties 'sol' du terrain.

    /// Les couleurs /////
    sf::Color       m_couleurSol;       ///< La couleur du sol.
    sf::Color       m_couleurTerre;     ///< La couleur de la terre
    sf::Color       m_couleurOmbres;    ///< La couleur des ombres.
    sf::Color       m_couleurAO;        ///< La couleur de l'Ambient occlusion.

}; // fin class Terrain

} // fin namespace jeu

#endif
