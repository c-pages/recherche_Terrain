#ifndef FENDECOREDIM_H
#define FENDECOREDIM_H

#include <gadgets/decorations/FenDecoration.h>
#include <Valeurs.h>
#include <interfaces/ActionEvenement.h>

namespace gui{
class BtnRectangle;

class FenDecoRedim : public FenDecoration
{
public:

    FenDecoRedim( Fenetre* fenetre );

    virtual ~FenDecoRedim();

   /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

    /////////////////////////////////////////////////
    virtual void traiterEvenements (const sf::Event& evenement);


    bool redimEnCours () {
        if ( m_redimGauche || m_redimDroite || m_redimHaut || m_redimBas )
            return true;
        else false;
    };

private:
    typedef ActionEvenement::FctnAction FctnAction;

    void redimmensionner_haut ();
    void redimmensionner_bas ();
    void redimmensionner_gauche ();
    void redimmensionner_droite ();

    void redimmensionner ();

    void corrigerTailleMinimum ();

    void initDrag();

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    // les proprietés fonctionnelles
    bool    m_redimGauche       = false;
    bool    m_redimDroite       = false;
    bool    m_redimHaut         = false;
    bool    m_redimBas          = false;
    bool    m_redimmensionner   = false;

    sf::Vector2i    m_sourisPosOrigin;
    sf::Vector2i    m_tailleOrigin;
    sf::Vector2i    m_posOrigin;
    sf::Vector2i    m_tailleFenetre;
    sf::Vector2i    m_posFenetre;
    sf::Vector2i    m_posMin;

    // les composants de l'interface du gadget
    std::shared_ptr<BtnRectangle>   m_btn_gauche;
    std::shared_ptr<BtnRectangle>   m_btn_droite;
    std::shared_ptr<BtnRectangle>   m_btn_hautGauche;
    std::shared_ptr<BtnRectangle>   m_btn_hautDroite;
    std::shared_ptr<BtnRectangle>   m_btn_basGauche;
    std::shared_ptr<BtnRectangle>   m_btn_basDroite;
    std::shared_ptr<BtnRectangle>   m_btn_haut;
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

    protected:
    private:
};
}; // fin namesapce gui
#endif // FENDECOREDIM_H
