


#include "appli/Config.h"
#include <iostream>


namespace app
{


/////////////////////////////////////////////////
//initialisation des membres statics
/////////////////////////////////////////////////
ResourceMgr<sf::Texture,    int>    Config::ms_textures;
ResourceMgr<sf::Font,       int>    Config::ms_polices;
ResourceMgr<sf::Shader,     int>    Config::ms_shaders;

sf::Time                        Config::ms_dureeImage  ;




/////////////////////////////////////////////////
Config::Config()
{
    //ctor
}



/////////////////////////////////////////////////
Config::~Config()
{
    //dtor
}


/////////////////////////////////////////////////
sf::Time
Config::getDureeImage()
{
    return ms_dureeImage;
}


/////////////////////////////////////////////////
void Config::init()
{

    ms_dureeImage =     sf::seconds (1.f / 60.f);

    initPolices();
    initTextures();

}


/////////////////////////////////////////////////
void Config::initPolices()
{
    ms_polices.load( Polices::police_1   , "media/polices/arial.ttf"  );
    ms_polices.load( Polices::police_2   , "media/polices/bgothl.ttf"  );
    ms_polices.load( Polices::log        , "media/polices/consola.ttf"  );
}


/////////////////////////////////////////////////
void Config::initTextures()
{
    ms_textures.load( Images::image_1       , "media/img/avatar 2.jpg"  );
    ms_textures.load( Images::image_2       , "media/img/ico_fenetre.png" );
    ms_textures.load( Images::fenetreFond1  , "media/img/fenetre_fond_1.jpg" );
}

/////////////////////////////////////////////////
void Config::initShaders()
{
    ms_shaders.load( Shaders::clipping  , "media/img/avatar 2.jpg" , sf::Shader::Fragment );
}


}




















