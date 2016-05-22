#ifndef FABRIQUE__H
#define FABRIQUE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gui/gadgets/Label.h"
#include "gui/gadgets/Image.h"
#include "gui/gadgets/Bouton.h"
#include "gui/gadgets/Fenetre.h"


namespace gui {

class Gui;

/////////////////////////////////////////////////
/// \brief La fabrique des gadget.
///
/////////////////////////////////////////////////
class Fabrique {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:

    /////////////////////////////////////////////////
    /// \brief Constructeur.
    ///
    /// \param le Gui parent
    /////////////////////////////////////////////////
    Fabrique ( Gui* interface );





    /////////////////////////////////////////////////
    /// \brief Créer un label.
    /// \return un pointeur vers le nouveau gadget créé.
    ///
    /// \param texte		 Le texte du label.
    /////////////////////////////////////////////////
    std::shared_ptr<Label> label ( std::string texte = "Nouveau label" );

    /////////////////////////////////////////////////
    /// \brief Créer une image.
    /// \return un pointeur vers le nouveau gadget créé.
    ///
    /// \param texture		 La texture du label.
    /////////////////////////////////////////////////
    std::shared_ptr<Image> image ( sf::Texture& texture );





    /////////////////////////////////////////////////
    /// \brief Créer un bouton texte rectangulaire.
    /// \return un pointeur vers le nouveau gadget créé.
    ///
    /// \param texte Le texte du bouton (optionel)
    /// \param taille La taille du bouton (optionel)
    /////////////////////////////////////////////////
    std::shared_ptr<Bouton> bouton ( std::string texte = "Bouton" , sf::Vector2i taille = {-1,-1} );

    /////////////////////////////////////////////////
    /// \brief Créer un bouton icone.
    /// \return un pointeur vers le nouveau gadget créé.
    ///
    /// \param texture		 La texture du bouton.
    /////////////////////////////////////////////////
    std::shared_ptr<Bouton> bouton ( sf::Texture& texture , sf::Vector2i taille = {-1,-1} );






    /////////////////////////////////////////////////
    /// \brief Créer une fenêtre
    /// \return un pointeur vers le nouveau gadget créé.
    ///
    /// \param titre		 Le titre de la fenetre
    /// \param taille		 La taille de la fenetre.
    /// \param draggable		 Si la fenetre peut être déplacer par l'utilisatuer.
    /// \param resizable		 Si la fenetre peut être redimmensionner par l'utilisatuer.
    /////////////////////////////////////////////////
    std::shared_ptr<Fenetre> fenetre  ( std::string titre = "Fenetre"
                                      , sf::Vector2i taille = {-1,-1}
                                      , bool draggable = true
                                      , bool resizable = true );




    //    /////////////////////////////////////////////////
    //    /// \brief Créer un support pour afficher une vue SFML.
    //    /// \return un pointeur vers le nouveau gadget créé.
    //    ///
    //    /////////////////////////////////////////////////
    //    std::shared_ptr<Vue> vue ();

/////////////////////////////////////////////////
// les membres
/////////////////////////////////////////////////
private:
    Gui*   m_interface;   ///< le Gui parent.



}; // fin class Fabrique

} // fin namespace gui

#endif
