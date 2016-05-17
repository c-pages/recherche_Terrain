#ifndef CONFIG_H
#define CONFIG_H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
//#include <ResourceMgr.h>
//#include <Skin.h>
//#include <Style.h>
#include <GUI.h>


namespace app
{

/////////////////////////////////////////////////
/// \brief Contient les différents éléments de Configuration de l'application.
///
/////////////////////////////////////////////////
class Config
{

public:
    /////////////////////////////////////////////////
    /// \brief listes les polices enregistrable dans le manager de polices
    ///
    /////////////////////////////////////////////////
    enum Polices                :  int  {   police_1
                                        ,   police_2
                                        ,   log
                                        };

    /////////////////////////////////////////////////
    /// \brief listes les styles (gui::Style) enregistrable dans la pile des Styles
    ///
    /////////////////////////////////////////////////
    enum Styles                 :  int  {   root
                                        ,   Bouton
                                        ,   Fenetre   };

    /////////////////////////////////////////////////
    /// \brief listes les skins (gui::Skin) enregistrable dans la pile des skins.
    ///
    /////////////////////////////////////////////////
    enum Skins                  :  int  {   Skin1   };


    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    Config();

    /////////////////////////////////////////////////
    /// \brief Destructeur
    ///
    /////////////////////////////////////////////////
    virtual ~Config();


    /////////////////////////////////////////////////
    /// \brief Initialiser les differents élément
    ///
    /// \li les textures
    /// \li les polices
    /// \li les styles
    /// \li les sons (à prévoir)
    /// \li les musiques (à prévoir)
    ///
    /////////////////////////////////////////////////
    static void init();

    /////////////////////////////////////////////////
    /// \brief recuperer la durée d'une image, DureeImage = 1.f / 60.f à 60Fps.
    ///
    /////////////////////////////////////////////////
    static sf::Time getDureeImage();

private:

    /////////////////////////////////////////////////
    /// \brief Initialise le manager de textures.
    ///
    /////////////////////////////////////////////////
    static void initTextures();

    /////////////////////////////////////////////////
    /// \brief Initialise le Manager des polices.
    ///
    /////////////////////////////////////////////////
    static void initPolices();

    /////////////////////////////////////////////////
    /// \brief Initialiser les differents skins pour l'interface graphique
    ///
    /////////////////////////////////////////////////
    static void initSkins();

    /////////////////////////////////////////////////
    /// \brief Initialiser les differents styles pour l'interface graphique
    ///
    /////////////////////////////////////////////////
    static void initStyles();


    /////////////////////////////////////////////////
    // Les membres
    /////////////////////////////////////////////////

public:

//    static  ResourceMgr<sf::Texture,int>                        m_textures;     ///< Manager des textures
//    static  ResourceMgr<sf::Font,int>                           m_polices;      ///< Manager des polices
//    static  std::map < Styles , std::shared_ptr<gui::Style> >   m_styles;       ///< les styles pour le GUI \todo passer de pointer* à point shared_ptr ou unique_ptr ?
//    static  std::map < Skins  , std::shared_ptr<gui::Skin > >   m_skins;        ///< les styles pour le GUI \todo passer de pointer* à point shared_ptr ou unique_ptr ?

private:
    static  sf::Time                                            m_dureeImage;   ///< Durée d'une image, Autrement dit on a 1/FrameRate = \e DureeImage



};
}; // fin app
#endif // CONFIG_H


////////////////////////////////////////////////////////////
/// \class app::Config
/// \ingroup application
///
/// Configuration des textures, sons, musiques polices, tailles, couleurs ....
///
/// \see app::Ecran, app::Gestion_ecrans
///
////////////////////////////////////////////////////////////

