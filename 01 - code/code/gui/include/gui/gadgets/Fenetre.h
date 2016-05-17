#ifndef FENETRE__H
#define FENETRE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <memory>

#include "interfaces/ActionEvenement.h"

#include "decorations/FenDecoration.h"

//#include "gadgets/outils/AffBarreTitre.h"

#include <interfaces/gadgets/Contenant.h>
#include <interfaces/composants/CmpOmbre.h>
#include <interfaces/composants/CmpFond.h>
#include <interfaces/composants/CmpBarreTitre.h>


namespace gui {


class Fenetre   : public ActionEvenement
                , public CmpFond
                , public CmpOmbre
                , public CmpBarreTitre
{

public:
    enum class Decorations{
        Drag,
        Retaille,
        RetaillePanneau,
        Fermer
    };

/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    Fenetre();
    virtual ~Fenetre(){};

    /////////////////////////////////////////////////
    /// \brief Bascule entre un panneau simple (false) et un panneau slider (true).
    ///
    /// \param val
    /////////////////////////////////////////////////
    virtual void setDefilementActif (bool val);

    /////////////////////////////////////////////////
    virtual void ajouter (std::shared_ptr<Gadget> enfant);

    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> retirer (std::shared_ptr<Gadget> enfant);

    /////////////////////////////////////////////////
    virtual void traiterEvenements (const sf::Event& evenement);

    /////////////////////////////////////////////////
    virtual bool        estInteractif() { return true; }; ///< \todo voir si on peut faire mieux ...

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

    /////////////////////////////////////////////////
//    virtual sf::Vector2i getTailleBouton (){ return m_tailleBoutons; };
    sf::Vector2i    getTailleMini();

    std::shared_ptr<AffRectangle> getOmbre() { return m_ombre; };




    void ajouterDecoration ( Decorations deco  );

    void retirerDecoration ( Decorations deco  )
    {
        if ( m_decorations.find( deco ) != m_decorations.end())        {
            m_decorations.erase( deco  );
            demanderActualisation();
        }
    };



    virtual void setDeplacable( bool val  = true );

    virtual void setRedimensionnable( bool val  = true );

    virtual void actualiserEtatDeco ( );

    void viderTableaux()    {
        if ( m_decoASupprimer.size()>0 )
            for ( auto deco : m_decoASupprimer )
                m_decorations.erase( deco  );
    };




    virtual void fermer();
    virtual void reduire();

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:

    // les decorations
    std::vector<Decorations>                                m_decoASupprimer;
    std::map<Decorations, std::shared_ptr<FenDecoration>>   m_decorations;

    // composants
    std::shared_ptr<Contenant>                              m_contenant;    ///<

    // les proprietés graphiques
    sf::Color               m_contenantFndCouleur;
    sf::Color               m_contenantFndLgnCouleur;
    float                   m_contenantFndLgnepaisseur;
    sf::Color               m_contenantContenantCouleur;
    sf::Color               m_contenantContenantLgnCouleur;
    float                   m_contenantContenantLgnepaisseur;


}; // fin class Fenetre


} // fin namespace gui

#endif
