#ifndef ECRAN_H
#define ECRAN_H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

namespace app
{

class Application;

/////////////////////////////////////////////////
/// \brief La classe virtuelle communues aux écrans.
///
/////////////////////////////////////////////////
class Ecran
{
public:

    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    Ecran( Application*  appli );

    /////////////////////////////////////////////////
    /// \brief Destructeur virtuel
    ///
    /////////////////////////////////////////////////
    virtual ~Ecran();

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
    virtual     void actualiser ( float deltaT ) =0;

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
    Application*    m_appli;    ///< La classe Apllication parent.

    sf::View        m_vueJeu;   ///<
    sf::View        m_vueGUI;   ///<

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
