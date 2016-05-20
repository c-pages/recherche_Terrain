#ifndef GADGET__H
#define GADGET__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

#include "gui/Actions.h"

#include <iostream>

namespace gui {

/////////////////////////////////////////////////
/// \brief Un gadget est la classe abstraite des éléments de l'interface.
///
/////////////////////////////////////////////////
class Gadget :  public std::enable_shared_from_this<Gadget>,
                public sf::NonCopyable,
                public sf::Transformable,
                public sf::Drawable,
                public Actions
{
/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////

public:
    ///< \brief Les differents états du bouton.
    enum Etat {
        Repos,      ///< Le bouton est au repos.
        Survol,     ///< Le bouton est survolé par la souris.
        Presse      ///< Le bouton est pressé.
    };


/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur.
    ///
    /////////////////////////////////////////////////
    Gadget ();

    /////////////////////////////////////////////////
    /// \brief Créer un shared pointeur vers this.
    /// \return Un pointeur vers ce gadget.
    ///
    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> thisPtr ()  { return shared_from_this(); };





    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    /// \return nullptr de base, fonction à surcharger pour éléments interactifs.
    ///
    /// \param posSouris		 La position à tester.
    /////////////////////////////////////////////////
    virtual Gadget* testerSurvol (sf::Vector2i posSouris) ;

    /////////////////////////////////////////////////
    /// \brief Traitement des évenements clavier ou souris.
    ///
    /// \param evenement		 L'évenemnt à tratier.
    /////////////////////////////////////////////////
    virtual void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments de l'interface.
    ///
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine tout les éléments de l'interface.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;







    /// Accesseurs / mutateur    /////////////////////

    /////////////////////////////////////////////////
    /// \brief Definie l'état du gadget , surtout pour les éléments interactifs, ici ne fait rien.
    ///
    /////////////////////////////////////////////////
    virtual void setEtat (Etat etat){ };

    /////////////////////////////////////////////////
    /// \brief Definir m_parent.
    ///
    /////////////////////////////////////////////////
    virtual void setParent( Gadget* val ){ m_parent = val; };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_parent.
    ///
    /////////////////////////////////////////////////
    virtual Gadget* getParent () const { return m_parent; };

    /////////////////////////////////////////////////
    /// \brief Ajouter un élement dans m_enfants.
    ///
    /////////////////////////////////////////////////
    virtual void ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement );

    /////////////////////////////////////////////////
    /// \brief retirer un enfant du gadget
    /// \param cible le gadget à retirer
    ///
    /////////////////////////////////////////////////
    virtual void retirerEnfant ( std::shared_ptr<Gadget> cible );

    /////////////////////////////////////////////////
    /// \brief Vider m_enfants.
    ///
    /////////////////////////////////////////////////
    virtual void viderEnfants () { m_enfants.clear(); };

    /////////////////////////////////////////////////
    /// \brief Accesseur à l'élément de m_enfants désigné par un id.
    ///
    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> getEnfant ( unsigned int id ) const { if ( id>=0 || id<m_enfants.size() )  return m_enfants.at( id ); else return 0; };





    /////////////////////////////////////////////////
    /// \brief demanderau perent à être au dessus des autres enfants.
    ///
    /////////////////////////////////////////////////
    void demander_etreDevant ();

    /////////////////////////////////////////////////
    /// \brief Mettre le gadget au dessus des autres enfants de son parent.
    ///
    /// \param gadget le gadget à mettre devant
    /////////////////////////////////////////////////
    void mettreDevant ( std::shared_ptr<Gadget> gadget );


    /////////////////////////////////////////////////
    /// \brief supprimer le gadget.
    ///
    /////////////////////////////////////////////////
    virtual void supprimer () { m_parent->retirerEnfant ( thisPtr() ); };





    ////////////////////////////////////////////////////////////
    /// \brief override (un peu a l'arrache) de la fonction sf::Transformable::setPosition().
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(float x, float y);

    ////////////////////////////////////////////////////////////
    /// \brief override (un peu a l'arrache) de la fonction sf::Transformable::setPosition().
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(const sf::Vector2f& position);

    ////////////////////////////////////////////////////////////
    /// \brief override (un peu a l'arrache) de la fonction sf::Transformable::setPosition().
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(const sf::Vector2i& position);

    /////////////////////////////////////////////////
    /// \brief Acceder à la position absolue du gadget.
    ///
    /////////////////////////////////////////////////
    sf::Vector2f getPosAbs () const;






    /////////////////////////////////////////////////
    /// \brief Definir m_size.
    ///
    /////////////////////////////////////////////////
    virtual void setSize( sf::Vector2i val );

    /////////////////////////////////////////////////
    /// \brief Acceder à m_size.
    ///
    /////////////////////////////////////////////////
    sf::Vector2i getSize () const { return m_size; };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_globalBounds.
    ///
    /////////////////////////////////////////////////
    sf::IntRect getGlobalBounds () const { return m_globalBounds; };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_localBounds.
    ///
    /////////////////////////////////////////////////
    sf::IntRect getLocalBounds () const { return m_localBounds; };







/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:
//    friend class Gui;

    /// Composite /////////////////////
    Gadget*                                 m_parent;           ///< Le gadget parent.
    std::vector<std::shared_ptr<Gadget>>    m_enfants;          ///< les liste des gadgets enfants.

    /// Geométrie /////////////////////
    sf::Vector2i    m_size;             ///< La taille du gadget.
    sf::IntRect     m_globalBounds;     ///< Les limites globales du gadget (par rapport à la fenêtre principale).
    sf::IntRect     m_localBounds;      ///< Les limites locales du gadget (par rapport à son parent).

}; // fin class Gadget

} // fin namespace gui

#endif



