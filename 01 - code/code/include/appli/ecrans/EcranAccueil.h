#ifndef ECRANACCUEIL_H
#define ECRANACCUEIL_H

/////////////////////////////////////////////////
//  Headers
/////////////////////////////////////////////////
#include    <SFML/Graphics.hpp>
#include    <appli/Ecran.h>
#include    <appli/Application.h>

#include    "gui/Gui.h"

namespace app {

/////////////////////////////////////////////////
/// \class  EcranAccueil
/// \brief  L'écran d'accueil affiche le menu de démarrage du jeu : Démarrer une partie, accéder au options, ou quitter l'application.
///
/////////////////////////////////////////////////
class EcranAccueil : public Ecran
{
public:

    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    EcranAccueil( Application* appli );

    /////////////////////////////////////////////////
    /// \brief Destructeur
    ///
    /////////////////////////////////////////////////
    ~EcranAccueil( );

private:
    /////////////////////////////////////////////////
    /// \brief La gestion des évènements utilisateurs.
    ///
    /// \details  Gère les entrées claviers, souris, fenetre ...
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    virtual     void traiter_evenements ( const sf::Event& event );

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments.
    ///
    /// \details Actualiser les différents éléments du ou des écrans actifs.
    /// \param   deltaT          Un \e sf::Time qui indique le delta du temps écoulé depuis la dernière actualisation.
    /// \return  Rien
    ///
    /////////////////////////////////////////////////
    virtual     void actualiser ( sf::Time deltaT );

    /////////////////////////////////////////////////
    /// \brief Rendre les éléments.
    ///
    /// Dessiner les différents éléments du ou des écrans actifs.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    virtual     void dessiner  ( );

    /////////////////////////////////////////////////
    /// \brief Fonction a supprimer
    ///
    /// juste là pour tester des machins bidules.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void test ();

    /////////////////////////////////////////////////
    /// \brief Initialisation de l'interface graphique.
    ///
    /// Creation des fenetres, boutons, menus... ...
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    virtual     void initGUI ();

private:

    /////////////////////////////////////////////////
    // Les membres
    /////////////////////////////////////////////////

    sf::View            m_vue;   ///< La vue SFML de l'écran.
    sf::RectangleShape  m_fond;  ///< Le shape SFML du fond de l'écran.

    std::shared_ptr<gui::Gui>      m_interface;


}; // fin EcranAccueil
}; // fin app
#endif // ECRANACCUEIL_H
