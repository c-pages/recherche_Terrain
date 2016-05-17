#ifndef LSTSIMPLE__H
#define LSTSIMPLE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/gadgets/Liste.h"
#include "gadgets/outils/BtnMenu.h"
#include <memory>



namespace gui {



class LstSimple : public Liste<std::string> {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    LstSimple();
    virtual void actualiserGeometrie ();

    ///< Ajouter un élement dans la liste
    virtual void ajouterElement ( std::string nouvelElement );

    virtual void actualiserStyle ();

//    void draw (sf::RenderTarget& target, sf::RenderStates states) const;



    void setAjustement ( bool val ) { m_ajustement = val; demanderActualisation(); };

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    bool                m_ajustement = false;

    std::shared_ptr<AffRectangle>           m_fond;
    std::vector<std::shared_ptr<BtnTexte>>  m_boutons;


}; // fin class LstSimple

} // fin namespace gui

#endif
