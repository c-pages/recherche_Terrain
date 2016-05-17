#ifndef DNGLISSERE__H
#define DNGLISSERE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/gadgets/Donnee.h"
#include "interfaces/composants/CmpGlissere.h"
#include "BtnRectangle.h"



namespace gui {



/////////////////////////////////////////////////
/// \brief Un slider permet de controler une valeur numerique.
///
/////////////////////////////////////////////////
class DnGlissere : public gui::Donnee<float> , public CmpGlissere {


/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    DnGlissere ( );

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

    /////////////////////////////////////////////////
    virtual void traiterEvenements (const sf::Event& evenement);

public:

    /////////////////////////////////////////////////
    virtual float getValeur();

    ///< Definir m_valeurMax
    void setValeurMax( float val );

    ///< Acceder à m_valeurMax
    float getValeurMax ( ) const ;

    ///< Definir m_valeurMin
    void setValeurMin( float val );

    ///< Acceder à m_valeurMin
    float getValeurMin ( ) const ;

    void incrementer( float increment = 20 );

    void decrementer( float increment = 20 );

private:

    bool dragEnCours( ) ;

    void setDrag (bool val );

    void deplacerSlider ();

    /////////////////////////////////////////////////
    /// \brief  Corriger la position pour la garder dans ses limites
    ///
    /////////////////////////////////////////////////
    void corrigerPositionSlider();

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    // les proprietés fonctionnelles
//    bool                            m_horizontal;   ///< l'orientation,  true: bouton horizontal, false: bouton vertical.
    float                           m_valeurMax;    ///<
    float                           m_valeurMin;    ///<
    bool                            m_drag;
    sf::Vector2i                    m_decalageDragSouris;

    // Les actions pour le fonctionnement
    FctnAction     fct_cliqueBtnFond;
    FctnAction     fct_dragStart;
    FctnAction     fct_dragStop;
    FctnAction     fct_rouletteH;
    FctnAction     fct_rouletteB;


}; // fin class DnGlissere

} // fin namespace gui

#endif

















