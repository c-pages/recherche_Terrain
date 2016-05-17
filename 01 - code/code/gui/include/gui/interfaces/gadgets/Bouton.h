#ifndef BOUTON__H
#define BOUTON__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/ActionEvenement.h"
#include "interfaces/Gadget.h"
#include "gadgets/AffRectangle.h"


namespace gui {



/////////////////////////////////////////////////
/// \brief Un simple bouton
///
/////////////////////////////////////////////////
class Bouton : public gui::ActionEvenement {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    Bouton ();
    ~Bouton ();

    virtual std::shared_ptr<Gadget>  testerSurvol ( sf::Vector2i position );

    void setAutoAjuster (bool val ){ m_autoAjust = val; demanderActualisation();};

    static  std::vector<Gadget*>  GetBoutons(){ return ms_boutons ; };

    virtual bool        estInteractif() { return true; }; ///< \todo voir si on peut faire mieux ...

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    friend class Interface;
    friend class FabriqueBase;

    static  std::vector<Gadget*>      ms_boutons;

protected:
    bool                        m_autoAjust;        ///< Ajuste automatiquement la taille du bouton au texte (en tenant compte de la marge).
    std::shared_ptr<AffRectangle>    m_focusRect;        ///< le cadre marquant le focus
}; // fin class Bouton

} // fin namespace gui

#endif
