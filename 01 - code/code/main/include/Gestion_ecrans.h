#ifndef GESTION_ECRANS_H
#define GESTION_ECRANS_H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <Ecran.h>

namespace app{
/////////////////////////////////////////////////
/// \brief  Gestionnaire des écrans
///
/////////////////////////////////////////////////
class Gestion_ecrans
{
public:
    /////////////////////////////////////////////////
    /// \brief Ajouter un écran sur la pile
    ///
    /// \param ecran Un nouvel \e Ecran à ajouter à la pile active.
    /// \return Rien.
    ///
    /////////////////////////////////////////////////
    void    ajouter ( Ecran* ecran );

    /////////////////////////////////////////////////
    /// \brief Retirer l'écran du dessus de la pile.
    ///
    /// \return Rien.
    ///
    /////////////////////////////////////////////////
    void    retirer ();

    /////////////////////////////////////////////////
    /// \brief Retirer tout les écrans de la pile.
    ///
    /// \return Rien.
    ///
    /////////////////////////////////////////////////
    void    vider ();

    /////////////////////////////////////////////////
    /// \brief Demande si il y a encore des ecrans dans la pile
    ///
    /// \return bool true si vide.
    ///
    /////////////////////////////////////////////////
    bool    estVide ();

    /////////////////////////////////////////////////
    /// \brief Changer d'écran
    ///
    /// On retire l'écran en cours, puis on ajoute le nouveau.
    ///
    /// \param ecran le nouvel \e Ecran à mettre à la place du dernier de la pile.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void    changer ( Ecran* ecran );

    /////////////////////////////////////////////////
    /// \brief Renvoie l'écran courant, celui au top de la \e _pile
    ///
    /// \return L'écran courant.
    ///
    /////////////////////////////////////////////////
    Ecran*    courant ();

    /////////////////////////////////////////////////
    /// \brief Gère les évenements  des écrans actifs.
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void traiter_evenements (sf::Event event );

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments.
    ///
    /// Actualiser les différents éléments du ou des écrans actifs.
    /// \param deltaT          Un \e float qui indique le delta du temps écoulé depuis la dernière actualisation.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void actualiser ( sf::Time deltaT );

    /////////////////////////////////////////////////
    /// \brief Rendre les écrans de la pile.
    ///
    /// Dessine les différents éléments du ou des écrans de la pile.
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void    dessiner ();

private:

    /////////////////////////////////////////////////
    //  Membres
    /////////////////////////////////////////////////
    std::vector<Ecran*>     m_pile;  ///< La pile des écrans actifs.

}; // Gestion_ecrans
}; // namespace app


#endif // GESTION_ECRANS_H


////////////////////////////////////////////////////////////
/// \class app::Gestion_ecrans
/// \ingroup application
///
/// Gère les différents écrans de l'application.
/// C'est lui qui porte les écrans actifs du programme.
/// qui permet de passer d'un écran à l'autre, etc.
/// \see app::Ecran
///
////////////////////////////////////////////////////////////




