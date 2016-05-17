#ifndef ECRANJEU_H
#define ECRANJEU_H

/////////////////////////////////////////////////
//  Headers
/////////////////////////////////////////////////
#include    <SFML/Graphics.hpp>
#include    <Ecran.h>
#include    <Application.h>

#include    "Jeu.h"

namespace app {

/////////////////////////////////////////////////
/// \class  EcranJeu
/// \brief  Ecran de jeu
///
///
/////////////////////////////////////////////////
class EcranJeu : public Ecran
{
public:

    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    EcranJeu( Application* appli );

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
    /// \param   deltaT          Un \e float qui indique le delta du temps écoulé depuis la dernière actualisation.
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

    std::shared_ptr<gui::Interface>     m_interface;
    std::shared_ptr<gui::Fenetre>       m_fenetreOptions;

//    std::shared_ptr<gui::Interface>     m_interface;
    bool                                m_afficheEcranOptions = false;
    bool                                m_pause = false;

   // gui::Groupe*     m_gui;         ///< Le groupe de GUI du menu principal.
    jeu::Jeu            m_jeu;  /// le jeu

}; // fin EcranJeu
}; // fin app
#endif // ECRANJEU_H
