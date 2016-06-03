#ifndef PLANTE__H
#define PLANTE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>

namespace jeu {

class Etage;

/////////////////////////////////////////////////
/// \brief Une plante verte apporte de la nourriture aux fourmis et autres insectes du biome.
///
/////////////////////////////////////////////////
class Plante    : public sf::Transformable
                , public sf::NonCopyable
                , public sf::Drawable {



/////////////////////////////////////////////////
/// les composants
/////////////////////////////////////////////////
    struct Tronc {

    };


    struct Racine:    public sf::Transformable
                    , public sf::NonCopyable
                    , public sf::Drawable {

        Racine( Plante* plante );


        void pousser();

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

    private:
        sf::CircleShape     m_shape;    ///<
        Plante *            m_parent;   ///< la plante parent
        float               m_angle;
    };








/////////////////////////////////////////////////
/// les fonctions
/////////////////////////////////////////////////
public:


    Plante( std::shared_ptr<Etage>  etage );

    int getAge();






    void creerNouvelleRacine();












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
/// les membres
/////////////////////////////////////////////////
private:

    std::shared_ptr<Etage>  m_etageParent;

    sf::Text                m_texte;    ///< pour debug ou infos
    sf::CircleShape         m_shape;   ///<
    float                   m_age;
    float                   m_ageBack;

    std::vector<std::shared_ptr<Racine>>     m_racines;

}; // fin class Plante

} // fin namespace jeu

#endif
