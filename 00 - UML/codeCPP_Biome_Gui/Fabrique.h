#ifndef FABRIQUE__H
#define FABRIQUE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////



namespace gui {



/////////////////////////////////////////////////
/// \brief La fabrique des gadget.
///
/////////////////////////////////////////////////
class Fabrique {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Cr�er un label.
    /// \return un pointeur vers le nouveau gadget cr��.
    ///
    /// \param texte		 Le texte du label.
    /////////////////////////////////////////////////
    std::shared_ptr<Label> label (string texte);

    /////////////////////////////////////////////////
    /// \brief Cr�er une image.
    /// \return un pointeur vers le nouveau gadget cr��.
    ///
    /// \param texture		 La texture du label.
    /////////////////////////////////////////////////
    std::shared_ptr<Image> image (sf::Texture texture);

    /////////////////////////////////////////////////
    /// \brief Cr�er un support pour afficher une vue SFML.
    /// \return un pointeur vers le nouveau gadget cr��.
    ///
    /////////////////////////////////////////////////
    std::shared_ptr<Vue> vue ();


}; // fin class Fabrique

} // fin namespace gui

#endif
