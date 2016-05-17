#include "Config.h"

#include <iostream>


namespace app
{


/////////////////////////////////////////////////
//initialisation des membres statics
/////////////////////////////////////////////////
//ResourceMgr<sf::Font,int>                                   Config::m_polices;
sf::Time                                                    Config::m_dureeImage  ;
//std::map < Config::Skins  , std::shared_ptr<gui::Skin >>    Config::m_skins = {};
//std::map < Config::Styles , std::shared_ptr<gui::Style>>    Config::m_styles = {};



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
    return m_dureeImage;
}


/////////////////////////////////////////////////
void Config::init()
{

    m_dureeImage =     sf::seconds (1.f / 60.f);

    initPolices();
    initTextures();
    initSkins();
    initStyles();
}


/////////////////////////////////////////////////
void Config::initPolices()
{
//    Config::m_polices.load( Polices::police_1   , "media/polices/arial.ttf"  );
//    Config::m_polices.load( Polices::police_2   , "media/polices/bgothl.ttf"  );
//    Config::m_polices.load( Polices::log        , "media/polices/consola.ttf"  );
}


/////////////////////////////////////////////////
void Config::initTextures()
{
  //  _textures.

}
/////////////////////////////////////////////////
void Config::initSkins()
{
/*
    /////////////////////////////////////////////////
    // Skin1
    /////////////////////////////////////////////////

    // Enregistrement du skin dans la pile de skin.
    m_skins.insert ( { Config::Skins::Skin1 , std::make_shared<gui::Skin> () } ) ;
    auto skin1 = m_skins[ Config::Skins::Skin1 ];

    //// quleques variables pour simplifier l'ecriture
    sf::Font    police              = m_polices.get( Polices::police_2 );
    sf::Color   couleurLignesExt    = sf::Color ( 75,75,95 , 255);
    sf::Color   couleurFond         = sf::Color ( 45,45,65 , 255 );
    sf::Color   couleurTexte        = sf::Color ( 175,175,190 );
    float       taille_Btn_Text     = 12;
    float       epaisseurLignes     = 1;

    //// DESACTIVE ///////////////////////////////////
    skin1->desactive->txt_police       = police;
    skin1->desactive->txt_style        = sf::Text::Style::Regular ;
    skin1->desactive->txt_taille       = taille_Btn_Text;
    skin1->desactive->txt_couleur      = sf::Color ( 200,200,200);
    skin1->desactive->lgn_epaisseur    = 1;
    skin1->desactive->lgn_couleur      = sf::Color ( 255,255,255 , 20 );
    skin1->desactive->fnd_couleur      = sf::Color ( 150,150,255 , 50 );
    skin1->desactive->fnd_texture      = sf::Texture ();
    skin1->desactive->align            = gui::Alignements::Libre ;
    skin1->desactive->ajust            = gui::Ajustements::Sans ;

    //// FENETRE ///////////////////////////////////
    skin1->fenetre->txt_police         = police;
    skin1->fenetre->txt_style          = sf::Text::Style::Regular ;
    skin1->fenetre->txt_taille         = 18;
    skin1->fenetre->txt_couleur        =            couleurTexte;
    skin1->fenetre->lgn_epaisseur      =            epaisseurLignes;
    skin1->fenetre->lgn_couleur        =            couleurLignesExt;
    skin1->fenetre->fnd_couleur        =            couleurFond;
    skin1->fenetre->fnd_texture        = sf::Texture ();
    skin1->fenetre->align              = gui::Alignements::Libre ;
    skin1->fenetre->ajust              = gui::Ajustements::Sans ;

    //// BOUTON REPOS ///////////////////////////////////
    skin1->btnRepos->txt_police        = police;
    skin1->btnRepos->txt_style         = sf::Text::Style::Regular ;
    skin1->btnRepos->txt_taille        = taille_Btn_Text;
    skin1->btnRepos->txt_couleur       = couleurTexte;
    skin1->btnRepos->lgn_epaisseur     = 0;
    skin1->btnRepos->lgn_couleur       = sf::Color ( 255,255,255 , 50 );
    skin1->btnRepos->fnd_couleur       = sf::Color ( 80,80,80 , 255 );
    skin1->btnRepos->fnd_texture       = sf::Texture ();
    skin1->btnRepos->align             = gui::Alignements::Libre;
    skin1->btnRepos->ajust             = gui::Ajustements::Sans;

    //// BOUTON SURVOL ///////////////////////////////////
    skin1->btnSurvol->txt_police       = police;
    skin1->btnSurvol->txt_style        = sf::Text::Style::Regular;
    skin1->btnSurvol->txt_taille       = taille_Btn_Text;
    skin1->btnSurvol->txt_couleur      =             couleurTexte;
    skin1->btnSurvol->lgn_epaisseur    = 0;
    skin1->btnSurvol->lgn_couleur      = sf::Color ( 255,255,255 , 150 );
    skin1->btnSurvol->fnd_couleur      = sf::Color ( 100,100,100 , 255 );
    skin1->btnSurvol->fnd_texture      = sf::Texture ();
    skin1->btnSurvol->align            = gui::Alignements::Libre;
    skin1->btnSurvol->ajust            = gui::Ajustements::Sans;

    //// BOUTON PRESS ///////////////////////////////////
    skin1->btnPress->txt_police        = police;
    skin1->btnPress->txt_style         = sf::Text::Style::Regular;
    skin1->btnPress->txt_taille        = taille_Btn_Text;
    skin1->btnPress->txt_couleur       =             couleurTexte;
    skin1->btnPress->lgn_epaisseur     = 0;
    skin1->btnPress->lgn_couleur       = sf::Color ( 255,255,255 , 200 );
    skin1->btnPress->fnd_couleur       = sf::Color ( 180,180,180 , 255 );
    skin1->btnPress->fnd_texture       = sf::Texture ();
    skin1->btnPress->align             = gui::Alignements::Libre;
    skin1->btnPress->ajust             = gui::Ajustements::Sans;

    //// LABEL TITRE ///////////////////////////////////
    skin1->lblTitre->txt_police        = police;
    skin1->lblTitre->txt_style         = sf::Text::Style::Regular ;
    skin1->lblTitre->txt_taille        = 10;
    skin1->lblTitre->txt_couleur       =             couleurTexte;
    skin1->lblTitre->lgn_epaisseur     = 1 ;
    skin1->lblTitre->lgn_couleur       = sf::Color ( 255,255,255 , 200 );
    skin1->lblTitre->fnd_couleur       = sf::Color ( 150,150,255 , 255 );
    skin1->lblTitre->fnd_texture       = sf::Texture ();
    skin1->lblTitre->align             = gui::Alignements::Libre;
    skin1->lblTitre->ajust             = gui::Ajustements::Sans;

    //// LABEL COURANT ///////////////////////////////////
    skin1->lblCourant->txt_police      = police;
    skin1->lblCourant->txt_style       = sf::Text::Style::Regular;
    skin1->lblCourant->txt_taille      = 13;
    skin1->lblCourant->txt_couleur     = sf::Color (50,50,50);
    skin1->lblCourant->lgn_epaisseur   = 1;
    skin1->lblCourant->lgn_couleur     = sf::Color ( 255,255,255 , 200 );
    skin1->lblCourant->fnd_couleur     = sf::Color ( 150,150,255 , 255 );
    skin1->lblCourant->fnd_texture     = sf::Texture ();
    skin1->lblCourant->align           = gui::Alignements::Libre;
    skin1->lblCourant->ajust           = gui::Ajustements::Sans;

    //// LABEL LOG ///////////////////////////////////
    skin1->lblLog->txt_police      = police;
    skin1->lblLog->txt_style       = sf::Text::Style::Regular;
    skin1->lblLog->txt_taille      = 11;
    skin1->lblLog->txt_couleur     = sf::Color (200,200,200);
    skin1->lblLog->lgn_epaisseur   = 1;
    skin1->lblLog->lgn_couleur     = sf::Color ( 255,255,255 , 200 );
    skin1->lblLog->fnd_couleur     = sf::Color ( 150,150,255 , 255 );
    skin1->lblLog->fnd_texture     = sf::Texture ();
    skin1->lblLog->align           = gui::Alignements::Libre;
    skin1->lblLog->ajust           = gui::Ajustements::Sans;

    //// cadre ///////////////////////////////////
    skin1->cadre->txt_police      = police;
    skin1->cadre->txt_style       = sf::Text::Style::Regular;
    skin1->cadre->txt_taille      = 2;
    skin1->cadre->txt_couleur     = sf::Color ( 200,200,200);
    skin1->cadre->lgn_epaisseur   =  0;//          epaisseurLignes;
    skin1->cadre->lgn_couleur     = sf::Color ( 255,255,255 , 20);
    skin1->cadre->fnd_couleur     = sf::Color ( 255,255,255 , 0 );
    skin1->cadre->fnd_texture     = sf::Texture ();
    skin1->cadre->align           = gui::Alignements::Libre;
    skin1->cadre->ajust           = gui::Ajustements::Sans;

    //// invisible ///////////////////////////////////
    skin1->invisible->txt_police      = police;
    skin1->invisible->txt_style       = sf::Text::Style::Regular;
    skin1->invisible->txt_taille      = 12;
    skin1->invisible->txt_couleur     = sf::Color ( 255,255,255 , 200);
    skin1->invisible->lgn_epaisseur   = 1;
    skin1->invisible->lgn_couleur     = sf::Color ( 255,255,255 , 00 );
    skin1->invisible->fnd_couleur     = sf::Color ( 255,255,255 , 0 );
    skin1->invisible->fnd_texture     = sf::Texture ();
    skin1->invisible->align           = gui::Alignements::Libre;
    skin1->invisible->ajust           = gui::Ajustements::Sans;
*/
}

/////////////////////////////////////////////////
void Config::initStyles()
{

}


}




















