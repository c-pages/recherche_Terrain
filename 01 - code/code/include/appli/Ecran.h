#ifndef ECRAN_H
#define ECRAN_H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <iostream>

namespace app
{
    /////////////////////////////////////////////////
    /// \brief les différents écrans que l'on va trouver dans l'application
    ///
    /////////////////////////////////////////////////
    namespace Ecrans {
       enum ID {
            Accueil,
            Pause,
            Options,
            Jeu,

            Vide
        };
    }


class Application;
class Gestion_ecrans;

/////////////////////////////////////////////////
/// \brief La classe virtuelle communues aux écrans.
///
/////////////////////////////////////////////////
class Ecran
{
public:

    ///< le context (la fenetre SFML, les textures, polices, ... ) associés aux Etats (intro, menu ...)
    struct Contexte
    {
        Contexte(    sf::RenderWindow&   fenetreSFML
//                ,   Niveau *            niveau
//                ,   TextureHolder*		textures;
//                ,   FontHolder*			fonts;
//                ,   Player*				player;
                )
                : fenetre ( &fenetreSFML ) {};

        sf::RenderWindow*	    fenetre;
        //Niveau                mNiveau;    ///<
        //TextureHolder*		textures;
        //FontHolder*			fonts;
        //Player*				player;
    };





    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    Ecran( Gestion_ecrans&  pileEcrans , Contexte contexte );

    /////////////////////////////////////////////////
    /// \brief Destructeur virtuel
    ///
    /////////////////////////////////////////////////
    virtual ~Ecran();

    /////////////////////////////////////////////////
    /// \brief definir l'état de la pause
    ///
    /// \param pause t
    /// \return rien
    ///
    /////////////////////////////////////////////////
    void setPause ( bool pause = true ) {
        m_pause = pause;
        std::cout << "PAUSE : " << m_pause;
    };

    /////////////////////////////////////////////////
    /// \brief acceder à l'état de la pause
    ///
    /// \param pause t
    /// \return rien
    ///
    ////////////////////////////////////////////////
    bool estEnPause ( ) { return m_pause; };








    /////////////////////////////////////////////////
    /// \brief ajouter un écran
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void ajouterEcran( Ecrans::ID ecranID );

    /////////////////////////////////////////////////
    /// \brief retirer un écran
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void retirerEcran( );

    /////////////////////////////////////////////////
    /// \brief vider les écrans
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void viderEcrans( );













    /////////////////////////////////////////////////
    /// \brief Gère les entrées claviers, souris, fenetre ...
    ///
    /// \param event evenement SFML a dispatcher
    /// \return rien
    ///
    /////////////////////////////////////////////////
    virtual     void traiter_evenements ( const sf::Event& event ) =0;

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments.
    ///
    /// Actualiser les différents éléments du ou des écrans actifs.
    ///
    /// \param deltaT          Un \e float qui indique le delta du temps écoulé depuis la dernière actualisation.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    virtual     void actualiser ( sf::Time deltaT ) =0;

    /////////////////////////////////////////////////
    /// \brief Rendre les éléments.
    ///
    /// Dessiner les différents éléments du ou des écrans actifs.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    virtual     void dessiner  ( ) =0;

protected:

/////////////////////////////////////////////////
// Les membres
/////////////////////////////////////////////////
    sf::View            m_vuePrincipale;    ///< La vue principale du jeu
    Contexte            m_contexte;         ///<  Le contexte de l'écran (la fenetre SFML, textures, polices...) \todo intégrer les textures et polices dans le contexte
    Gestion_ecrans*     m_pileEcrans ;      ///<  Le gestionnaire des écrans
    bool                m_pause = false;    ///<  La pause stope l'actualisation et le traitement des évènements de l'écrans mais pas l'affichage.

}; // fin Ecran
}; // fin app
#endif // ECRAN_H



////////////////////////////////////////////////////////////
/// \class app::Ecran
/// \ingroup application
///
/// app::Ecran la classe de base des écrans.
/// Les écrans peuvent se superposer (par exemple l'écran pause-option avec en dessous l'écran
/// jeu en pause).
///
/// \see app::EcranDemo
///
////////////////////////////////////////////////////////////
