﻿
#ifndef CONFIG_H
#define CONFIG_H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>


#include "appli/ResourceMgr.h"


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
    /// \brief listes les polices enregistrables dans le manager de polices
    ///
    /////////////////////////////////////////////////
    enum Polices                :  int  {   police_1
                                        ,   police_2
                                        ,   log
                                        };

    /////////////////////////////////////////////////
    /// \brief listes les images enregistrables dans le manager de texture
    ///
    /////////////////////////////////////////////////
    enum Images                :  int  {   image_1
                                        ,  image_2
                                        };





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
    /// \li \todo les sons (à prévoir)
    /// \li \todo les musiques (à prévoir)
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

    static  ResourceMgr<sf::Texture,int>                        ms_textures;     ///< Manager des textures
    static  ResourceMgr<sf::Font,int>                           ms_polices;      ///< Manager des polices

private:
    static  sf::Time                                            ms_dureeImage;   ///< Durée d'une image, Autrement dit on a 1/FrameRate = \e DureeImage



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
