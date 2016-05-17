#ifndef BTNMENU__H
#define BTNMENU__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <vector>
#include <memory>

#include "interfaces/gadgets/Bouton.h"
#include "gadgets/AffRectangle.h"
#include "gadgets/BtnTexte.h"

#include "interfaces/composants/CmpOmbre.h"


namespace gui {



/////////////////////////////////////////////////
/// \brief Un menu, permet de déclencher un action parmis d'autres.
///
/////////////////////////////////////////////////
class BtnMenu   : public Bouton
                , public CmpOmbre
                , public CmpFond
                , public CmpTexte {



/////////////////////////////////////////////////
// struct
/////////////////////////////////////////////////
struct ElementMenu {
    std::string                 nom;
    FctnAction                  fonction;
    std::shared_ptr<BtnTexte>   bouton;

    virtual void    setCoche ( bool val ){};
};
struct ElementAction : public ElementMenu{
};
struct ElementCoche : public ElementMenu {
    bool                        coche;
    virtual void    setCoche ( bool val ){ coche = val; };
};





/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    BtnMenu ();

    void ajouterElement         (std::string nom, FctnAction fonction );
    void ajouterEspace          ( );
    void ajouterElementCoche    (std::string nom, FctnAction fonction, bool coche = false );

    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param id
    /////////////////////////////////////////////////
    void supprimerElement (unsigned int id);



//    virtual void actualiserBounds ();

    /////////////////////////////////////////////////
    void actualiserGeometrie();

    /////////////////////////////////////////////////
    void actualiserStyle();



    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

//    virtual std::shared_ptr<Gadget>  testerSurvol ( sf::Vector2i position );

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
public:

    static  std::shared_ptr<BtnMenu>        ms_menuOuvert;

protected:

    // les proprietés fonctionnelles
    sf::Vector2i                    m_tailleMenu;   ///< La taille d'un bouton du menu
    float                           m_ecart;

    // les composants de l'interface du gadget
    std::vector<ElementMenu*>       m_elements;

    // les proprietés graphiques
    Valeurs<sf::Color>  m_btnCouleurs;
    Valeurs<sf::Color>  m_btnLignesCouleurs;
    Valeurs<float>      m_btnLignesEpaisseurs;

}; // fin class BtnMenu

} // fin namespace gui

#endif
