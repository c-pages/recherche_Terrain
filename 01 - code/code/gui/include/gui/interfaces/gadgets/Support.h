#ifndef SUPPORT__H
#define SUPPORT__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/Gadget.h"

#include "interfaces/gadgets/Contenant.h"
#include "repartiteurs/Repartiteur.h"
#include <memory>
#include <map>



namespace gui {



class Support : public Gadget {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    Support(  );

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();
    virtual bool estAbsorbable(){ return m_absorbable; };

    void setInterface ( Interface *     interfacePArent );

    virtual void setAbsorbable ( bool val ) {m_absorbable = val; actualiserStyle ();};


/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////

protected:
    std::shared_ptr<AffRectangle>      m_fond;

    bool                               m_absorbable = false;

    Interface *     m_interface;

    sf::Color   m_fndCouleur;
    sf::Color   m_fndCouleurSurvol;
    sf::Color   m_fndLgnCouleur;
    float       m_fndLgnEpaisseur;

}; // fin class Support

} // fin namespace gui

#endif
