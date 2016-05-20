/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gui/Fabrique.h>
#include "gui/Gui.h"

#include "appli/Config.h"

namespace gui {

/////////////////////////////////////////////////
Fabrique::Fabrique ( Gui* interface )
: m_interface ( interface )
{ }



/////////////////////////////////////////////////
std::shared_ptr<Label> Fabrique::label ( std::string texte )
{
    // creation du label dans son pointeur
    std::shared_ptr<Label> nouveauGadget = std::make_shared<gui::Label>( texte );

    // initialisation du label
    m_interface->m_calqueFond->ajouterEnfant( nouveauGadget );

    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<Image> Fabrique::image ( sf::Texture& image )
{
    // creation d'une image dans son pointeur
    std::shared_ptr<Image> nouveauGadget = std::make_shared<gui::Image>( image );

    // initialisation du label
    m_interface->m_calqueFond->ajouterEnfant( nouveauGadget );

    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<Bouton> Fabrique::bouton ( std::string texte , sf::Vector2i taille )
{
    // creation d'une image dans son pointeur
    std::shared_ptr<Bouton> nouveauGadget = std::make_shared<gui::Bouton>( texte , taille );

    // initialisation du label
    m_interface->m_calqueFond->ajouterEnfant( nouveauGadget );

    return nouveauGadget;
}



/////////////////////////////////////////////////
std::shared_ptr<Bouton> Fabrique::bouton ( sf::Texture& texture )
{
//    // creation d'une image dans son pointeur
//    std::shared_ptr<Bouton> nouveauGadget = std::make_shared<gui::Bouton>( image );
//
//    // initialisation du label
//    m_interface->m_calqueFond.ajouterEnfant( nouveauGadget );
//
//    return nouveauGadget;
}

///////////////////////////////////////////////////
//std::shared_ptr<Vue> Fabrique::vue ()
//{
//
//}


} // fin namespace gui
