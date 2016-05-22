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
    // creation du gadget dans son pointeur
    std::shared_ptr<Label> nouveauGadget = std::make_shared<gui::Label>( texte );

    // initialisation du gadget
    m_interface->m_calqueFond->ajouterEnfant( nouveauGadget );

    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<Image> Fabrique::image ( sf::Texture& image )
{
    // creation du gadget dans son pointeur
    std::shared_ptr<Image> nouveauGadget = std::make_shared<gui::Image>( image );

    // initialisation du gadget
    m_interface->m_calqueFond->ajouterEnfant( nouveauGadget );

    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<Bouton> Fabrique::bouton ( std::string texte , sf::Vector2i taille )
{
    // creation du gadget dans son pointeur
    std::shared_ptr<Bouton> nouveauGadget = std::make_shared<gui::Bouton>(  );

    // initialisation du gadget
    m_interface->m_calqueFond->ajouterEnfant( nouveauGadget );
    nouveauGadget->setTexte ( texte );
    if ( taille != sf::Vector2i( -1,-1 ) )
        nouveauGadget->setSize ( taille );
    else nouveauGadget->ajuster();

    return nouveauGadget;
}



/////////////////////////////////////////////////
std::shared_ptr<Bouton> Fabrique::bouton ( sf::Texture& texture, sf::Vector2i taille  )
{
    // creation du gadget dans son pointeur
    std::shared_ptr<Bouton> nouveauGadget = std::make_shared<gui::Bouton>( );

    // initialisation du gadget
    m_interface->m_calqueFond->ajouterEnfant( nouveauGadget );
    nouveauGadget->setIcone( texture );
    if ( taille != sf::Vector2i( -1,-1 ) )
        nouveauGadget->setSize ( taille );
    else nouveauGadget->ajuster();

    return nouveauGadget;
}






/////////////////////////////////////////////////
std::shared_ptr<Fenetre> Fabrique::fenetre  ( std::string titre , sf::Vector2i taille , bool draggable , bool resizable )
{

    // creation du gadget dans son pointeur
    std::shared_ptr<Fenetre> nouveauGadget = std::make_shared<gui::Fenetre>( );

    // initialisation du gadget
    m_interface->m_calqueFenetres->ajouterEnfant( nouveauGadget );
    nouveauGadget->setTitre     ( titre );
    nouveauGadget->setSize      ( taille );
    nouveauGadget->setDraggable ( draggable );
    nouveauGadget->setResizable ( resizable );

    return nouveauGadget;

}







///////////////////////////////////////////////////
//std::shared_ptr<Vue> Fabrique::vue ()
//{
//
//}


} // fin namespace gui

