
#include "FabriqueBase.h"
#include "gui.h"


#include <iostream>


namespace gui{

/////////////////////////////////////////////////
FabriqueBase::FabriqueBase ( Interface* interfaceParent )
: m_interfaceParent ( interfaceParent )
{}



/////////////////////////////////////////////////
template<typename T>
std::shared_ptr<T>  FabriqueBase::creerGadget (){

    // Creation du nouveau gadget
    std::shared_ptr<T> nouveauGadget = std::make_shared<T>( );

    // Affiliation a l'interface
    m_interfaceParent->ajouter ( nouveauGadget );
    nouveauGadget->setParent ( m_interfaceParent );
    m_interfaceParent->ms_calque_bureau->ajouter ( nouveauGadget );

//    // Application du skin de l'interface au gadget
//    nouveauGadget->setSkin ( m_interfaceParent->getSkin() );

    // renvois du nouveau gadget créé.
    return nouveauGadget;

}


/////////////////////////////////////////////////
template<typename T>
std::shared_ptr<T>  FabriqueBase::creerBureau (){

    // Creation du nouveau gadget
    std::shared_ptr<T> nouveauGadget = std::make_shared<T>( );

    // Affiliation a l'interface
    m_interfaceParent->ajouter ( nouveauGadget );
    nouveauGadget->setParent ( m_interfaceParent );
    m_interfaceParent->ms_calque_bureau->ajouter ( nouveauGadget );

//    // Application du skin de l'interface au gadget
//    nouveauGadget->setSkin ( m_interfaceParent->getSkin() );

    // renvois du nouveau gadget créé.
    return nouveauGadget;

}



/////////////////////////////////////////////////
template<typename T>
std::shared_ptr<T>  FabriqueBase::creerFenetre (){

    // Creation du nouveau gadget
    std::shared_ptr<T> nouveauGadget = std::make_shared<T>( );

    m_interfaceParent->ajouter ( nouveauGadget );
    nouveauGadget->setParent ( m_interfaceParent );
    m_interfaceParent->ms_calque_fenetres->ajouter ( nouveauGadget );

    m_interfaceParent->demanderActualisation();
//    // Application du skin de l'interface au gadget
//    nouveauGadget->setSkin ( m_interfaceParent->getSkin() );

    // renvois du nouveau gadget créé.
    return nouveauGadget;

}

/////////////////////////////////////////////////
template<typename T>
std::shared_ptr<T>  FabriqueBase::creerBandeau (){

    // Creation du nouveau gadget
    std::shared_ptr<T> nouveauGadget = std::make_shared<T>( );

    // La hierarchie
    m_interfaceParent->ajouter  ( nouveauGadget );
    nouveauGadget->setParent    ( m_interfaceParent );
//    m_interfaceParent->ms_calque_bandeaux->ajouter ( nouveauGadget );

    // la reference à l'interface parent.
    nouveauGadget->setInterface( m_interfaceParent );
    m_interfaceParent->demanderActualisation();

    // renvois du nouveau gadget créé.
    return nouveauGadget;

}


/////////////////////////////////////////////////
template<typename T>
std::shared_ptr<T>  FabriqueBase::creerPanneau (){

    // Creation du nouveau gadget
    std::shared_ptr<T> nouveauGadget = std::make_shared<T>( );

    // La hierarchie
    m_interfaceParent->ajouter  ( nouveauGadget );
    nouveauGadget->setParent    ( m_interfaceParent );
//    m_interfaceParent->ms_calque_panneau_G->ajouter ( nouveauGadget );

    // la reference à l'interface parent.
    nouveauGadget->setInterface( m_interfaceParent );
    m_interfaceParent->demanderActualisation();

    // renvois du nouveau gadget créé.
    return nouveauGadget;

}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////
std::shared_ptr<AffRectangle>    FabriqueBase::rectangle( sf::Vector2i taille )
{

    m_interfaceParent->log ("Creation: rectangle" );
    auto nouveauGadget = creerBureau<AffRectangle>( );

    nouveauGadget->setTaille ( taille );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}

