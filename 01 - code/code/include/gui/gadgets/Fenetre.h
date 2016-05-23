
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
// Classes internes
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
            /// \param orientation	Un slider horizontal ou vertical.
            /// \param fenetre      La Fenetre parent.
            /////////////////////////////////////////////////
            Glissiere ( Orientation orientation  , Fenetre* fenetre );



            /////////////////////////////////////////////////
            /// \brief Modifie la longueur du gadget pour l'adapter à la fenetre.
            ///
            /// \param longueur la nouvelle longueur
            /////////////////////////////////////////////////
            void setLongueur ( int longueur );

            /////////////////////////////////////////////////
            /// \brief Modifie la longueur de la glissere.
            ///
            /// \param rapport la nouvelle longueur
            /////////////////////////////////////////////////
            void setRapport ( float rapport );

            /////////////////////////////////////////////////
            /// \brief Definie la position de la glissere sur le gadget
            ///
            /// \return position la nouvelle position
            /////////////////////////////////////////////////
            void setPosGlissiere ( int position );

            /////////////////////////////////////////////////
            /// \brief Acceder à la position de la glissere sur le gadget
            ///
            /// \return longueur la nouvelle longueur
            /////////////////////////////////////////////////
            int getPosGlissiere ();

            /////////////////////////////////////////////////
            /// \brief Modifie la largeur de la glissere.
            ///
            /// \param largeur la nouvelle largeur
            /////////////////////////////////////////////////
            void setLargeur ( int largeur ) { m_largeur = largeur; };

            /////////////////////////////////////////////////
            /// \brief Accéder à la largeur de la glissere.
            ///
            /// \return  la largeur
            /////////////////////////////////////////////////
            int getLargeur ( ) { return m_largeur; };






            /////////////////////////////////////////////////
            /// \brief Teste le survol du gadget par la souris.
            /// \return thisPtr si est survolé, sinon nullptr.
            ///
            /// \param posSouris
            /////////////////////////////////////////////////
            virtual Gadget* testerSurvol (sf::Vector2i posSouris) ;

            /////////////////////////////////////////////////
            /// \brief Traitement des évenements clavier ou souris. C'est ici qu'on va gérer le drag de la glissière.
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




        /////////////////////////////////////////////////
        // Membres
        /////////////////////////////////////////////////
        private:

            Fenetre*        m_fenetre;              ///< La fenêtre parent

            Orientation     m_orientation;          ///< L'orientation de la glissère, soit horizontal, soit vertical
            int             m_largeur;              ///< La largeur de la glissiere, represente m_size.x pour une glissiere vertical et m_size.y pour une horizontale.

            bool            m_dragEnCours;          ///< Si on est en train de dragger la fenêtre.
            sf::Vector2i    m_dragPosOrigin;        ///< La position d'origine au debut du drag.
            sf::Vector2i    m_dragPosSourisOrigin;  ///< La position d'origine de la souris au debut du drag.

            Bouton          m_btnFond;              ///< Le bouton fix de fond, il permet de déplacer en un clique le m_btnGlissière.
            Bouton          m_btnGlissiere;         ///< Ce bouton est la glissière proprement dite, c'est ce bouton qui glisse pour deplacer le contenu de la fenetre.

    }; // fin class Glissiere



    /////////////////////////////////////////////////
    /// \brief Redimensionnement
    ///
    /// Ensemble de boutons et de comportements permettant de redimenssionner la fenetre à laquel il appartient.
    /////////////////////////////////////////////////
    class Redimensionnement : public gui::Gadget {

        /////////////////////////////////////////////////
        // Méthodes
        /////////////////////////////////////////////////
        private:
        friend class Fenetre;

            /////////////////////////////////////////////////
            /// \brief Constructeur (privée, seulement créable depuis une fenêtre (pour l(instant).
            ///
            /// \param fenetre		 La Fenetre parent du Redimensionnement
            /////////////////////////////////////////////////
            Redimensionnement ( Fenetre* fenetre );

            /////////////////////////////////////////////////
            /// \brief Modifie la largeur des boutons
            ///
            /// \param largeur la nouvelle largeur
            /////////////////////////////////////////////////
            void setLargeur ( int largeur ) { m_largeur = largeur; };

            /////////////////////////////////////////////////
            /// \brief Accéder à la largeur des boutons
            ///
            /// \return  la largeur
            /////////////////////////////////////////////////
            int getLargeur ( ) { return m_largeur; };




            /////////////////////////////////////////////////
            /// \brief Teste le survol du gadget par la souris.
            /// \return thisPtr si est survolé, sinon nullptr.
            ///
            /// \param posSouris
            /////////////////////////////////////////////////
            virtual Gadget* testerSurvol (sf::Vector2i posSouris) ;

            /////////////////////////////////////////////////
            /// \brief Actualiser les positions des boutons
            ///
            /////////////////////////////////////////////////
            virtual void actualiser ();





        /////////////////////////////////////////////////
        // Membres
        /////////////////////////////////////////////////
        private:

            Fenetre*    m_fenetre;  ///< La fenêtre parent
            int         m_largeur;  ///< La largeur des boutons

            Bouton      m_btn_HG;   ///< Bouton Haut gauche
            Bouton      m_btn_H;    ///< Bouton Haut
            Bouton      m_btn_HD;   ///< Bouton Haut droit
            Bouton      m_btn_D;    ///< Bouton droit
            Bouton      m_btn_G;    ///< Bouton gauche
            Bouton      m_btn_BG;   ///< Bouton Bas gauche
            Bouton      m_btn_B;    ///< Bouton Bas
            Bouton      m_btn_BD;   ///< Bouton Bas droit

            std::vector<Bouton*>    m_boutons;  ///< la liste des boutons pour simplifier les manips

    }; // fin class Redimensionnement







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

    /////////////////////////////////////////////////
    /// \brief Définit si on peut déplacer la fenetre
    ///
    /// \param val true:fenêtre déplaçable, false, fenêtre fixe
    /////////////////////////////////////////////////
    void setDraggable( bool val ){ m_draggable = val; };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_draggable
    ///
    /////////////////////////////////////////////////
    bool getDraggable () const { return m_draggable; };

    /////////////////////////////////////////////////
    /// \brief Définit si on peut redimmensionner la fenetre
    ///
    /// \param val true:fenêtre redimmensionable, false, fenêtre fixe
    /////////////////////////////////////////////////
    void setResizable( bool val ){ m_resizable = val; };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_resizable
    ///
    /////////////////////////////////////////////////
    bool getResizable () const { return m_resizable; };

    /////////////////////////////////////////////////
    /// \brief Rendre visible ou non le bouton de fermeture de la fenetre
    ///
    /// \param val Le visibilité du bouton fermer.
    /////////////////////////////////////////////////
    void setFermable( bool val ){ m_fermable = val; m_btnFermer.setVisible( m_fermable ); };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_fermable
    ///
    /////////////////////////////////////////////////
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
    void setTitre (std::string titre)
    { m_titre.setString ( titre ); actualiser(); };

    /////////////////////////////////////////////////
    /// \brief Définir la couleur du titre.
    ///
    /// \param couleur		 La nouvelle couleur du titre.
    /////////////////////////////////////////////////
    void setTitreCouleur (sf::Color couleur)
    { m_titre.setColor ( couleur ); };

    /////////////////////////////////////////////////
    /// \brief Définir la taille du texte du titre.
    ///
    /// \param taille		 La nouvelle taille du texte du titre.
    /////////////////////////////////////////////////
    void setTitreTaille (float taille)
    { m_titre.setCharacterSize( taille ); actualiser(); };

    /////////////////////////////////////////////////
    /// \brief Définit le style du texte du titre.
    ///
    /// \param style		 Le nouveau style du texte du dtitre.
    /////////////////////////////////////////////////
    void setTitreStyle (sf::Text::Style style)
    { m_titre.setStyle( style ); actualiser(); };

    /////////////////////////////////////////////////
    /// \brief Définit la police du titre.
    ///
    /// \param police		 La nouvelle police du titre.
    /////////////////////////////////////////////////
    void setTitrePolice (sf::Font& police)
    { m_titre.setFont( police ); actualiser(); };

    /////////////////////////////////////////////////
    /// \brief Definit la texture du fond de la fenetre.
    ///
    /// \param texture		 La nouvelle texture.
    /////////////////////////////////////////////////
    void setFondTexture (sf::Texture& texture)
    { m_fond.setTexture( &texture ); };

    /////////////////////////////////////////////////
    /// \brief Definir la couleur du fond de la fenêtre.
    ///
    /// \param couleur		 La nouvelle couleur.
    /////////////////////////////////////////////////
    void setFondCouleur (sf::Color couleur)
    { m_fond.setFillColor( couleur ); };

    //////////////////////m_fermable///////////////////////////
    /// \brief Definir la couleur du contour de la fenêtre.
    ///
    /// \param couleur		 La nouvelle couleur.
    /////////////////////////////////////////////////
    void setContourCouleur (sf::Color couleur)
    { m_fond.setOutlineColor( couleur ); };

    /////////////////////////////////////////////////
    /// \brief Definir l'épaisseur du contour de la fenêtre.
    ///
    /// \param epaisseur		 La nouvelle épaisseur du contour.
    /////////////////////////////////////////////////
    void setContourEpaisseur (float epaisseur)
    { m_fond.setOutlineThickness( epaisseur ); };







    /////////////////////////////////////////////////
    /// \brief Faire défiler horizontalement le calque des enfnnts
    ///
    /// \param rapport		 La nouvelle position du calque.
    /////////////////////////////////////////////////
    void defilerHorizontal ( float rapport );

    /////////////////////////////////////////////////
    /// \brief Faire défiler verticalement le calque des enfnnts
    ///
    /// \param rapport		 La nouvelle position du calque.
    /////////////////////////////////////////////////
    void defilerVertical ( float rapport );




    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    ///
    /// \param posSouris
    /// \return thisPtr si est survolé, sinon nullptr.
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

    /// Les composants de la fenetre /////////////////

    sf::RectangleShape  m_fond;                 ///< Le shape du fond de la fenêtre.
    sf::Text            m_titre;                ///< Le titre de la fenêtre.

    Bouton              m_btnFermer;            ///< Le bouton de fermeture de la fenetre
    Glissiere           m_btnSliderH;           ///< Le slider horizontal
    Glissiere           m_btnSliderV;           ///< Le slider vertical
    Redimensionnement   m_redim;                ///< les boutons permettant le redimensionnement de la fenêtre

    std::shared_ptr<Calque> m_contenant;        ///< Le calque contenant, immobile, contient le calque contenu.
    std::shared_ptr<Calque> m_contenu;          ///< Le calque contenu, c'est lui qui conteient les enfants de la fenêtre et qui est mobile si besoin à l'aide des glissières.

}; // fin class Fenetre

} // fin namespace gui

#endif
