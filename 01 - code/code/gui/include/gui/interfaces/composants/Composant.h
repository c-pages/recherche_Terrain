#ifndef COMPOSANT_H
#define COMPOSANT_H


//#include "../../GUI.h"

#include "interfaces/Gadget.h"

namespace gui {

class Composant
{

public:
protected:

    virtual void initialiserComposants ( Gadget*     base ) = 0;

    virtual void appliquerEtat( Etat etat ){};

    Gadget*     m_base; // le gadget sur lequel on vient se raccrocher (par heritage)


}; // fin composant

}; // fin namespace gui


#endif // COMPOSANT_H
