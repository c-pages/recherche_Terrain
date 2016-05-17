#ifndef GADGET__H
#define GADGET__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <memory>
#include <interfaces/Geometrie.h>
#include <interfaces/Composition.h>
//#include <Skin.h>
#include <interfaces/ActionClavier.h>
#include <Enums.h>


namespace gui {

class Interface;
class BtnMenu;

/////////////////////////////////////////////////
/// \brief Classe communes à tout les gadgets, gère affichage actualisation, etc...
///
/////////////////////////////////////////////////
class Gadget : public std::enable_shared_from_this<Gadget>, public sf::Drawable, public gui::Geometrie, public gui::Composition, public gui::ActionClavier  {


/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////
    typedef std::shared_ptr<Gadget> ptr;    ///< Pointeur vers un gadget.


    /////////////////////////////////////////////////
    /// \brief  Les differentes grandes familles de gadgets
    /////////////////////////////////////////////////
    enum class Type {

        Interface,  ///<

        Affichage,  ///< Les gadgets sans interaction, affichant seulement une donnée (image, texte ...)
        Bouton,     ///< Les gadgets interactifs qui declenchent une action.
        Donnee,     ///< Gadgets interactif controlant une donnée.
        Liste,      ///< Gadgets controlant la selection d'un element parmis une liste.
        Fenetre,    ///< Permet de regrouper n'importe quel gadgets dans un ensemble manipulable.

        Outils      ///< tout les gadgets qui ne servent qu'en composant ( pour composer un gadget ).
    };



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:

    virtual std::shared_ptr<Gadget> thisPtr()  {
//        std::cout << "DEMANDE DE THISPTR\n";
        return shared_from_this();
    };


    /////////////////////////////////////////////////
    /// \brief accesseur à la taille
    ///
    /// \return la taille. Si non visible renvois {0,0}
    /////////////////////////////////////////////////
    virtual sf::Vector2i getTaille () const
    {
        if ( estVisible() )
            return m_taille;
        else return {0,0};
    };

    virtual bool estAbsorbable(){};
    virtual void setAbsorbable ( bool val ) {};

    ///< Definir m_visible
    void setVisible( bool val = true );

//    ///< Definir m_visible
//    bool getVisible( );

    ///< Definir m_actif
    void setActif( bool val  = true );

    ///< Definir m_focus
    void setFocus( bool val   = true );

    ///< Definir m_survol
    void setSurvol( bool val  = true );

    ///< Definir m_presse
    void setPresse( bool val  = true );

    ///< Definir m_deplacable
    virtual void setDeplacable( bool val  = true );

    ///< Definir m_redimensionnable
    virtual void setRedimensionnable( bool val  = true );


public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    Gadget ();

    /////////////////////////////////////////////////
    /// \brief Destructeur
    ///
    /////////////////////////////////////////////////
    virtual ~Gadget ();

    /////////////////////////////////////////////////
    /// \brief Constructeur de recopie (=delete pour empecher la copie).
    ///
    /// \param original		 Le gadget a recopier.
    /////////////////////////////////////////////////
    Gadget (Gadget & original)= delete;

    /////////////////////////////////////////////////
    /// \brief Surcharge de l'operateur =(=delete pour empecher la copie).
    ///
    /// \param original
    /////////////////////////////////////////////////
    Gadget& operator= (Gadget & original)= delete;

    /////////////////////////////////////////////////
    /// \brief Actualiser les géométrie du gadgets, et donc ses bounds.
    ///
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie (){};

    /////////////////////////////////////////////////
    virtual void actualiserStyle (){};


    /////////////////////////////////////////////////
    virtual void actualiserEtat (){
        // On analyse l'etat du bouton
        if ( ! estActif() )
            m_etat = Etat::desactive;
        else if ( !estSurvole () && !estPresse() )
            m_etat = Etat::repos;
        else if ( estPresse () )
            m_etat = Etat::press;
        else if ( estSurvole () )
            m_etat = Etat::survol;
    };

    /////////////////////////////////////////////////
    Etat etat (){
        actualiserEtat ();
        return m_etat;
    };

    /////////////////////////////////////////////////
    /// \brief Actualiser le gadget pour l'animation.
    ///
    /// \param deltaTemps		 Le temps écoulé depuis la dernière actualisation.
    /////////////////////////////////////////////////
    virtual void actualiser ( sf::Time deltaTemps );

    /////////////////////////////////////////////////
    /// \brief  Traitement des évènements  du gadget.
    ///
    /// \param evenement		 L'evenemnt SFML à traiter.
    /////////////////////////////////////////////////
    virtual void traiterEvenements (const sf::Event& evenement);


    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;


