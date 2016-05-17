#ifndef AFFCURSEURSOURIS_H
#define AFFCURSEURSOURIS_H

#include <gadgets/AffIcone.h>
#include <Enums.h>

namespace gui {


class AffCurseurSouris : public AffIcone
{
public:

    AffCurseurSouris( Interface *     interfacePArent  );

    //virtual ~AffCurseurSouris();

    void setCurseur ( Curseurs    curseur );

    /////////////////////////////////////////////////
    virtual void traiterEvenements( sf::Event evenement );

protected:

private:

    Interface *     m_interface;

};

}; // fin namespace gui

#endif // AFFCURSEURSOURIS_H
