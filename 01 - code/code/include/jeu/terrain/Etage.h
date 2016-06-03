#ifndef ETAGE__H
#define ETAGE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>

#include "jeu/vegetation/Plante.h"

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
    Etage ( Terrain* terrain, sf::Vector2i taille , int index );


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
    /// \brief Applique le renderTexture à la texture
    ///
    /////////////////////////////////////////////////
    void appliquerTexture ( );






//    /////////////////////////////////////////////////
//    void genererPlantations ( int nbrePlantes = 20 ) ;




    /////////////////////////////////////////////////
    /// \brief Savoir si le pixel est libre ou occupé
    ///
    /// \param pos la position du pixel à tester
    /// \param rayon le rayon autour du pixel ou étendre le test, defaut = 0, juste le pixel à la pos sera tester
    /// \return true si libre, false occupé
    ///
    /////////////////////////////////////////////////
    bool estLibre ( sf::Vector2i pos, int rayon = 0 ) const;

    /////////////////////////////////////////////////
    /// \brief Savoir si le pixel est libre ou occupé
    ///
    /// \param pos la position du pixel à tester
    /// \param rayon le rayon autour du pixel ou étendre le test, defaut = 0, juste le pixel à la pos sera tester
    /// \return true si libre, false occupé
    ///
    /////////////////////////////////////////////////
    bool estDeLaTerre ( sf::Vector2i pos, int rayon = 0 ) const;

    /////////////////////////////////////////////////
    bool estCoupe () const;

    /////////////////////////////////////////////////
    void setCourant ( bool val = true );

    /////////////////////////////////////////////////
    bool estCourant () const;

    /////////////////////////////////////////////////
    /// \brief
    /// \return pointeur vers etage dessous
    ///
    /////////////////////////////////////////////////
    std::shared_ptr<Etage> getEtageDessous()const;


    /////////////////////////////////////////////////
    /// \brief
    /// \return pointeur vers etage dessus
    ///
    /////////////////////////////////////////////////
    std::shared_ptr<Etage> getEtageDessus()const;



//    /////////////////////////////////////////////////
//    /// \brief Définir l'origin pour les shaders du terrain
//    /// Sert à recaller l'origine des hachures et du quadrillage des shaders du terrain.
//    ///
//    /// \param pos la nouvelle origine des shaders.
//    /////////////////////////////////////////////////
//    void setShadersOrigin ( sf::Vector2f pos ){
//        m_shaderGrille.setParameter( "origin", pos );
//        m_shaderHachures.setParameter( "origin", pos );
//    };









    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments du jeu.
    ///
    /// \param deltaT		 Temps écoulé depuis la dernière actualisation. ( par défaut = 0: Actualise sans tenir compte du temps ecoulé)
    /////////////////////////////////////////////////
    void actualiser (sf::Time deltaT = sf::Time::Zero );

    /////////////////////////////////////////////////
    /// \brief La fonction de dessin SFML. Dessine l'étage courant.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    int                 m_index;
    Terrain*            m_terrain;          ///<  le terrain parent.

//    std::vector<std::shared_ptr<Plante>>    m_plantes;


//    sf::Image           m_mapCollision;     ///< Image N&B representant l'occupation de l'étage.
//    sf::Image           m_mapPheromones;    ///< La map de phéromones, les fourmis

    sf::Image           m_imageTerre;           ///< La map du sol, 3 couleurs : couleur sol (case libre), couleur terre(pixel occupé), transparent( case vide, vue sur étage du dessous).

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
//    sf::Shader      m_shaderGrille;     ///< Le shader dessinant la grille sur les parties 'sol' du terrain.
//    sf::Shader      m_shaderHachures;   ///< Le shader dessinant les hachures sur les parties 'terre' du terrain.
    sf::Shader      m_shaderOmbre;      ///< Le shader dessinant les ombres ('terre', végétation ...)  sur les parties 'sol' du terrain. /todo voir pour gérer ça en fonction du mouvement d'un soleil, pour représenter un cycle jour/nuit)
    sf::Shader      m_shaderAO;         ///< Le shader simulant un AO ('terre', végétation ...) sur les parties 'sol' du terrain.

    /// Les couleurs /////
    sf::Color       m_couleurSol;       ///< La couleur du sol.
    sf::Color       m_couleurTerre;     ///< La couleur de la terre
    sf::Color       m_couleurOmbres;    ///< La couleur des ombres.
    sf::Color       m_couleurAO;        ///< La couleur de l'Ambient occlusion.

}; // fin class Etage





/////////////////////////////////////////////////
/// \brief Etage vide
///
/////////////////////////////////////////////////
class EtageVide : public Etage {
    public:

    EtageVide( Terrain* terrain, sf::Vector2i taille , int index) : Etage ( terrain, taille , index) {};


    /////////////////////////////////////////////////
    /// \brief La fonction de dessin SFML. Dessine l'étage courant.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const{};

};



} // fin namespace jeu






#endif
