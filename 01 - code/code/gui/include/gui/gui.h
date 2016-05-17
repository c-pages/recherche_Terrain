#ifndef __GUI_H__
#define __GUI_H__


/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <string>
#include <SFML/Graphics.hpp>

#include "Valeurs.h"
#include "Enums.h"
#include "FabriqueBase.h"
#include "ResourcesMgr.h"

#include "interfaces/Gadget.h"
#include "interfaces/gadgets/Calque.h"

#include "gadgets/outils/AffCurseurSouris.h"
#include "gadgets/outils/AffInfoBulle.h"


/////////////////////////////////////////////////
// Definitions
/////////////////////////////////////////////////
#define  TAILLE_MASK 1080


namespace gui {



/////////////////////////////////////////////////
/// \brief Gère l'ensemble des gadgets et leurs interactions
///
/////////////////////////////////////////////////
class Interface : public Gadget {


public:
    Interface ( sf::RenderWindow* fenetre );

    virtual void draw ( sf::RenderTarget& target, sf::RenderStates states ) const;

    virtual void traiterEvenements ( sf::Event evenement );

    /////////////////////////////////////////////////
    /// \brief Actualiser les géométrie du gadgets, et donc ses bounds.
    ///
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    virtual void actualiser ( sf::Time deltaTemps ) { Gadget::actualiser( deltaTemps ); };


    virtual sf::Vector2i getTaille() const;

    sf::RenderWindow*        getFenetre()  { return m_fenetre; };

    /////////////////////////////////////////////////
    /// \brief Vide l'interface de tout ces gadgets et comportements
    ///
    /////////////////////////////////////////////////
    void reinitialiser();



private:

    std::shared_ptr<Gadget> chercherGadgetSurvole ();

    /////////////////////////////////////////////////
    /// \brief Déclenche un évènement pour tout les boutons (ms_boutons)
    ///
    /// \param evenement    L'évènement à déclencher.
    /// \param saufGadget   L'évènement ne sera pas déclencher pour ce gadget.    ///
    /////////////////////////////////////////////////
    void declencherToutBoutons ( Evenement evenement , std::shared_ptr<Gadget> saufGadget = nullptr );

    // FPS
    void calculerFPS();
    // gadget survolé
    void majAffichage_BoutonSurvol();


public:
    void setAfficherFPS ( bool val ) { m_afficherFPS = val ; };
public:
    void setAfficherBoutonSurvol ( bool val ) { m_afficherBoutonSurvol = val ; };


    /////////////////////////////////////////////////
    /// \brief Déclenche un évènement pour tout les boutons (ms_boutons)
    ///
    /// \param evenement    L'évènement à déclencher.
    /// \param saufGadget   L'évènement ne sera pas déclencher pour ce gadget.    ///
    /////////////////////////////////////////////////
protected:
    virtual bool        estInterface () { return true; };

/////////////////////////////////////////////////
// fonctions statics
/////////////////////////////////////////////////
public:

    static sf::Vector2i getPosSouris() {
        return sf::Mouse::getPosition( *ms_fenetreSFML );
    };

    static  void necessiteActualisation()                       { ms_necessiteActualisation = true ; };
    static  void setCurseur ( Curseurs    curseur   )           { ms_curseurSouris->setCurseur ( curseur  );  };
    static  std::shared_ptr<Gadget>       getBoutonSurvol ()    { return ms_boutonSurvole; };
    static  std::shared_ptr<Gadget>       getBoutonPress ()     { return ms_boutonPresse; };
    static  void                          vider_msBoutons ()    { ms_boutonSurvole = nullptr; ms_boutonPresse = nullptr; }


/////////////////////////////////////////////////
// membres statics
/////////////////////////////////////////////////
public:
    static sf::RenderWindow*                            ms_fenetreSFML;     ///< La fenetyre SFML;

    static  ResourcesMgr< sf::Font,      std::string >   ms_polices;        ///< Manager des polices
    static  ResourcesMgr< sf::Texture,   std::string >   ms_images;         ///< Manager des images
    static  ResourcesMgr< sf::Texture,   std::string >   ms_icones;         ///< Manager des icones ... a voir
    static  ResourcesMgr< sf::Texture,   std::string >   ms_curseurs;       ///< Manager des curseurs
/*
    static  std::shared_ptr<Calque>        ms_calque_bandeaux;
    static  std::shared_ptr<Calque>        ms_calque_panneau_G;
    static  std::shared_ptr<Calque>        ms_calque_panneau_D;
    static  std::shared_ptr<Calque>        ms_calque_bandeauMenuDeroulants;
    static  std::shared_ptr<Calque>        ms_calque_menuDeroulants;
*/
    static  std::shared_ptr<Calque>        ms_calque_bureau;
    static  std::shared_ptr<Calque>        ms_calque_fenetres;
    static  std::shared_ptr<Calque>        ms_calque_infos;
    static  std::shared_ptr<Calque>        ms_calque_souris;
private:

    static  bool                                    ms_necessiteActualisation;
    static  std::shared_ptr<AffCurseurSouris>       ms_curseurSouris;

    static  std::shared_ptr<Gadget>     ms_boutonSurvole;    ///< Le bouton survolé actuelement par la souris.
    static  std::shared_ptr<Gadget>     ms_boutonPresse;     ///< Le bouton pressé actuelement par la souris.



/////////////////////////////////////////////////
// membres
/////////////////////////////////////////////////
public:
    FabriqueBase    creer;                              ///< La fabrique de gadget de base (GOF: Fabrique)

private:

    sf::RenderWindow*           m_fenetre;          ///< La fenetyre SFML;

    /////////////////////////////////////////////////
    // FPS et infos survol
    /////////////////////////////////////////////////
    bool            m_afficherFPS;
    sf::Text        m_labelFPS;
    std::string     m_textFPS;
    sf::Clock       m_chronoFPS;
    unsigned int    m_compteurFPS;

    // gadget survolé
    bool                    m_afficherBoutonSurvol;
    sf::Text                m_labelBoutonSurvol;
    std::string             m_textBoutonSurvol;

    /////////////////////////////////////////////////
    // Infobulle
    /////////////////////////////////////////////////
    std::shared_ptr<AffInfoBulle>   m_infoBulle;
    bool                            m_infoActif;
    sf::Clock                       m_chronoDeclenchementInfo;      ///< Le chrono pour le déclenchement de l'info bulle
    sf::Vector2i                    m_sourisPosBack;

}; // fin class gui

}; // fin namespace gui



#endif // __GUI_H__
