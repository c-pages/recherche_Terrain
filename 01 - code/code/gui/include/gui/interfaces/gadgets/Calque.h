#ifndef CALQUE_H
#define CALQUE_H

#include "interfaces/Gadget.h"

namespace gui {

class Calque : public Gadget
{
public:
    Calque( std::string nom );
    virtual ~Calque();

    /////////////////////////////////////////////////
    void actualiser ();

    /////////////////////////////////////////////////
    std::shared_ptr<Gadget>  testerSurvol ( sf::Vector2i position );


protected:
private:


};

};


#endif // CALQUE_H
