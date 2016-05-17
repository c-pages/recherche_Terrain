#ifndef BTNBARREOUTILS__H
#define BTNBARREOUTILS__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
//#include "Donnee.h"
#include "interfaces/gadgets/Bouton.h"
#include "BtnIcone.h"
#include "interfaces/gadgets/Contenant.h"
#include    "interfaces/composants/CmpFond.h"
#include    "interfaces/composants/CmpOmbre.h"


namespace gui {



/////////////////////////////////////////////////
/// \brief Une barre d'outils, permet de déclencher des fonctions.
///
/////////////////////////////////////////////////
//class BtnBarreFonctions : public Donnee<std::vector<int>> {
class BtnBarreFonctions : public Bouton
                        , public CmpFond
                        , public CmpOmbre {


/////////////////////////////////////////////////
// struct
/////////////////////////////////////////////////
struct ElementOutil {
    std::string                 nom;
    FctnAction                  fonction;
    std::shared_ptr<BtnIcone>   bouton;
};



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    BtnBarreFonctions ();

    std::shared_ptr<BtnIcone> operator[](int i);

    std::shared_ptr<BtnIcone> ajouterElement (std::string nom, std::string fichierIcone, FctnAction action = [](){});

    std::shared_ptr<BtnIcone> ajouterElement (std::string nom, sf::Texture* icone, FctnAction action= [](){});

    void supprimerElement (unsigned int id);

    virtual void actualiserGeometrie ();

    virtual void actualiserStyle ();
    /////////////////////////////////////////////////
    virtual void traiterEvenements (const sf::Event& evenement);

    void setDrag ( bool val ) { m_drag = val;};
    bool dragEnCours(){return m_drag;};
    void positionnerFenetre ();
    virtual std::shared_ptr<Gadget>  testerSurvol ( sf::Vector2i position );

    void setModeOutils ( bool val = true );

    void    select ( int id);
    void    deselect ( );
    int     getSelect();


//    virtual void actualiserContenu ();
//    virtual void actualiserBounds ();

//    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    bool                            m_modeOutils;           ///< si on l'utilise comme une barre d'outils (un seul bouton a le focus à la fois)
    int                             m_outilActif;           ///< l'index de l'outil actif, -1: pas d'outils actif

    sf::Vector2i                    m_tailleBouton;         ///< La taille d'un bouton du menu
    std::vector< ElementOutil*>     m_elements;
    float                           m_largeurDrag;
    bool                            m_drag;
    sf::Vector2i                    m_decalageDragSouris;
    bool                            m_modeFenetre;



}; // fin class BtnBarreFonctions

} // fin namespace gui

#endif
