#ifndef ACTIONCLAVIER__H
#define ACTIONCLAVIER__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <map>
#include <SFML/Graphics.hpp>
#include <functional>



namespace gui {



/////////////////////////////////////////////////
/// \brief Classe abstraite qui gère les évenements clavier.
///
/////////////////////////////////////////////////
class ActionClavier {

public:
/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////
    using FctnAction = std::function<void()>;    ///< le type de fonction associé aux declenchements des evenements.


/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Créer une nouvelle liaison entre un evenement clavier  et une fonction lambda.
    ///
    /// \param touche		 la touche du clavier.
    /// \param fonction		 Le fonction à déclencher.
    /////////////////////////////////////////////////
    void lier ( sf::Keyboard::Key  touche, FctnAction fonction);

    /////////////////////////////////////////////////
    /// \brief Supprime une liaison entre un evenement clavier  et une fonction lambda.
    ///
    /// \param touche
    /////////////////////////////////////////////////
    void delier ( sf::Keyboard::Key   touche);


    /////////////////////////////////////////////////
    /// \brief Vérifie s'il a des actions a lancer suite à un évenemnt clavier.
    ///
    /// \param evenement
    /////////////////////////////////////////////////
    void traiterEvenementsClavier (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Supprime une liaison entre un evenement clavier  et une fonction lambda.
    ///
    /// \param touche
    /////////////////////////////////////////////////
    void viderLiaisons ( );


protected:


/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    std::map < sf::Keyboard::Key  , FctnAction > m_evenementsClavier;    ///<  la liste des evenements claviers enregistrés.

}; // fin class ActionClavier

} // fin namespace gui

#endif
