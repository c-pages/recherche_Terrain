#ifndef LSTDEROULANTE__H
#define LSTDEROULANTE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/gadgets/Liste.h"
#include "LstSimple.h"
#include "BtnTexte.h"
#include "AffIcone.h"
#include <memory>



namespace gui {



class LstDeroulante : public Liste<std::string> {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////
public:
    LstDeroulante();

    virtual void actualiserGeometrie ();

    virtual void actualiserStyle ();

    ///< Ajouter un élement dans la liste
    virtual void ajouterElement ( std::string nouvelElement );


//    void draw (sf::RenderTarget& target, sf::RenderStates states) const;



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    bool                        m_deroule = false;

    std::shared_ptr<LstSimple>  m_liste;
    std::shared_ptr<BtnTexte>   m_boutonLabel;
    std::shared_ptr<AffIcone>   m_fleche;

}; // fin class LstDeroulante

} // fin namespace gui

#endif
