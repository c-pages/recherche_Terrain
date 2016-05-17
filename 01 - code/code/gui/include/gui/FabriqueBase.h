#ifndef FABRIQUEBASE_H
#define FABRIQUEBASE_H

#include "SFML/Graphics.hpp"
#include "memory"


#include "interfaces/Gadget.h"

// AFFICHAGES
#include "gadgets\AffRectangle.h"
#include "gadgets\AffLabel.h"
#include "gadgets\AffImage.h"
#include "gadgets\AffIcone.h"


// BOUTONS
#include "gadgets\BtnRectangle.h"
#include "gadgets\BtnTexte.h"
#include "gadgets\BtnIcone.h"



// DONNEES
#include "gadgets\DnCaseACocher.h"
#include "gadgets\DnZoneTexte.h"
#include "gadgets\DnGlissere.h"
#include "gadgets\DnZoneNum.h"

// LISTES
#include "gadgets\LstSimple.h"
#include "gadgets\LstDeroulante.h"


// FENTRES
#include "gadgets\Fenetre.h"

#include "gadgets\BtnBarreFonctions.h"




// OUTILS
// a retirer de la liste des creations
//#include "gadgets/outils\AffBarreTitre.h"
#include "gadgets/outils\BtnMenu.h"

#include "gadgets/outils\CntSliders.h"

#include "gadgets/outils\SupBandeau.h"
#include "gadgets/outils\SupBandeauMenusDeroulants.h"
#include "gadgets/outils\SupPanneau.h"

#include "interfaces\gadgets/Contenant.h"


namespace gui{


/////////////////////////////////////////////////
/// \brief Fabrique de gadgets de base (cf. GOF: Fabrique)
///
/////////////////////////////////////////////////
class FabriqueBase
{
private:

    template<typename T>
    std::shared_ptr<T>  creerGadget ();

    template<typename T>
    std::shared_ptr<T>  creerBureau ();

    template<typename T>
    std::shared_ptr<T>  creerFenetre ();

    template<typename T>
    std::shared_ptr<T>  creerBandeau ();

    template<typename T>
    std::shared_ptr<T>  creerPanneau ();

public:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AFFICHAGES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    FabriqueBase ( Interface* interfaceParent );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un simple rectangle
    ///
    /// \param taille
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<AffRectangle>    rectangle( sf::Vector2i taille = {100,100} );
    std::shared_ptr<AffRectangle>    rectangle( float x = 100 , float y = 100 );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un simple label
    ///
    /// \param text
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<AffLabel>    label( std::string text = "Label" );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une simple image
    ///
    /// \param fichier
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<AffImage>    image( std::string fichier = "" );
/*
    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une simple image
    ///
    /// \param fichier
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<AffImage>    image( int id );*/

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une simple ic�ne
    ///
    /// \param fichier
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<AffIcone>    icone( std::string fichier = "" , unsigned int id = 1 );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une simple ic�ne
    ///
    /// \param fichier
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
//    std::shared_ptr<AffBarreTitre>    barreTitre( std::string fichier = ""  );



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BOUTONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un simple bouton texte
    ///
    /// \param texte
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<BtnTexte>    boutonTexte( std::string texte = "" );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un simple bouton rectangulaire
    ///
    /// \param taille
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<BtnRectangle>    boutonRect( sf::Vector2i taille );
    std::shared_ptr<BtnRectangle>    boutonRect( float x , float y );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un simple bouton rectangulaire
    ///
    /// \param taille
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<BtnIcone>    boutonIcone( std::string texte = "" );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un simple bouton rectangulaire
    ///
    /// \param taille
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<BtnIcone>    boutonIcone ( sf::Texture* texture );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un Menu
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<BtnMenu>        menu( );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DONNEES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un bouton interrupteur ( bool )
    ///
    /// \param val
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<DnCaseACocher>        btnACocher( std::string texte = "", bool val = true );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une zone de texte
    ///
    /// \param texte
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<DnZoneTexte>        zoneTexte( std::string texte = "zone de texte" );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une zone de texte
    ///
    /// \param texte
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<DnZoneNum>        zoneNum( float valeurInitial = 12345 ,float min = 0, float max = 100000, float pas = 1 );



    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un slider
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<DnGlissere>        slider( );

//    /////////////////////////////////////////////////
//    /// \brief  Cr�ation d'une barre de defilement pour deplacer un contenu � l'interieur d'un panneau
//    ///
//    /// \return Un pointeur vers le nouveau gadget.
//    /////////////////////////////////////////////////
//    std::shared_ptr<DnBarreDefilement>        barreDefilement( );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une barre de defilement pour deplacer un contenu � l'interieur d'un panneau
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<BtnBarreFonctions>        barreFonctions( );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une barre de defilement pour deplacer un contenu � l'interieur d'un panneau
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<BtnBarreFonctions>        barreOutils( );
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GROUPEMENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un panneau
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<Contenant>        contenant( );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un panneau
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<CntSliders>        groupeSliders( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Liste
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une liste
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<LstSimple>        liste( );

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'une liste deroulante
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<LstDeroulante>   listeDeroulante( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FENETRES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un panneau
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<Fenetre>        fenetre( std::string titre = "Fen�tre" );


//    /////////////////////////////////////////////////
//    /// \brief  Cr�ation d'un panneau
//    ///
//    /// \return Un pointeur vers le nouveau gadget.
//    /////////////////////////////////////////////////
//    std::shared_ptr<FenRedim>        fenetreRedim( std::string titre = "Fen�tre" );


//    /////////////////////////////////////////////////
//    /// \brief  Cr�ation d'un panneau
//    ///
//    /// \return Un pointeur vers le nouveau gadget.
//    /////////////////////////////////////////////////
//    std::shared_ptr<FenPanneau>        panneau( std::string titre = "Panneau" );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SUPPORTS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un panneau
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<SupBandeau>        bandeau( );


    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un panneau
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<SupBandeauMenusDeroulants>    menusDeroulants(  );



    /////////////////////////////////////////////////
    /// \brief  Cr�ation d'un panneau
    ///
    /// \return Un pointeur vers le nouveau gadget.
    /////////////////////////////////////////////////
    std::shared_ptr<SupPanneau>        supportPanneaux( );





/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////

    Interface*      m_interfaceParent;





};

}; // fin namespace gui

#endif // FABRIQUEBASE_H
