#ifndef ETAGE__H
#define ETAGE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>



namespace jeu {

class Terrain;


/////////////////////////////////////////////////
/// \brief Un seul étage est visible à la fois. Composé de sol, terre et vide. Chaque étage gère les collisions.
///
/////////////////////////////////////////////////
class Etage : public sf::NonCopyable, public sf::Drawable {

friend class Terrain;

/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    Etage ( Terrain* terrain, sf::Vector2i taille );


    /////////////////////////////////////////////////
    /// \brief accesseur texture
    ///
    /// \return la texture de l'étage
    /////////////////////////////////////////////////
    const sf::Texture* getTexture ();


    /////////////////////////////////////////////////
    /// \brief accesseur rendertexture
    ///
    /// \return le render texture de l'étage
    /////////////////////////////////////////////////
    sf::RenderTexture* getRenderTexture ();


    /////////////////////////////////////////////////
    /// \brief Définir l'origin pour les shaders du terrain
    /// Sert à recaller l'origine des hachures et du quadrillage des shaders du terrain.
    ///
    /// \param pos la nouvelle origine des shaders.
    /////////////////////////////////////////////////
    void setShadersOrigin ( sf::Vector2f pos ){
        m_shaderGrille.setParameter( "origin", pos );
        m_shaderHachures.setParameter( "origin", pos );
    };

    /////////////////////////////////////////////////
    /// \brief Applique le renderTexture à la texture
    ///
    /////////////////////////////////////////////////
    void appliquerTexture ( );

    /////////////////////////////////////////////////
    /// \brief La fonction de dessin SFML. Dessine l'étage courant.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

    void setCourant ( bool val = true ) {
        m_estCourant = val;
        if ( m_estCourant )
            m_shapeTerre.setFillColor( m_couleurTerre );
        else
            m_shapeTerre.setFillColor( m_couleurSol );
    };

    bool estCourant () const {return m_estCourant;};



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    Terrain*            m_terrain;          ///<  le terrain parent.

    sf::Image           m_mapCollision;     ///< Image N&B representant l'occupation de l'étage.
    sf::Image           m_mapPheromones;    ///< La map de phéromones, les fourmis

    sf::Image           m_mapSol;           ///< La map du sol, 3 couleurs : couleur sol (case libre), couleur terre(pixel occupé), transparent( case vide, vue sur étage du dessous).

    sf::Vector2i        m_taille;           ///< La taille du terrain, en pixels.

    bool                m_estCourant;       ///<  Si c'est l'étage courant

//    sf::Image               m_image;                ///< la bitmap
    sf::Texture             m_texture;              ///< la texture
    sf::RenderTexture       m_renderTexture;        ///< le render ou dessiner la map

    /// Les shapes /////
    sf::RectangleShape      m_shapeTerre;           ///< le shape qui recoit le terrain
    sf::RectangleShape      m_shapeOmbreTerre;      ///< le shape qui recoit le terrain
    sf::RectangleShape      m_shapeAO;              ///< le shape qui recoit le terrain
    sf::RectangleShape      m_shapesol;             ///< le shape qui recoit le terrain

    /// Les shaders /////
    sf::Shader      m_shaderGrille;     ///< Le shader dessinant la grille sur les parties 'sol' du terrain.
    sf::Shader      m_shaderHachures;   ///< Le shader dessinant les hachures sur les parties 'terre' du terrain.
    sf::Shader      m_shaderOmbre;      ///< Le shader dessinant les ombres ('terre', végétation ...)  sur les parties 'sol' du terrain. /todo voir pour gérer ça en fonction du mouvement d'un soleil, pour représenter un cycle jour/nuit)
    sf::Shader      m_shaderAO;         ///< Le shader simulant un AO ('terre', végétation ...) sur les parties 'sol' du terrain.

    /// Les couleurs /////
    sf::Color       m_couleurSol;       ///< La couleur du sol.
    sf::Color       m_couleurTerre;     ///< La couleur de la terre
    sf::Color       m_couleurOmbres;    ///< La couleur des ombres.
    sf::Color       m_couleurAO;        ///< La couleur de l'Ambient occlusion.

}; // fin class Etage

} // fin namespace jeu

#endif
