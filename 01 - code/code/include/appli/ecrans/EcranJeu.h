#ifndef ECRANJEU_H
#define ECRANJEU_H

/////////////////////////////////////////////////
//  Headers
/////////////////////////////////////////////////
#include    <SFML/Graphics.hpp>
#include    <appli/Ecran.h>
#include    <appli/Application.h>

#include    "jeu/Jeu.h"

namespace app {

/////////////////////////////////////////////////
/// \class  EcranJeu
/// \brief  Ecran de jeu
///
/////////////////////////////////////////////////
class EcranJeu : public Ecran
{
public:

    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    EcranJeu( Gestion_ecrans&  pileEcrans , Contexte contexte );

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

    jeu::Jeu            m_jeu;                  /// le jeu

    sf::RectangleShape  m_fond;                 ///< Le shape SFML du fond de l'écran.
    std::shared_ptr<gui::Gui>   m_interface;
    std::shared_ptr<gui::Label> m_lblCoordSouris;

    // pour le drag de la souris
    bool            m_drag                = false;
    sf::Vector2f    m_posVueOrigine       = {0,0};
    sf::Vector2i    m_posSourisOrigine    = {0,0};


}; // fin EcranJeu
}; // fin app
#endif // ECRANJEU_H
