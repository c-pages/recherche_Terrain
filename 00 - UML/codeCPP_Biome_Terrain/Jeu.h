#ifndef JEU__H
#define JEU__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>



namespace jeu {

class Terrain;


/////////////////////////////////////////////////
/// \brief La classe g�n�ral du jeu, g�re le jeu de mani�re global.
///
/////////////////////////////////////////////////
class Jeu : public sf::NonCopyable, public sf::Drawable {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
public:
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
    Terrain m_terrain;    ///< Le terrain de la partie en cours.    

}; // fin class Jeu

} // fin namespace jeu

#endif