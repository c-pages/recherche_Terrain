#ifndef CMPOMBRE_H
#define CMPOMBRE_H

#include <SFML/Graphics.hpp>

#include "Composant.h"
#include "Valeurs.h"

#include "gadgets/AffRectangle.h"

namespace gui {

class CmpOmbre : public Composant
{
private:
public:
    CmpOmbre();


public:
    virtual void setOmbreCouleur         ( sf::Color couleur  );

    virtual void setOmbreActive ( bool val = true );

protected :
    /////////////////////////////////////////////////
    virtual void initialiserComposants ( Gadget*     base );

////////////////////////////////// ///////////////
// Membres
/////////////////////////////////////////////////
protected:

    bool            m_ombreActive;

    // les composants de l'interface du gadget
    std::shared_ptr<AffRectangle>    m_ombre;

    // les proprietés graphiques
    sf::Color      m_ombreCouleur;

};// fin CmpOmbre

}; // fin namespace gui

#endif // COMPFOND_H
