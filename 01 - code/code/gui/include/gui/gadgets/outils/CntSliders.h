#ifndef GRPPANNEAUSLIDERS__H
#define GRPPANNEAUSLIDERS__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <memory>
#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "Valeurs.h"

#include "gadgets/AffRectangle.h"
#include "gadgets/AffImage.h"
#include "gadgets/DnGlissere.h"
#include "interfaces/gadgets/Contenant.h"

#include "repartiteurs/Repartiteur.h"
#include "repartiteurs/RepartiteurGrille.h"
#include "repartiteurs/RepartiteurHorizontal.h"
#include "repartiteurs/RepartiteurLibre.h"
#include "repartiteurs/RepartiteurVerticale.h"

namespace gui {



class CntSliders : public gui::Contenant {


/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    CntSliders ();

//    /////////////////////////////////////////////////
//    /// \brief Actualise le repartiteur puis les gadgets enfant contenus.
//    ///
//    /////////////////////////////////////////////////
//    virtual void actualiser ();


    void setSliderCouleur ( Valeurs<sf::Color> couleurs  ) {
            m_btnCouleurs = couleurs;
            actualiserStyle();
//            m_rectangle->setFondCouleur( couleur );
        };
    void setSliderLigneCouleur ( Valeurs<sf::Color> couleurs  ) {
            m_btnLgnCouleurs = couleurs;
            actualiserStyle();
//            m_rectangle->setFondLigneCouleur( couleur );
        };
    void setSliderLigneEpaisseur ( Valeurs<float> epaisseur ) {
            m_btnLgnepaisseurs =  epaisseur;
            actualiserStyle();
//            m_rectangle->setFondLigneEpaisseur( epaisseur );
        };


//    /////////////////////////////////////////////////
//    virtual void actualiserMasque ();

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

//    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

private:

//    virtual sf::Vector2f    deplMaxContenu();

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    float                   m_largeurSliders;

    // les composants de l'interface du gadget
    std::shared_ptr<DnGlissere>  m_slider_V;
    std::shared_ptr<DnGlissere>  m_slider_H;

    // les proprietés graphiques
    Valeurs<sf::Color>      m_btnCouleurs;
    Valeurs<sf::Color>      m_btnLgnCouleurs;
    Valeurs<float>          m_btnLgnepaisseurs;

    Valeurs<sf::Color>      m_btnBtnCouleurs;
    Valeurs<sf::Color>      m_btnBtnLgnCouleurs;
    Valeurs<float>          m_btnBtnLgnepaisseurs;

    Valeurs<sf::Color>      m_btnSlideCouleurs;
    Valeurs<sf::Color>      m_btnSlideLgnCouleurs;
    Valeurs<float>          m_btnSlideLgnepaisseurs;

    sf::Color               m_btnFndCouleur;
    sf::Color               m_btnFndLgnCouleur;
    float                   m_btnFndLgnepaisseur;

}; // fin class CntSliders

} // fin namespace gui

#endif
