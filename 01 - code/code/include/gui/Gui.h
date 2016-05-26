#ifndef GUI__H
#define GUI__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <memory>
#include "gui/Gadget.h"
#include "gui/Fabrique.h"
#include "gui/gadgets/Calque.h"
#include <iostream>



/////////////////////////////////////////////////
/// \brief Le gui regroupe tout les élément consernant les interfaces graphiques
///
/////////////////////////////////////////////////
namespace gui {


/////////////////////////////////////////////////
/// \brief Le Gui gère l'ensemble des interactions homme-machine du jeu.
/// D'un coté un système de fenêtre, boutons basiques gérant les différents menus de l'appli.
/// De l'autre, le menu phéromones, système central de l'interaction du joueur avec ses fourmis.
///
/////////////////////////////////////////////////
class Gui : public Gadget {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur.
    ///
    /// \param fenetre		 La fenêtre SFML de l'application
    /////////////////////////////////////////////////
    Gui ( sf::RenderWindow* fenetre );


/////////////////////////////////////////////////
// Fonctions static
/////////////////////////////////////////////////

    /////////////////////////////////////////////////
    /// \brief accesseur de la position de la souris
    ///
    /////////////////////////////////////////////////
    static sf::Vector2i getSourisPosition ();

    /////////////////////////////////////////////////
    /// \brief accesseur de la fenetre SFML
    ///
    /////////////////////////////////////////////////
    static sf::RenderWindow* getFenetreSFML ();




    /////////////////////////////////////////////////
    /// \brief Definir m_parent. Ici ne fait rien car Gui est le root.
    ///
    /////////////////////////////////////////////////
    virtual void setParent( Gadget* val ){ std::cout << "ATTENTION: gui::Gui ne peut pas recevoir de parent !\n"; abort(); };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_parent. Ici ne fait rien car Gui est le root.
    ///
    /////////////////////////////////////////////////
    virtual Gadget* getParent () const { return nullptr; };

//    /////////////////////////////////////////////////
//    /// \brief Ajouter un élement dans m_enfants.
//    /// pour l'instant ne fait rien.
//    /// \todo mettre le nouvel enfant dans le bon calque (en fonction de sa classe?).
//    ///
//    /////////////////////////////////////////////////
//    virtual void ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement ){  };

    /////////////////////////////////////////////////
    /// \brief retirer un enfant du gadget
    /// \param cible le gadget à retirer
    ///
    /////////////////////////////////////////////////
    virtual void supprimerEnfant ( std::shared_ptr<Gadget> cible );

    /////////////////////////////////////////////////
    /// \brief Vider m_enfants. Ici on vide le contenu des calques.
    ///
    /////////////////////////////////////////////////
    virtual void viderEnfants () { m_calqueFond->viderEnfants (); m_calqueFenetres->viderEnfants ();  };

    /////////////////////////////////////////////////
    /// \brief Accesseur à l'élément de m_enfants désigné par un id.
    /// \return pour l'instant ne fait rien (nullptr).
    ///
    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> getEnfant ( unsigned int id ) const { return nullptr; };

    /////////////////////////////////////////////////
    /// \brief Definir m_size. Ici ne fait rien car Gui à la taille de la fenetre SFML.
    ///
    /////////////////////////////////////////////////
    virtual void setSize( sf::Vector2i val ){  };






    /////////////////////////////////////////////////
    /// \brief Recherche le gadget survolé par la sourie dans l'interface.
    ///
    /// \return Un pointeur vers le gadget survolé, nullptr si aucun.
    /////////////////////////////////////////////////
    Gadget*  chercherGadgetSurvole ();

    /////////////////////////////////////////////////
    /// \brief Traitement général des évenements clavier ou souris de tout les gadgets de l'interface.
    ///
    /// \param evenement		 L'évenemnt à tratier.
    /////////////////////////////////////////////////
    void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments de l'interface.
    ///
    /////////////////////////////////////////////////
    void actualiser ();







/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
public:

    /// la fabrique /////////////////////
    Fabrique       creer;              ///< La fabrique des gadget.

private:

    /// la fenetre SFML /////////////////////
    static sf::RenderWindow*  ms_fenetre;          ///< La fenêtre SFML de l'application, pour acceder aux coordonnées de la souris par exemple.

    /// les calques /////////////////////
    friend class                Fabrique;
    std::shared_ptr<Calque>     m_calqueFond;       ///< Le calque regroupant les gadgets les plus au fond de la vue.
    std::shared_ptr<Calque>     m_calqueFenetres;   ///< Le calque regroupant les fenetres.

    /// la gestion des gadgets interactifs /////////////////////
    Gadget*     m_gadgetSurvole;    ///> Le gadget survolé (nullptr si aucun)
    Gadget*     m_gadgetPresse;     ///> Le gadget pressé (nullptr si aucun)

}; // fin class Gui

} // fin namespace gui

#endif


////////////////////////////////////////////////////////////
/// \class gui::Gui
/// \ingroup Interface
///
/// Gère les gadgets composant les interfaces. Ce n'est pas un singleton mais il ne doit y avoir qu'une seul instance.
///
/// \see gui::Gadget
///
////////////////////////////////////////////////////////////



