#ifndef FENDECOREDIMPANNEAU_H
#define FENDECOREDIMPANNEAU_H

#include <gadgets/decorations/FenDecoration.h>
#include <Valeurs.h>
#include <interfaces/ActionEvenement.h>

namespace gui{

class BtnRectangle;


class FenDecoRedimPanneau : public FenDecoration
{
    public:

        FenDecoRedimPanneau( Fenetre* fenetre );

        virtual ~FenDecoRedimPanneau();

   /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

    virtual void traiterEvenements (const sf::Event& evenement);

    /////////////////////////////////////////////////
//    void actualiser ( sf::Time delta );

    bool redimEnCours () {
        return m_redimensionner;
    };

private:
    typedef ActionEvenement::FctnAction FctnAction;
    void redimensionner ();

    void corrigerTailleMinimum ();



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    // les proprietés fonctionnelles
    bool    m_redimensionner   = false;

    sf::Vector2i     m_sourisPosOrigin;
    sf::Vector2i     m_tailleOrigin;

    sf::Vector2i     m_tailleFenetre;

    // les composants de l'interface du gadget
    std::shared_ptr<BtnRectangle>   m_btn_bas;

    // les proprietés graphiques
    Valeurs<sf::Color>      m_btnDragCouleurs;
    Valeurs<sf::Color>      m_btnDragLgnCouleurs;
    Valeurs<float>          m_btnDragLgnepaisseurs;

    Valeurs<sf::Color>      m_btnDragSlideCouleurs;
    Valeurs<sf::Color>      m_btnDragSlideLgnCouleurs;
    Valeurs<float>          m_btnDragSlideLgnepaisseurs;

    sf::Color               m_btnDragFndCouleur;
    sf::Color               m_btnDragFndLgnCouleur;
    float                   m_btnDragFndLgnepaisseur;

    // Les actions pour le fonctionnement
    FctnAction     fct_redimStartB;
    FctnAction     fct_redimStopB;

};

}; // fin namesapce gui


#endif // FENDECOREDIM_H
