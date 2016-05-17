#ifndef DNCASEACOCHER__H
#define DNCASEACOCHER__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/gadgets/Donnee.h"
#include "interfaces/composants/CmpTexte.h"

#include "BtnRectangle.h"
#include "AffRectangle.h"


namespace gui {


/////////////////////////////////////////////////
/// \brief Une case à cocher pour controler une valeur booléene.
///
/////////////////////////////////////////////////
class DnCaseACocher : public Donnee<bool> , public CmpTexte {

/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    DnCaseACocher ();

    virtual void actualiserGeometrie ();

    virtual void actualiserStyle ();

    virtual void actualiserBounds();

    virtual std::shared_ptr<Gadget>  testerSurvol ( sf::Vector2i position );

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    // les composants de l'interface du gadget
    std::shared_ptr<BtnRectangle>    m_bouton;
    std::shared_ptr<AffRectangle>    m_coche;

    // Les actions pour le fonctionnement
    FctnAction              fn_basculerValeur;

    Valeurs<sf::Color>      m_btnCouleurs;
    Valeurs<sf::Color>      m_btnLgnCouleurs;
    Valeurs<float>          m_btnLgnepaisseurs;

    Valeurs<sf::Color>      m_cocheCouleurs;
    Valeurs<sf::Color>      m_cocheLgnCouleurs;
    Valeurs<float>          m_cocheLgnepaisseurs;

}; // fin class DnCaseACocher

} // fin namespace gui

#endif
