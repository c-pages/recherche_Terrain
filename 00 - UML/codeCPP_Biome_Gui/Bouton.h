#ifndef BOUTON__H
#define BOUTON__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Gadget.h"



namespace gui {



/////////////////////////////////////////////////
/// \brief Un bouton 
///
/////////////////////////////////////////////////
class Bouton : public gui::Gadget {


/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /// \brief Les differents �tats du bouton.
    /////////////////////////////////////////////////
    enum Etat {
        Repos,            ///< Le bouton au repos.
        Survol,            ///< Le bouton est survol� par la souris.
        Presse            ///< Le bouton est press�.
    };



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    Bouton ();

    /////////////////////////////////////////////////
    /// \brief D�finie l'�tat du bouton.
    ///
    /// \param etat		 Le nouvel �tat du bouton.
    /////////////////////////////////////////////////
    void setEtat (Etat etat);

    /////////////////////////////////////////////////
    /// \brief Traitement des �venements clavier ou souris.
    ///
    /// \param evenement		 L'�venemnt � tratier.
    /////////////////////////////////////////////////
    virtual void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualiser les �l�ments de l'interface.
    ///
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine tout les �l�ments de l'interface.
    ///
    /// \param target		 
    /// \param states		 
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    /// \return thisPtr si est survol�, sinon nullptr.
    ///
    /// \param posSouris		 
    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> testerSurvol (sf::Vector2i posSouris) const;



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
public:
    Etat m_etat;    ///< L'�tat du bouton    

}; // fin class Bouton

} // fin namespace gui

#endif
