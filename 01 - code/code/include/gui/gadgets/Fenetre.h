
#ifndef FENETRE__H
#define FENETRE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gui/Gadget.h"
#include <gui/Calque.h>
#include "gui/gadgets/Bouton.h"

#include <SFML/Graphics.hpp>



namespace gui {

/////////////////////////////////////////////////
/// \brief Une fenêtre encapsule des éléments d'interface.
///
///
/////////////////////////////////////////////////
class Fenetre : public gui::Gadget {

/////////////////////////////////////////////////
// Classe interne
/////////////////////////////////////////////////
private:

    /////////////////////////////////////////////////
    /// \brief Une Glissière est un élément interactif qui permet de deplacer le contenu d'une fenetre.
    ///
    /////////////////////////////////////////////////
    class Glissiere : public gui::Gadget {

        /////////////////////////////////////////////////
        // Enums & typedefs
        /////////////////////////////////////////////////
        public:
            /////////////////////////////////////////////////
            /// \brief l'orientation du slider.
            /////////////////////////////////////////////////
            enum Orientation {
                Horizontal,
                Vertical
            };

        /////////////////////////////////////////////////
        // Méthodes
        /////////////////////////////////////////////////
        private:
        friend class Fenetre;

            /////////////////////////////////////////////////
            /// \brief Constructeur (privée, seulement créable depuis une fenêtre (pour l(instant).
            ///
            /// \param orientation		 Un slider horizontal ou vertical.
            /////////////////////////////////////////////////
            Glissiere (Orientation orientation);

        /////////////////////////////////////////////////
        // Membres
        /////////////////////////////////////////////////
        private:
            Orientation m_orientation;
            Bouton m_btnFond;           ///< Le bouton fix de fond, il permet de déplacer en un clique le m_btnGlissière.
            Bouton m_btnGlissiere;      ///< Ce bouton est la glissière proprement dite, c'est ce bouton qui glisse pour deplacer le contenu de la fenetre.

    }; // fin class Glissiere



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:

    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    Fenetre (  );

public:
    ///< Definir m_draggable
    void setDraggable( bool val ){ m_draggable = val; };

    ///< Acceder à m_draggable
    bool getDraggable () const { return m_draggable; };

    ///< Definir m_resizable
    void setResizable( bool val ){ m_resizable = val; };

    ///< Acceder à m_resizable
    bool getResizable () const { return m_resizable; };

    ///< Rendre visible ou non le bouton de fermeture de la fenetre
    void setFermable( bool val ){ m_fermable = val; };

    ///< Acceder à m_fermable
    bool getFermable () const { return m_fermable; };





    /////////////////////////////////////////////////
    /// \brief Ajouter un élement dans m_enfants.
    ///
    /////////////////////////////////////////////////
    virtual void ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement );

    /////////////////////////////////////////////////
    /// \brief Définit le titre de la fenêtre.
    ///
    /// \param titre		 Le nouveau titre.
    /////////////////////////////////////////////////
    void setTitre (std::string titre);

    /////////////////////////////////////////////////
    /// \brief Définir la couleur du titre.
    ///
    /// \param couleur		 La nouvelle couleur du titre.
    /////////////////////////////////////////////////
    void setTitreCouleur (sf::Color couleur);

    /////////////////////////////////////////////////
    /// \brief Définir la taille du texte du titre.
    ///
    /// \param taille		 La nouvelle taille du texte du titre.
    /////////////////////////////////////////////////
    void setTitreTaille (float taille);

    /////////////////////////////////////////////////
    /// \brief Définit le style du texte du titre.
    ///
    /// \param style		 Le nouveau style du texte du dtitre.
    /////////////////////////////////////////////////
    void setTitreStyle (sf::Text::Style style);

    /////////////////////////////////////////////////
    /// \brief Définit la police du titre.
    ///
    /// \param police		 La nouvelle police du titre.
    /////////////////////////////////////////////////
    void setTitrePolice (sf::Font& police);

    /////////////////////////////////////////////////
    /// \brief Definit la texture du fond de la fenetre.
    ///
    /// \param texture		 La nouvelle texture.
    /////////////////////////////////////////////////
    void setFondTexture (sf::Texture& texture);

    /////////////////////////////////////////////////
    /// \brief Definir la couleur du fond de la fenêtre.
    ///
    /// \param couleur		 La nouvelle couleur.
    /////////////////////////////////////////////////
    void setFondCouleur (sf::Color couleur);

    //////////////////////m_fermable///////////////////////////
    /// \brief Definir la couleur du contour de la fenêtre.
    ///
    /// \param couleur		 La nouvelle couleur.
    /////////////////////////////////////////////////
    void setContourCouleur (sf::Color couleur);

    /////////////////////////////////////////////////
    /// \brief Definir l'épaisseur du contour de la fenêtre.
    ///
    /// \param epaisseur		 La nouvelle épaisseur du contour.
    /////////////////////////////////////////////////
    void setContourEpaisseur (float epaisseur);






    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    /// \return thisPtr si est survolé, sinon nullptr.
    ///
    /// \param posSouris
    /////////////////////////////////////////////////
    virtual Gadget* testerSurvol (sf::Vector2i posSouris) ;


    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments de l'interface.
    ///
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Traitement des évenements clavier ou souris. C'est ici qu'on va gérer le drag et le redimmensionnement.
    ///
    /// \param evenement		 L'évenemnt à tratier.
    /////////////////////////////////////////////////
    virtual void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Dessine tout les éléments de l'interface.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

private:
    /////////////////////////////////////////////////
    /// \brief Actualise les parametres du shader clipping.
    ///
    /////////////////////////////////////////////////
    void actualiserClipping ();



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    /// options et propriétés de fonctionement /////////////////
    bool                m_fermable;             ///< Si on affiche le bouton de fermeture de la fenetre (defaut:true)
    bool                m_resizable;            ///< Si on peut redimmensionner la fenetre (defaut:true)
    bool                m_draggable;            ///< Si on peut dragger la fenetre (defaut:true)
    bool                m_dragEnCours;          ///< Si on est en train de dragger la fenêtre.
    sf::Vector2i        m_dragPosOrigin;        ///< La position d'origine au debut du drag.
    sf::Vector2i        m_dragPosSourisOrigin;  ///< La position d'origine de la souris au debut du drag.

    /// le shader /////////////////
    sf::Shader          m_shaderClip;       ///< Le shader qui permet de clipper les enfants de la fenêtre qui sortent de la zone d'affichage \todo Reintegrer en RAII les shaders!!

    /// Les composants de la fenetre /////////////////
    Bouton              m_boutonFermer;     ///< Le bouton de fermeture de la fenetre
    sf::RectangleShape  m_fond;             ///< Le shape du fond de la fenêtre.
    sf::Text            m_titre;            ///< Le titre de la fenêtre.
    Glissiere           m_sliderH;          ///< Le slider horizontal
    Glissiere           m_sliderV;          ///< Le slider vertical

    std::shared_ptr<Calque> m_calque;       ///< Le calque regroupant les enfants de la fenetres.


}; // fin class Fenetre

} // fin namespace gui

#endif
