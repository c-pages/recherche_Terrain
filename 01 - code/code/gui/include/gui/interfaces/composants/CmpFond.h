#ifndef CMPFOND_H
#define CMPFOND_H

#include <SFML/Graphics.hpp>

#include "Composant.h"
#include "Valeurs.h"

#include "gadgets/AffRectangle.h"

namespace gui {

class CmpFond : public Composant
{
private:
public:
    CmpFond();


public:
    virtual void setFondCouleur         ( sf::Color couleur  );
    virtual void setFondCouleur         ( sf::Color couleur , Etat etat );
    virtual void setFondCouleur         ( Valeurs<sf::Color> couleurs  );

    virtual void setFondLigneCouleur    ( sf::Color couleur  );
    virtual void setFondLigneCouleur    ( sf::Color couleur , Etat etat );
    virtual void setFondLigneCouleur    ( Valeurs<sf::Color> couleurs );

    virtual void setFondLigneEpaisseur  ( float epaisseur );
    virtual void setFondLigneEpaisseur  ( float epaisseur , Etat etat );
    virtual void setFondLigneEpaisseur  ( Valeurs<float> epaisseur );

    virtual void appliquerEtat( Etat etat );
protected :
    /////////////////////////////////////////////////
    virtual void initialiserComposants ( Gadget*     base );

////////////////////////////////// ///////////////
// Membres
/////////////////////////////////////////////////
protected:

    // les composants de l'interface du gadget
    std::shared_ptr<AffRectangle>    m_fond;

    // les proprietés graphiques
    Valeurs<sf::Color>      m_fondCouleur;
    Valeurs<sf::Color>      m_fondLgnCouleur;
    Valeurs<float>          m_fondLgnEpaisseur;

};// fin CmpFond

}; // fin namespace gui

#endif // COMPFOND_H
