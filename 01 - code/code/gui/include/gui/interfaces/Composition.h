#ifndef COMPOSITION__H
#define COMPOSITION__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>



namespace gui {

class Gadget;

/////////////////////////////////////////////////
/// \brief Gestion des gadgets qui compose l'interface de ce gadget, parent (GOF4: Filiation)
///
/////////////////////////////////////////////////
class Composition {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    virtual void traiterEvenementsComposants (const sf::Event& evenement);

    /////////////////////////////////////////////////
    /// \brief Ajouter un gadget à la liste de gadgets enfant.
    ///
    /// \param enfant		 L'enfant à ajouter.
    /////////////////////////////////////////////////
    virtual void ajouterComposant (std::shared_ptr<Gadget> enfant);

    /////////////////////////////////////////////////
    /// \brief Retirer un enfant de la liste des enfants de ce gadget sans le supprimer.
    ///
    /// \param enfant		 L'enfant à retirer de la liste des enfants.
    /////////////////////////////////////////////////
    virtual void retirerComposant (std::shared_ptr<Gadget> enfant);

    /////////////////////////////////////////////////
    /// \brief Mettre au dessus des autres gadgets ( mouvements de la liste des enfants).
    ///
    /// \param gadget		 le pointeur vers le gadget à mettre au dessus des autres parmis m_enfants.
    /////////////////////////////////////////////////
    virtual void mettre_composantAuDessus (std::shared_ptr<Gadget> gadget);

    std::shared_ptr<Gadget> testerSurvolComposants (sf::Vector2i position);

    /////////////////////////////////////////////////
    /// \brief Dessiner les enfants du gadget.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    void dessinerComposant (sf::RenderTarget& target, sf::RenderStates states) const;


    void actualiserComposants ();
//    void demanderActuaBoundsComposants ();

    std::vector<std::shared_ptr<Gadget>> getComposants() { return m_composants; } ;

protected:
/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:
    std::vector<std::shared_ptr<Gadget>> m_composants;    ///< Les enfants du gadget.

}; // fin class Composant

} // fin namespace gui

#endif
