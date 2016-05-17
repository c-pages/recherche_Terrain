#ifndef CONTENANT__H
#define CONTENANT__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/Gadget.h"
#include "interfaces/gadgets/Groupe.h"
#include "gadgets/AffRectangle.h"
#include "repartiteurs/Repartiteur.h"

#include "interfaces/composants/CmpFond.h"

namespace gui {




class Contenant : public Gadget, public CmpFond {


enum class Decorations{
    Sliders
};

/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    Contenant ();


public:
    ///< Definir m_repartiteur
    void setRepartiteur( std::unique_ptr<Repartiteur> val ){ m_repartiteur = std::move(val); };

    void repartirEnfants () {
        m_repartiteur->repartir( m_groupe->getEnfants() );
    };

    /////////////////////////////////////////////////
    virtual void ajouter ( std::shared_ptr<Gadget> enfant, unsigned int index );
    virtual void ajouter ( std::shared_ptr<Gadget> enfant );

    void setRepartition ( Repartitions repartition );

//    /////////////////////////////////////////////////
//    virtual void actualiserMasque ();


    /////////////////////////////////////////////////
//    virtual void actualiserContenu ();

    /////////////////////////////////////////////////
    virtual void actualiserBounds ();

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    virtual void setTaille(sf::Vector2i taille){
        m_taille = taille;
        m_affContenant->setSize( { m_taille.x , m_taille.y } );
        demanderActuaGeom();
//        actualiserMasque () ;
    }
/*

    void setContenantFillColor ( sf::Color couleurs  ) {
            m_contenantCouleur = couleurs;
            demanderActuaStyle();
//            m_rectangle->setFondCouleur( couleur );
        };
    void setContenantOutlineColor ( sf::Color couleurs  ) {
            m_contenantLgnCouleur = couleurs;
            demanderActuaStyle();
//            m_rectangle->setFondLigneCouleur( couleur );
        };
    void setContenantOutlineThickness ( float epaisseur ) {
            m_contenantLgnepaisseur =  epaisseur;
            demanderActuaStyle();
//            m_rectangle->setFondLigneEpaisseur( epaisseur );
        };
*/
    /////////////////////////////////////////////////
    sf::Vector2f    deplMaxContenu();

    virtual std::shared_ptr<Gadget>  testerSurvol ( sf::Vector2i position );

    virtual sf::Vector2i getTailleContenant()   { return m_tailleContenant; };

    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

    virtual bool aEnfants() { return m_groupe->aEnfants(); };

    virtual std::vector<std::shared_ptr<Gadget>> getEnfants() const { return m_groupe->getEnfants(); };


/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:

    std::unique_ptr<Repartiteur>        m_repartiteur;      ///< cf; GOF Strategie


    sf::Texture                         m_contenu;          ///< La texture SFML qui affiche le contenu du panneau.
    sf::RenderTexture                   m_renderTexture;
    sf::Vector2f                        m_largeurSliders;

    sf::Vector2i                        m_tailleContenant;
    sf::Vector2i                        m_posContenant;

    // les composants de l'interface du gadget

    std::shared_ptr<sf::RectangleShape> m_affContenant;
    std::shared_ptr<Groupe>             m_groupe;

    // les proprietés graphiques
//    sf::Color               m_fndCouleur;


    sf::Color               m_contenantCouleur;
    sf::Color               m_contenantLgnCouleur;
    float                   m_contenantLgnepaisseur;

    int                     m_largeurRedimH;
    int                     m_largeurRedimV;

//
//    sf::Shader             m_masqueShader; ///< le shader qui s'occupe de masquer les bouts qui dépassent des fenêtres. (nullptr si non utilisé

}; // fin class Contenant

} // fin namespace gui

#endif
