#ifndef JEU__H
#define JEU__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

#include "jeu/Terrain.h"
#include "appli/Ecran.h"

namespace jeu {



/////////////////////////////////////////////////
/// \brief La classe g�n�ral du jeu, g�re le jeu de mani�re global.
///
/////////////////////////////////////////////////
class Jeu : public sf::NonCopyable, public sf::Drawable {


/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////
public:




    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    Jeu (app::Ecran::Contexte contexte);


    /////////////////////////////////////////////////
    /// \brief D�marre une nouvelle partie.
    ///
    /// \param seed		 Le seed permet de d�finir le seed du noise et ainsi d'aoptenir tojours le meme terrain avec le m�me seed. (cf. Minecraft)
    /////////////////////////////////////////////////
    void demarrerPartie (int seed = 123456);

    /////////////////////////////////////////////////
    /// \brief Quitter la partie en cours (sans sauvegarde).
    ///
    /////////////////////////////////////////////////
    void quitterPartie ();

    /////////////////////////////////////////////////
    /// \brief Charger une partie precedement sauvegarder.
    ///
    /////////////////////////////////////////////////
    void chargerPartie ();

    /////////////////////////////////////////////////
    /// \brief Sauvegarder une partie.
    ///
    /////////////////////////////////////////////////
    void sauvegarderPartie ();






    /////////////////////////////////////////////////
    /// \brief acceder � la taille de la carte du jeu
    ///
    /// \return la taille de la carte de jeu en pixel
    /////////////////////////////////////////////////
    sf::Vector2i getTailleCarte () const { return m_tailleCarte; };



    /////////////////////////////////////////////////
    /// \brief Monter d'un �tage
    ///
    /////////////////////////////////////////////////
    void etageMonter ();

    /////////////////////////////////////////////////
    /// \brief Descendre d'un �tage
    ///
    /////////////////////////////////////////////////
    void etageDescendre ();



    /////////////////////////////////////////////////
    /// \brief test des trucs
    /// \param pos la nouvelle origine des shaders.
    /////////////////////////////////////////////////
    void test ( sf::Vector2i pos );


    /////////////////////////////////////////////////
    /// \brief D�finir l'origin pour les shaders du terrain
    /// Sert � recaller l'origine des hachures et du quadrillage des shaders du terrain.
    ///
    /// \param pos la nouvelle origine des shaders.
    /////////////////////////////////////////////////
    void setShadersOrigin ( sf::Vector2f pos )
    { m_terrain.setShadersOrigin ( pos ); };





    /////////////////////////////////////////////////
    /// \brief Actualiser les �l�ments du jeu.
    ///
    /// \param deltaT		 Temps �coul� depuis la derni�re actualisation. ( par d�faut = 0: Actualise sans tenir compte du temps ecoul�)
    /////////////////////////////////////////////////
    void actualiser (sf::Time deltaT = sf::Time::Zero );

    /////////////////////////////////////////////////
    /// \brief Traitement des �venemnts clavier et souris.
    ///
    /// \param evenement		 l'�venement � traiter.
    /////////////////////////////////////////////////
    void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief D�ssine tout les �l�ments graphiques n�cessaires (terrains, plantes, PJ, PNJ, interface... tout quoi).
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    app::Ecran::Contexte    m_contexte;         ///< Le contexte courant.
    sf::Vector2i            m_tailleCarte;      ///< La taille du terrain, en pixels.


    Terrain                 m_terrain;          ///< Le terrain de la partie en cours.

//    std::vector<shared_ptr<Plante>>     m_plantes;


}; // fin class Jeu

} // fin namespace jeu

#endif
