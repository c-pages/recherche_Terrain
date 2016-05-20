#ifndef BOUTON__H
#define BOUTON__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gui/Gadget.h"



namespace gui {



/////////////////////////////////////////////////
/// \brief Un bouton rectangulaire
///
///
/////////////////////////////////////////////////
class Bouton :  public gui::Gadget {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /// \param texte Le texte du bouton (optionel)
    /// \param taille La taille du bouton (optionel)
    /////////////////////////////////////////////////
    Bouton ( std::string texte , sf::Vector2i taille );

//
//    /////////////////////////////////////////////////
//    /// \brief Créer un shared pointeur vers this.
//    /// \return Un pointeur vers ce gadget.
//    ///
//    /////////////////////////////////////////////////
//    virtual std::shared_ptr<Gadget> thisPtr ()  { return std::make_shared<Bouton>(this); };


    /////////////////////////////////////////////////
    /// \brief Définie l'état du bouton.
    ///
    /// \param etat		 Le nouvel état du bouton.
    /////////////////////////////////////////////////
    virtual void setEtat (Etat etat);

    /////////////////////////////////////////////////
    /// \brief Traitement des évenements clavier ou souris.
    ///
    /// \param evenement		 L'évenemnt à tratier.
    /////////////////////////////////////////////////
    virtual void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualiser le gadget (bounding bax)
    ///
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine le gadget
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    /// \return thisPtr si est survolé, sinon nullptr.
    ///
    /// \param posSouris
    /////////////////////////////////////////////////
//    virtual std::shared_ptr<Gadget> testerSurvol (sf::Vector2i posSouris) ;
    virtual Gadget* testerSurvol (sf::Vector2i posSouris) ;



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
public:

    Etat                m_etat;     ///< L'état du bouton

    /// les éléments graphiques /////////////////
    sf::RectangleShape  m_shape;    ///< Le shape à dessiner.
    sf::Text            m_texte;    ///< Le texte sfml affiché.
//
//    sf::Color           m_couleurRepos;
//    sf::Color           m_couleurSurvol;
//    sf::Color           m_couleurPresse;

}; // fin class Bouton

} // fin namespace gui

#endif
