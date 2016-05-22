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
    /// créer un bouton
    ///
    /////////////////////////////////////////////////
    Bouton ( );



    /// Accessuers / mutateurs ///////////////////////


    /////////////////////////////////////////////////
    /// \brief Définie l'état du bouton.
    ///
    /// \param etat		 Le nouvel état du bouton. (optionnel : si on ne le remplie pas, premet d'actualiser l'état tel qu'il est ).
    /////////////////////////////////////////////////
    virtual void setEtat ( Etat etat = Fin );




    /////////////////////////////////////////////////
    /// \brief Definie la taille de la marge
    ///
    /// \param marge La nouvelle marge
    /////////////////////////////////////////////////
    virtual void setMarge ( sf::Vector2f marge ){ m_marge = marge; ajuster(); };

    /////////////////////////////////////////////////
    /// \brief Définie le texte à afficher.
    ///
    /// \param texte		 le nouveau texte du gadget.
    /////////////////////////////////////////////////
    void setTexte ( std::string texte );

    /////////////////////////////////////////////////
    /// \brief Definie la taille du texte.
    ///
    /// \param taille		 La nouvelle taille du texte.
    /////////////////////////////////////////////////
    void setTexteTaille ( float taille );

    /////////////////////////////////////////////////
    /// \brief Definie la couleur du texte.
    ///
    /// \param couleur		 La nouvelle couleur du texte.
    /////////////////////////////////////////////////
    void setTexteCouleur ( sf::Color couleur );

    /////////////////////////////////////////////////
    /// \brief Défine le style du texte (sf::Text::Style).
    ///
    /// \param style		 Le style de texte à appliquer au gadget.
    /////////////////////////////////////////////////
    void setTexteStyle ( sf::Text::Style style );

    /////////////////////////////////////////////////
    /// \brief Definie la police du texte.
    ///
    /// \param police		 La nouvelle police du gadget.
    /////////////////////////////////////////////////
    void setTextePolice ( sf::Font& police );




    /////////////////////////////////////////////////
    /// \brief Definie la couleur du remplissage.
    ///
    /// \param couleur		 La nouvelle couleur.
    /////////////////////////////////////////////////
    void setRemplissageCouleur ( sf::Color couleur );

    /////////////////////////////////////////////////
    /// \brief Definie la couleur du contour.
    ///
    /// \param couleur		 La nouvelle couleur.
    /////////////////////////////////////////////////
    void setContourCouleur ( sf::Color couleur );

    /////////////////////////////////////////////////
    /// \brief Definie la couleur du contour.
    ///
    /// \param epaisseur		 La nouvelle epaisseur du contour.
    /////////////////////////////////////////////////
    void setContourEpaisseur ( float epaisseur );

    /////////////////////////////////////////////////
    /// \brief Définie l'image à afficher
    ///
    /// \param texure		 La texture à afficher. (bonne pratique : utiliser RAI (un manager de ressources))
    /////////////////////////////////////////////////
    void setIcone (sf::Texture& texture );

    /////////////////////////////////////////////////
    /// \brief Definie l'alpha du fond du bouton à l'état de repos
    ///
    /// \param repos		 L' alpha du fond au repos
    /// \param survol		 L' alpha du fond au survol
    /// \param press		 L' alpha du fond au press
    /////////////////////////////////////////////////
    void setAlphaEtats ( float repos , float survol, float press );

    /////////////////////////////////////////////////
    /// \brief Ajuster le fond au texte et à l'icone (le plus grand des deux)
    ///
    /////////////////////////////////////////////////
    void ajuster ( );








    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    /// \return thisPtr si est survolé, sinon nullptr.
    ///
    /// \param posSouris
    /////////////////////////////////////////////////
    virtual Gadget* testerSurvol (sf::Vector2i posSouris) ;

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
// Membres
/////////////////////////////////////////////////
public:

    Etat                m_etat;     ///< L'état du bouton

    /// les éléments graphiques /////////////////
    sf::RectangleShape  m_fond;     ///< Le fond .
    sf::RectangleShape  m_icone;    ///< L'icone à dessiner.
    sf::Text            m_texte;    ///< Le texte sfml affiché.

    /// les alphas en fonction de l'état du bouton /////////////////
    float   m_alphaRepos;           ///< l'alpha du fond du bouton au repos
    float   m_alphaSurvol;          ///< l'alpha du fond du bouton au survol
    float   m_alphaPresse;          ///< l'alpha du fond du bouton au presse

}; // fin class Bouton

} // fin namespace gui

#endif
