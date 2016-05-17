/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gadgets/Fenetre.h"
#include "gadgets/decorations/FenDecoDrag.h"
#include "gadgets/decorations/FenDecoRedim.h"
#include "gadgets/decorations/FenDecoRedimPanneau.h"

#include <gui.h>

#include "gadgets/outils/CntSliders.h"
//#include <CntSimple.h>


namespace gui {

/////////////////////////////////////////////////
Fenetre::Fenetre ()
: m_contenant       ( std::make_shared<CntSliders>() )
//: m_contenant       ( std::make_shared<CntSliders>() )
{
    creerNomUnique ( "Fenetre");

    // debug
//    m_mute = false;

    // initialiser les composants herités
    CmpOmbre::initialiserComposants ( this );
    CmpFond::initialiserComposants ( this );
    CmpBarreTitre::initialiserComposants ( this );

    // les composants
    ajouterComposant( m_contenant );

    m_taille = { 350 , 200 };
//    m_marge = {20,20};
    m_redimensionnable = true;
    m_deplacable = true;

    // les decorations
    if ( m_redimensionnable )
        ajouterDecoration ( Decorations::Retaille );

    if ( m_deplacable )
        ajouterDecoration ( Decorations::Drag );

    // les couleurs
    m_contenantFndCouleur             = sf::Color( 70,70,70, 255 );
    m_contenantFndLgnCouleur          = sf::Color( 90,90,90 );
    m_contenantFndLgnepaisseur        = 0;

    m_contenantContenantCouleur       = sf::Color( 255,255,255, 255 );
    m_contenantContenantLgnCouleur    = sf::Color( 90,90,90, 255 );
    m_contenantContenantLgnepaisseur  = 0;

    m_fondCouleur                   = sf::Color( 60,60,60, 255 );
    m_fondLgnCouleur                = sf::Color( 90,90,90, 255 );
    m_fondLgnEpaisseur              = 1;

    // les boutons



}





/////////////////////////////////////////////////
void Fenetre::fermer(){

    log("fermer");

    // declencher evenement
    declencher ( Evenement::onFen_fermer );

    // soit juste on le cache
    setVisible( false);

    // soit on le supprime carrement ... avoir
    // demander_aEtre_supprimer ();

}

/////////////////////////////////////////////////
void Fenetre::reduire(){
    log("reduire");
}



/////////////////////////////////////////////////
void Fenetre::ajouterDecoration ( Decorations deco  )
{
    // si il est deja dans la liste on zappe.
    if ( m_decorations.find( deco ) != m_decorations.end() )
        return;

    switch ( deco )    {
        case Decorations::Drag:
            m_decorations.insert( { deco , std::make_shared<FenDecoDrag> ( this ) } );
            break;
        case Decorations::Retaille:
            m_decorations.insert( { deco , std::make_shared<FenDecoRedim> ( this ) } );
            break;
        case Decorations::RetaillePanneau:
            m_decorations.insert( { deco , std::make_shared<FenDecoRedimPanneau> ( this ) } );
            break;
        default:break;
    }
    demanderActualisation();
};

/////////////////////////////////////////////////
void Fenetre::setDeplacable( bool val  ){
    if ( val )
        ajouterDecoration ( Decorations::Drag );
    else
        retirerDecoration( Decorations::Drag );

    demanderActualisation();
}

/////////////////////////////////////////////////
void Fenetre::setRedimensionnable( bool val ){
    if ( val )
        ajouterDecoration ( Decorations::Retaille );
    else
        retirerDecoration( Decorations::Retaille );

    demanderActualisation();
};



/////////////////////////////////////////////////
void Fenetre::traiterEvenements (const sf::Event& evenement)
{
    for(auto deco : m_decorations)
        deco.second->traiterEvenements ( evenement );

    for ( auto enfant : m_enfants )
        enfant->traiterEvenements ( evenement);

    for ( auto composant : m_composants )
        composant->traiterEvenements ( evenement);

}


/////////////////////////////////////////////////
 sf::Vector2i  Fenetre::getTailleMini ()
{
    return  { m_titreIcone->getTaille().x + m_titreLabel->getTaille().x + 2 * m_btnFermer->getTaille().x + 3*m_titreMarge.x + 2*m_marge.x
            , m_titreFond->getTaille().y + 2*m_marge.y };
}


/////////////////////////////////////////////////
void Fenetre::setDefilementActif (bool val)
{

}

/////////////////////////////////////////////////
void Fenetre::ajouter ( std::shared_ptr<Gadget>  enfant )
{
    m_contenant->ajouter ( enfant );
//    if (m_parent != nullptr)
//        m_parent->actualiserContenu();
}


/////////////////////////////////////////////////
std::shared_ptr<Gadget> Fenetre::retirer (std::shared_ptr<Gadget> enfant)
{
    m_contenant->retirer ( enfant );
}



/////////////////////////////////////////////////
void Fenetre::actualiserEtatDeco ( )
{/*
    if ( m_parent != nullptr ){
        // si on est dans le calque fenetres on redimmenssione des 4 cotés
        if ( m_parent->getNom() == Interface::ms_calque_fenetres->getNom() ){
            retirerDecoration ( Decorations::RetaillePanneau );
            ajouterDecoration ( Decorations::Retaille );
        // sinon on est dans le calque panneau on redimmenssione par le bas
        } else {
            retirerDecoration ( Decorations::Retaille );
            ajouterDecoration ( Decorations::RetaillePanneau );
        }
    }*/
}



/////////////////////////////////////////////////
void Fenetre::actualiserGeometrie ()
{
//    std::cout << " Fenetre    ::ACTUALISERGEOMETRIE \n";

//    log ("ActualiserGEom");
    for(auto deco : m_decorations)
        deco.second->actualiserGeometrie ();

    // on actualise le titre
    CmpBarreTitre::actualiserGeometrie();

    m_contenant->setTaille    ( { m_taille.x - 2*m_marge.x, m_taille.y - m_titreFond->getTaille().y - 2*m_marge.y } );
    m_contenant->setPosition  ( m_marge.x , m_titreFond->getTaille().y + m_marge.y );


    m_fond->setTaille       ( m_taille );
    m_fond->setPosition     ( 0 , 0 );

    m_ombre->setTaille      ( m_taille );

    demanderActuaBounds();
}

/////////////////////////////////////////////////
void Fenetre::actualiserStyle ()
{

    for(auto deco : m_decorations)
        deco.second->actualiserStyle ();

    m_contenant->setFondCouleur            ( m_contenantFndCouleur ) ;
    m_contenant->setFondLigneCouleur       ( m_contenantFndLgnCouleur  ) ;
    m_contenant->setFondLigneEpaisseur     ( m_contenantFndLgnepaisseur  );
/*
    m_contenant->setContenantFillColor       ( m_contenantContenantCouleur ) ;
    m_contenant->setContenantOutlineColor    ( m_contenantContenantLgnCouleur  ) ;
    m_contenant->setContenantOutlineThickness( m_contenantContenantLgnepaisseur  );
*/

    // on actualise le titre
    CmpBarreTitre::actualiserStyle();

    // on actualise le fond
    m_fond->setFondCouleur          ( m_fondCouleur.repos );
    m_fond->setFondLigneCouleur     ( m_fondLgnCouleur.repos );
    m_fond->setFondLigneEpaisseur   ( m_fondLgnEpaisseur.repos );

}



} // fin namespace gui

