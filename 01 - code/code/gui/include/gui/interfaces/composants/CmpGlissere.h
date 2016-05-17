#ifndef CMPGLISSERE_H
#define CMPGLISSERE_H

#include "Composant.h"
#include "Valeurs.h"

#include "gadgets/AffRectangle.h"
#include "gadgets/BtnRectangle.h"

namespace gui {

class CmpGlissere : public Composant
{
public:

    CmpGlissere();


    // le slider
    virtual void setSliderCouleur           ( Valeurs<sf::Color> couleurs );
    virtual void setSliderLigneCouleur      ( Valeurs<sf::Color> couleurs );
    virtual void setSliderLigneEpaisseur    ( Valeurs<float> epaisseur );

    // le bouton
    virtual void setBoutonCouleur           ( Valeurs<sf::Color> couleurs );
    virtual void setBoutonLigneCouleur      ( Valeurs<sf::Color> couleurs );
    virtual void setBoutonLigneEpaisseur    ( Valeurs<float> epaisseur );

    // le fond
    virtual void setFondCouleur             ( sf::Color couleurs );
    virtual void setFondLigneCouleur        ( sf::Color couleurs );
    virtual void setFondLigneEpaisseur      ( float epaisseur );

    // dimensionnement
    virtual void setLongueurCurseur( float pourcentage );
    virtual void setLongueur( float longueur );
    virtual void setLargeur( float largeur );

    virtual void setHorizontal (  );
    virtual void setVertical (  );

protected :
    /////////////////////////////////////////////////
    virtual void initialiserComposants ( Gadget*     base );


/////////////////////////////////////////////////
// les membres
/////////////////////////////////////////////////
protected:
  // les proprietés fonctionnelles
    bool                            m_horizontal;   ///< l'orientation,  true: bouton horizontal, false: bouton vertical.
    float                           m_valeurMax;    ///<
    float                           m_valeurMin;    ///<
    float                           m_longueur;     ///<
    float                           m_largeur;      ///<

    // les composants de l'interface du gadget
    std::shared_ptr<BtnRectangle>   m_boutonFond;
    std::shared_ptr<BtnRectangle>   m_slider;
    std::shared_ptr<AffRectangle>   m_fond;


    Valeurs<sf::Color>      m_btnCouleurs;
    Valeurs<sf::Color>      m_btnLgnCouleurs;
    Valeurs<float>          m_btnLgnepaisseurs;

    Valeurs<sf::Color>      m_slideCouleurs;
    Valeurs<sf::Color>      m_slideLgnCouleurs;
    Valeurs<float>          m_slideLgnepaisseurs;

    sf::Color               m_fndCouleur;
    sf::Color               m_fndLgnCouleur;
    float                   m_fndLgnepaisseur;
private:
};

};

#endif // CMPGLISSERE_H