    /////////////////////////////////////////////////
    /// \brief Déclencher un évenement souris (les évenement claviers sont gérer.
    ///
    /// \param evenement
    /////////////////////////////////////////////////
    virtual void declencher ( Evenement evenement ){};

public:
    /////////////////////////////////////////////////
    /// \brief Le gadget est-il actif (m_actif)?
    ///
    /////////////////////////////////////////////////
    bool estActif () const;

    /////////////////////////////////////////////////
    /// \brief Le gadget est-il visible (m_visible)?
    ///
    /////////////////////////////////////////////////
    bool estVisible () const;

    /////////////////////////////////////////////////
    /// \brief Le gadget a-t-il le focus (m_focusf)?
    ///
    /////////////////////////////////////////////////
    bool aLeFocus () const;

    /////////////////////////////////////////////////
    /// \brief Le gadget est-il survolé (m_survol)?
    ///
    /////////////////////////////////////////////////
    bool estSurvole () const;

    /////////////////////////////////////////////////
    /// \brief Le gadget est-il pressé (m_presse)?
    ///
    /////////////////////////////////////////////////
    bool estPresse () const;

    /////////////////////////////////////////////////
    /// \brief Le gadget est-il déplacable (m_deplacable)?
    ///
    /////////////////////////////////////////////////
    bool estDeplacable () const;

    sf::Vector2i getPosSouris ( );
    sf::Vector2i getLocalPosSouris ( );

    virtual void actualiserEtatDeco ( ){};

    /////////////////////////////////////////////////
    virtual void creerNomUnique( std::string type  = "Gadget" );

    virtual std::shared_ptr<Gadget>  testerSurvol ( sf::Vector2i position );

    virtual std::string getNom() const;
    void                setNom( std::string nom );

    unsigned int        getID() const;

    int                 getNombreGadgets () const;
//
//    virtual void    setTexte( std::string val );
//    std::string     getTexte( ) const;

    void            setMarge ( sf::Vector2f marge );
    void            setMarge ( float val );
    void            setMarge ( float x , float y );
    sf::Vector2f    getMarge() const;


    void    demanderActualisation();
    void    demanderActuaGeom();
    void    demanderActuaStyle();
    void    demanderActuaContenu();
    void    demanderActuaBounds();

    virtual bool        estInterface () { return false; };///< \todo voir si on peut faire mieux ...
    virtual bool        estInteractif() { return false; }; ///< \todo voir si on peut faire mieux ...

    void setMenu(std::shared_ptr<BtnMenu> menu ) { m_menu = menu; };


    virtual void fermer(){};    ///< \todo pour les fenetre, à voir si no a pas mieux
    virtual void reduire(){};   ///< \todo pour les fenetre, à voir si no a pas mieux

    void            setInfo( std::string info );
    std::string     getInfo();

//    virtual void setShaderMasque( sf::Shader shader );
    virtual void setMasqueRect  ( float posX, float posY, float tailleX, float tailleY );
    void setMasqueActif ( bool val = true );
    bool estMasque      () const;
/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:

    static std::string      ms_logNomGadgetBack;

    sf::Vector2f            m_marge;            ///< La marge à laissé

    bool                    m_necessiteActualisation ;
    bool                    m_aBesoinActuaGeom ;
    bool                    m_aBesoinActuaStyle ;
//    bool                    m_aBesoinActuaContenu ;
    bool                    m_aBesoinActuaBounds ;

    unsigned int            m_id;

    static  int             ms_CompteurGadgets;   ///< L'interface courante dans laquelle on créé les gadgets.

//    std::string         m_texte;            ///< Le texte du gadget.

    std::string             m_nom;          ///< Nom unique automatique pour le gadget.
    Type                    m_type;         ///< Nom unique automatique pour le gadget.

    bool m_visible;             ///< La visibilité du gadget ( true: visible, false: invisible )
    bool m_actif;               ///< L'activité du gadget ( true: actif, false: inactif )
    bool m_focus;               ///< Le focus du gadget ( true: à le focus, false: sans le focus )
    bool m_survol;              ///< Le survol par la souris (true si le gadget est survolé par la souris).
    bool m_presse;              ///< Le bouton gauche de la souris est pressé (true si le gadget est survolé par la souris).

    bool m_deplacable;          ///< Si le gadget est déplacable (clique and drag)
    bool m_redimensionnable;    ///< Si le gadget est redimensionnable (clique and drag)

    Etat m_etat;                ///< l'etat du bouton

    friend class            FabriqueBase;

    shared_ptr<BtnMenu>     m_menu;     ///< le menu déroulant au clqiue droit sur le gadget

    std::string             m_info;          ///< le texte de l'info bulle.

//
    sf::Shader              m_masqueShader;     ///< le shader qui s'occupe de masquer les bouts qui dépassent des fenêtres. (nullptr si non utilisé
    bool                    m_masqueActif;      ///<
//    sf::FloatRect           m_masqueRect;       ///<

}; // fin class Gadget

} // fin namespace gui

#endif




























