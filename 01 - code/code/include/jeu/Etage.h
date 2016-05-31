#ifndef ETAGE__H
#define ETAGE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>



namespace jeu {

class Terrain;


/////////////////////////////////////////////////
/// \brief Un seul �tage est visible � la fois. Compos� de sol, terre et vide. Chaque �tage g�re les collisions.
///
/////////////////////////////////////////////////
class Etage : public sf::NonCopyable, public sf::Drawable {

friend class Terrain;

/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par d�faut.
    ///
    /////////////////////////////////////////////////
    Etage ( Terrain* terrain, sf::Vector2i taille );


    /////////////////////////////////////////////////
    /// \brief accesseur texture
    ///
    /// \return la texture de l'�tage
    /////////////////////////////////////////////////
    const sf::Texture* getTexture ();


    /////////////////////////////////////////////////
    /// \brief accesseur rendertexture
    ///
    /// \return le render texture de l'�tage
    /////////////////////////////////////////////////
    sf::RenderTexture* getRenderTexture ();


    /////////////////////////////////////////////////
    /// \brief D�finir l'origin pour les shaders du terrain
    /// Sert � recaller l'origine des hachures et du quadrillage des shaders du terrain.
    ///
    /// \param pos la nouvelle origine des shaders.
    /////////////////////////////////////////////////
    void setShadersOrigin ( sf::Vector2f pos ){
        m_shaderGrille.setParameter( "origin", pos );
        m_shaderHachures.setParameter( "origin", pos );
    };

    /////////////////////////////////////////////////
    /// \brief Applique le renderTexture � la texture
    ///
    /////////////////////////////////////////////////
    void appliquerTexture ( );

    /////////////////////////////////////////////////
    /// \brief La fonction de dessin SFML. Dessine l'�tage courant.
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

    sf::Image           m_mapCollision;     ///< Image N&B representant l'occupation de l'�tage.
    sf::Image           m_mapPheromones;    ///< La map de ph�romones, les fourmis

    sf::Image           m_mapSol;           ///< La map du sol, 3 couleurs : couleur sol (case libre), couleur terre(pixel occup�), transparent( case vide, vue sur �tage du dessous).

    sf::Vector2i        m_taille;           ///< La taille du terrain, en pixels.

    bool                m_estCourant;       ///<  Si c'est l'�tage courant

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
    sf::Shader      m_shaderOmbre;      ///< Le shader dessinant les ombres ('terre', v�g�tation ...)  sur les parties 'sol' du terrain. /todo voir pour g�rer �a en fonction du mouvement d'un soleil, pour repr�senter un cycle jour/nuit)
    sf::Shader      m_shaderAO;         ///< Le shader simulant un AO ('terre', v�g�tation ...) sur les parties 'sol' du terrain.

    /// Les couleurs /////
    sf::Color       m_couleurSol;       ///< La couleur du sol.
    sf::Color       m_couleurTerre;     ///< La couleur de la terre
    sf::Color       m_couleurOmbres;    ///< La couleur des ombres.
    sf::Color       m_couleurAO;        ///< La couleur de l'Ambient occlusion.

}; // fin class Etage

} // fin namespace jeu

#endif
