#ifndef DNZONENUM_H
#define DNZONENUM_H

#include "interfaces/gadgets/Donnee.h"

namespace gui {
class DnZoneTexte;
class BtnIcone;


class DnZoneNum : public Donnee<double>
{
public:

    DnZoneNum();


    /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

    /////////////////////////////////////////////////
    virtual void traiterEvenements (const sf::Event& evenement);

    void setMin ( double val ){m_min = val;};
    void setMax ( double val ){m_max = val;};
    void setPas ( double val ){m_pas = val;};

protected:
    virtual std::shared_ptr<Gadget>  testerSurvol ( sf::Vector2i position );
private:

//    sf::Vector2i    m_tailleBoutons;
    double           m_min;
    double           m_max;
    double           m_pas;

    std::shared_ptr<DnZoneTexte>    m_zoneTexte;
    std::shared_ptr<BtnIcone>       m_btnPlus;
    std::shared_ptr<BtnIcone>       m_btnMoins;

};

}; // fin namesapce gui
#endif // DNZONENUM_H
