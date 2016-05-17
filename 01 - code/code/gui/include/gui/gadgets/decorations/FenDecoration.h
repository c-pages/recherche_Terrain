#ifndef DECOFENETRE_H
#define DECOFENETRE_H
#include <memory>
#include "SFML/Graphics.hpp"

//#include <Fenetre.h>

namespace gui {
class Fenetre;
class FenDecoration //: public Fenetre
{
    public:
        ///< Default constructor
        FenDecoration( Fenetre* fenetre );



        /////////////////////////////////////////////////
        virtual void actualiserGeometrie (){};

        /////////////////////////////////////////////////
        virtual void actualiserStyle (){};

        /////////////////////////////////////////////////
        virtual void traiterEvenements (const sf::Event& evenement){};





    protected:

        Fenetre* m_fenetre;
};

}; // fin namespace gui

#endif // DECOFENETRE_H
