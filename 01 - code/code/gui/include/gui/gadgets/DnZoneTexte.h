#ifndef DNZONETEXTE__H
#define DNZONETEXTE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/gadgets/Donnee.h"
#include "interfaces/composants/CmpTexte.h"
#include "BtnRectangle.h"
#include "AffLabel.h"

#include <memory>



namespace gui {


/////////////////////////////////////////////////
/// \brief Une zone pour entrer du texte.
///
/// \todo Placer le curseur à l'endroit du clique
/// \todo Déplacer le curseur avec les fleches
/// \todo Séléctionner une partie du texte
/// \todo copier-coller avec le clipboard de l'OS
/////////////////////////////////////////////////
class DnZoneTexte : public gui::Donnee<std::string> , public CmpTexte {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    DnZoneTexte ();

    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

//    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void traiterEvenements(const sf::Event& evenement );

public:
    ///< Definir m_ecritureActive
    void setModeEcritureActif( bool val ) { m_ecritureActive = val; actualiser (); };

    ///< Acceder à m_ecritureActive
    bool modeEcritureActif () const { return m_ecritureActive;  };

    void setNumericOnly ( bool val ){m_numerique = val; };

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    // les proprietés fonctionnelles
    bool            m_ecritureActive;    ///<
    bool            m_numerique;
    bool            m_clignotte;
    sf::Clock       m_clignotteChrono;
    int             m_curseurPos;

    // les composants de l'interface du gadget
    std::shared_ptr<BtnRectangle>   m_bouton;
    std::shared_ptr<BtnRectangle>   m_boutonSortir;
    std::shared_ptr<AffRectangle>   m_curseur;

    // Les actions pour le fonctionnement
    FctnAction                      fn_annuler ;
    FctnAction                      fn_valider ;
    FctnAction                      fn_cliqueTexte ;

    // les proprietés graphiques
    Valeurs<sf::Color>      m_btnCouleurs;
    Valeurs<sf::Color>      m_btnLgnCouleurs;
    Valeurs<float>          m_btnLgnepaisseurs;

    Valeurs<sf::Color>      m_curseurCouleurs;
    Valeurs<sf::Color>      m_curseurLgnCouleurs;
    Valeurs<float>          m_curseurLgnepaisseurs;


}; // fin class DnZoneTexte

} // fin namespace gui

#endif
