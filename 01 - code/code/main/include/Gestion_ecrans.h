#ifndef GESTION_ECRANS_H
#define GESTION_ECRANS_H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <Ecran.h>

namespace app{
/////////////////////////////////////////////////
/// \brief  Gestionnaire des �crans
///
/////////////////////////////////////////////////
class Gestion_ecrans
{
public:
    /////////////////////////////////////////////////
    /// \brief Ajouter un �cran sur la pile
    ///
    /// \param ecran Un nouvel \e Ecran � ajouter � la pile active.
    /// \return Rien.
    ///
    /////////////////////////////////////////////////
    void    ajouter ( Ecran* ecran );

    /////////////////////////////////////////////////
    /// \brief Retirer l'�cran du dessus de la pile.
    ///
    /// \return Rien.
    ///
    /////////////////////////////////////////////////
    void    retirer ();

    /////////////////////////////////////////////////
    /// \brief Retirer tout les �crans de la pile.
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
    /// \brief Changer d'�cran
    ///
    /// On retire l'�cran en cours, puis on ajoute le nouveau.
    ///
    /// \param ecran le nouvel \e Ecran � mettre � la place du dernier de la pile.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void    changer ( Ecran* ecran );

    /////////////////////////////////////////////////
    /// \brief Renvoie l'�cran courant, celui au top de la \e _pile
    ///
    /// \return L'�cran courant.
    ///
    /////////////////////////////////////////////////
    Ecran*    courant ();

    /////////////////////////////////////////////////
    /// \brief G�re les �venements  des �crans actifs.
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void traiter_evenements (sf::Event event );

    /////////////////////////////////////////////////
    /// \brief Actualiser les �l�ments.
    ///
    /// Actualiser les diff�rents �l�ments du ou des �crans actifs.
    /// \param deltaT          Un \e float qui indique le delta du temps �coul� depuis la derni�re actualisation.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void actualiser ( float deltaT );

    /////////////////////////////////////////////////
    /// \brief Rendre les �crans de la pile.
    ///
    /// Dessine les diff�rents �l�ments du ou des �crans de la pile.
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void    dessiner ();

private:

    /////////////////////////////////////////////////
    //  Membres
    /////////////////////////////////////////////////
    std::vector<Ecran*>     m_pile;  ///< La pile des �crans actifs.

}; // Gestion_ecrans
}; // namespace app


#endif // GESTION_ECRANS_H


////////////////////////////////////////////////////////////
/// \class app::Gestion_ecrans
/// \ingroup application
///
/// G�re les diff�rents �crans de l'application.
/// C'est lui qui porte les �crans actifs du programme.
/// qui permet de passer d'un �cran � l'autre, etc.
/// \see app::Ecran
///
////////////////////////////////////////////////////////////