    std::shared_ptr<AffRectangle>    rectangle( float x = 100 , float y = 100 );


/////////////////////////////////////////////////
std::shared_ptr<AffRectangle>    FabriqueBase::rectangle( float x  , float y  )
{
    return rectangle( sf::Vector2i ( x , y ) );
}



/////////////////////////////////////////////////
std::shared_ptr<AffLabel>    FabriqueBase::label( std::string text )
{

    m_interfaceParent->log ("Creation: label" );
    auto nouveauGadget = creerBureau<AffLabel>( );

    nouveauGadget->setTexte ( text );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}

/////////////////////////////////////////////////
std::shared_ptr<AffImage>    FabriqueBase::image( std::string fichier )
{

    m_interfaceParent->log ("Creation: image" );
    auto nouveauGadget = creerBureau<AffImage>( );


    if ( fichier != "" )
        nouveauGadget->setImage ( fichier );

    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}



///////////////////////////////////////////////////
//std::shared_ptr<AffBarreTitre>    FabriqueBase::barreTitre( std::string text )
//{
//    auto nouveauGadget = creerBureau<AffBarreTitre>( );
////    nouveauGadget->setTexte ( text );
//    //nouveauGadget->demanderActualisation();
//    return nouveauGadget;
//}

/*
/////////////////////////////////////////////////
std::shared_ptr<AffImage>    FabriqueBase::image( int id )
{
    auto nouveauGadget = creerBureau<AffImage>( );
//    if ( fichier != "");
//        nouveauGadget->chargerDepuisFichier ( fichier );
    return nouveauGadget;
}
*/


/////////////////////////////////////////////////
std::shared_ptr<AffIcone>    FabriqueBase::icone( std::string fichier , unsigned int id )
{
    m_interfaceParent->log ("Creation: icone" );
    auto nouveauGadget = creerBureau<AffIcone>( );

    if ( fichier != "")
        nouveauGadget->setImage ( fichier );
    nouveauGadget->setIndex ( id );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}



/////////////////////////////////////////////////
std::shared_ptr<BtnRectangle>    FabriqueBase::boutonRect( float x , float y )
{
    return boutonRect( sf::Vector2i ( x , y ) );
}



/////////////////////////////////////////////////
std::shared_ptr<BtnRectangle>    FabriqueBase::boutonRect( sf::Vector2i taille )
{
    m_interfaceParent->log ("Creation: bouton rectangle" );
    auto nouveauGadget = creerBureau<BtnRectangle>( );


    nouveauGadget->setTaille ( taille );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}



/////////////////////////////////////////////////
std::shared_ptr<BtnTexte>    FabriqueBase::boutonTexte( std::string texte )
{
    m_interfaceParent->log ("Creation: bouton texte");
    auto nouveauGadget = creerBureau<BtnTexte>( );

    if ( texte != "")
        nouveauGadget->setTexte ( texte );
    //nouveauGadget->demanderActualisation();

    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<BtnIcone>    FabriqueBase::boutonIcone( std::string fichier )
{
    m_interfaceParent->log ("Creation: bouton icone");
    auto nouveauGadget = creerBureau<BtnIcone>( );
    if ( fichier != "")
        nouveauGadget->setImage ( fichier );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;

}



/////////////////////////////////////////////////
std::shared_ptr<BtnIcone>    FabriqueBase::boutonIcone( sf::Texture* texture  )
{
    m_interfaceParent->log ("Creation: bouton icone");
    auto nouveauGadget = creerBureau<BtnIcone>( );

    nouveauGadget->setImage ( texture );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;

}




/*
/////////////////////////////////////////////////
std::shared_ptr<BtnRectangle>    FabriqueBase::bouton( sf::Vector2i taille )
{
    auto nouveauGadget = creerBureau<BtnRectangle>( );
    nouveauGadget->setTaille ( taille );
    return nouveauGadget;
}*/

/////////////////////////////////////////////////
std::shared_ptr<BtnMenu>   FabriqueBase::menu( )
{
    auto nouveauGadget = creerBureau<BtnMenu>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<DnCaseACocher>        FabriqueBase::btnACocher( std::string texte, bool val )
{
    auto nouveauGadget = creerBureau<DnCaseACocher>( );
    nouveauGadget->setValeur ( val );
    nouveauGadget->setTexte ( texte );

    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<DnZoneTexte>        FabriqueBase::zoneTexte( std::string texte )
{
    auto nouveauGadget = creerBureau<DnZoneTexte>( );
    nouveauGadget->setTexte ( texte );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}

/////////////////////////////////////////////////
std::shared_ptr<DnZoneNum>        FabriqueBase::zoneNum( float valeurInitial ,float min , float max , float pas )
{
    auto nouveauGadget = creerBureau<DnZoneNum>( );
    nouveauGadget->setValeur ( valeurInitial );
    nouveauGadget->setMin ( min );
    nouveauGadget->setMax ( max );
    nouveauGadget->setPas ( pas );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}



/////////////////////////////////////////////////
std::shared_ptr<DnGlissere>        FabriqueBase::slider( )
{
    m_interfaceParent->log ("Creation: slider");
    auto nouveauGadget = creerBureau<DnGlissere>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}


///////////////////////////////////////////////////
//std::shared_ptr<DnBarreDefilement>        FabriqueBase::barreDefilement( )
//{
//    auto nouveauGadget = creerBureau<DnBarreDefilement>( );
//    return nouveauGadget;
//}

/////////////////////////////////////////////////
std::shared_ptr<BtnBarreFonctions>    FabriqueBase::barreFonctions(  )
{
    auto nouveauGadget = creerGadget<BtnBarreFonctions>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<BtnBarreFonctions>    FabriqueBase::barreOutils(  )
{
    auto nouveauGadget = creerGadget<BtnBarreFonctions>( );
    //nouveauGadget->demanderActualisation();
    nouveauGadget->setModeOutils();
    return nouveauGadget;
}




/////////////////////////////////////////////////
std::shared_ptr<Contenant>        FabriqueBase::contenant( )
{
    auto nouveauGadget = creerBureau<Contenant>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}

/////////////////////////////////////////////////
std::shared_ptr<CntSliders>        FabriqueBase::groupeSliders( )
{
    auto nouveauGadget = creerBureau<CntSliders>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}


/////////////////////////////////////////////////
std::shared_ptr<Fenetre>        FabriqueBase::fenetre( std::string titre )
{
    auto nouveauGadget = creerFenetre<Fenetre>( );
    nouveauGadget->setTitre (titre);
    return nouveauGadget;
}


///////////////////////////////////////////////////
//
//std::shared_ptr<FenRedim>        FabriqueBase::fenetreRedim( std::string titre  )
//{
//    auto nouveauGadget = creerFenetre<FenRedim>( );
//    nouveauGadget->setTexte (titre);
//    return nouveauGadget;
//}
//
//
//
///////////////////////////////////////////////////
//std::shared_ptr<FenPanneau>    FabriqueBase::panneau( std::string titre  )
//{
//    auto nouveauGadget = creerGadget<FenPanneau>( );
//    nouveauGadget->setTexte (titre);
//    return nouveauGadget;
//}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////
std::shared_ptr<LstSimple>    FabriqueBase::liste(  )
{
    auto nouveauGadget = creerBureau<LstSimple>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}



/////////////////////////////////////////////////
std::shared_ptr<LstDeroulante>    FabriqueBase::listeDeroulante(  )
{
    auto nouveauGadget = creerBureau<LstDeroulante>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////
std::shared_ptr<SupBandeau>    FabriqueBase::bandeau(  )
{
    auto nouveauGadget = creerBandeau<SupBandeau>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}
/////////////////////////////////////////////////
std::shared_ptr<SupBandeauMenusDeroulants>    FabriqueBase::menusDeroulants(  )
{
//    auto nouveauGadget = creerBandeau<SupBandeauMenusDeroulants>( );

    std::shared_ptr<SupBandeauMenusDeroulants> nouveauGadget = std::make_shared<SupBandeauMenusDeroulants>( );

    // La hierarchie
//    m_interfaceParent->ms_calque_bandeauMenuDeroulants->ajouter ( nouveauGadget );

    // la reference à l'interface parent.
    nouveauGadget->setInterface( m_interfaceParent );


    return nouveauGadget;
}



/////////////////////////////////////////////////
std::shared_ptr<SupPanneau>    FabriqueBase::supportPanneaux(  )
{
    auto nouveauGadget = creerPanneau<SupPanneau>( );
    //nouveauGadget->demanderActualisation();
    return nouveauGadget;
}


}; // fin namespace gui















