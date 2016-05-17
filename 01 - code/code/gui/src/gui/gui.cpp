#include "gui.h"




#include <iostream>
#include <stdio.h>

namespace gui {


sf::RenderWindow*                           Interface::ms_fenetreSFML   = nullptr;
ResourcesMgr<sf::Font,std::string >         Interface::ms_polices       = {};
ResourcesMgr<sf::Texture,   std::string >   Interface::ms_images        = {};
ResourcesMgr<sf::Texture,   std::string >   Interface::ms_curseurs      = {};
ResourcesMgr<sf::Texture,   std::string >   Interface::ms_icones        = {};
/*
std::shared_ptr<Calque>        Interface::ms_calque_bandeaux                = std::make_shared<Calque>("_Bandeaux");
std::shared_ptr<Calque>        Interface::ms_calque_panneau_G               = std::make_shared<Calque>("_PanneauG");
std::shared_ptr<Calque>        Interface::ms_calque_panneau_D               = std::make_shared<Calque>("_PanneauD");
std::shared_ptr<Calque>        Interface::ms_calque_bandeauMenuDeroulants   = std::make_shared<Calque>("_BandeauMD");
std::shared_ptr<Calque>        Interface::ms_calque_menuDeroulants          = std::make_shared<Calque>("_Menus");
*/
std::shared_ptr<Calque>        Interface::ms_calque_bureau                  = std::make_shared<Calque>("_Bureau");
std::shared_ptr<Calque>        Interface::ms_calque_fenetres                = std::make_shared<Calque>("_Fenetres");
std::shared_ptr<Calque>        Interface::ms_calque_infos                   = std::make_shared<Calque>("_Infos");
std::shared_ptr<Calque>        Interface::ms_calque_souris                  = std::make_shared<Calque>("_Souris");
std::shared_ptr<AffCurseurSouris>       Interface::ms_curseurSouris;
bool                                    Interface::ms_necessiteActualisation = false;

std::shared_ptr<Gadget>         Interface::ms_boutonSurvole = nullptr;    ///< Le bouton survolé actuelement par la souris.
std::shared_ptr<Gadget>         Interface::ms_boutonPresse  = nullptr;    ///< Le bouton pressé actuelement par la souris.

/////////////////////////////////////////////////
Interface::Interface( sf::RenderWindow* fenetre )
: Gadget ()
, m_fenetre         ( fenetre )
, creer             ( this )

// fPS
, m_afficherFPS     ( true )
, m_labelFPS        ( )
, m_textFPS         ( "FPS: " )
, m_compteurFPS     ( 0 )

// btn survol
, m_afficherBoutonSurvol    ( false )
, m_labelBoutonSurvol       ( )
, m_textBoutonSurvol        ( "Gadget : ")

//// infoBulle
//, m_infoBulle      ( std::make_shared<AffInfoBulle>() )
, m_infoActif ( false )
{
    m_mute          = true;
    m_nom           = "GUI";
    m_taille        = { 1920 , 1080 };
    ms_fenetreSFML  = fenetre;
    m_parent        = nullptr;



    // reset du nombre de gadgets
    ms_CompteurGadgets = 0;
/*
    // les calques
    ajouter ( ms_calque_panneau_G );
    ajouter ( ms_calque_panneau_D );
    ajouter ( ms_calque_bandeaux );
    ajouter ( ms_calque_bandeauMenuDeroulants );
    ajouter ( ms_calque_menuDeroulants );
*/
    ajouter ( ms_calque_bureau );
    ajouter ( ms_calque_fenetres );
    ajouter ( ms_calque_infos );
    ajouter ( ms_calque_souris );

    // initialiser les polices
    ms_polices.load( "Defaut"   , "media/polices/consola.ttf"   );
    ms_polices.load( "arial"    , "media/polices/arial.ttf"     );
    ms_polices.load( "swisse"   , "media/polices/swisse.ttf"    );
    ms_polices.load( "syastro"  , "media/polices/syastro_.ttf"  );

    // initialiser les icones
    ms_icones.load( "ico_fenetre"           , "media/img/icones_fenetre.png" );
    ms_icones.load( "ico_fenetreDefaut"     , "media/img/ico_fenetre.png" );
    ms_icones.load( "ico_fleches"           , "media/img/ico_fleches.png"    );
    ms_icones.load( "ico_fichiers"          , "media/img/ico_fichiers.png"    );
    ms_icones.load( "ico_historique"        , "media/img/ico_Historique.png"    );

    // initialiser les curseurs
    ms_curseurSouris = std::make_shared<AffCurseurSouris>( this );
    ms_calque_souris->ajouter(ms_curseurSouris);
    ms_curseurs.load( "Redimensionnement"  , "media/img/curs_redimensionnement.png" );

    // InfoBulle
    m_infoBulle     = std::make_shared<AffInfoBulle>() ;
    ms_calque_infos->ajouter( m_infoBulle );
    m_chronoDeclenchementInfo.restart();



    //// RETOURS ////
    // initialiser les trucs FPS
    m_labelFPS.setFont              ( ms_polices.get    ( "swisse" ) );
    m_labelFPS.setCharacterSize     ( 9 );
    m_labelFPS.setColor             ( sf::Color::White );
    m_labelFPS.setString            ( "..." );

    // initialiser les trucs bouton survol
    m_labelBoutonSurvol.setFont              ( ms_polices.get    ( "swisse" ) );
    m_labelBoutonSurvol.setCharacterSize     ( 9 );
    m_labelBoutonSurvol.setColor             ( sf::Color::White );
    m_labelBoutonSurvol.setString            ( "..." );



}

/////////////////////////////////////////////////
void Interface::reinitialiser ()
{
    // on vide les calques
    for (auto calque : m_enfants)
        calque->viderEnfants();

    // on vide les liaisons
    viderLiaisons();


}



/////////////////////////////////////////////////
std::shared_ptr<Gadget> Interface::chercherGadgetSurvole ()
{
//    log ("chercherGadgetSurvole");
    sf::Vector2i posSouris = sf::Mouse::getPosition( *m_fenetre );

    for (int i=m_enfants.size()-1; i>=0; i-- )    {
        auto enfant = m_enfants[i];
        std::shared_ptr<Gadget> result = enfant->testerSurvol ( posSouris );
        if ( result != nullptr ) return result;
    }

    return nullptr;
}


/////////////////////////////////////////////////
void Interface::actualiser ()
{
    // les FPS
    if ( m_afficherFPS )
        calculerFPS();

    // retour infos gadget survol
    if ( m_afficherBoutonSurvol )
        majAffichage_BoutonSurvol();

    // infobulle
    if ( m_chronoDeclenchementInfo.getElapsedTime().asSeconds() > 1
    &&   ms_boutonSurvole != nullptr
    &&  !m_infoActif ) {
        if ( ms_boutonSurvole->getInfo() != "" ) {
            m_infoBulle->setVisible ();
            m_infoActif = true;
            m_infoBulle->setPosition ( getPosSouris().x, getPosSouris().y + 20 );
            m_infoBulle->setTexte  ( ms_boutonSurvole->getInfo() );
        }
    }









    // si pas besoin on zappe
    if ( ! ms_necessiteActualisation )
        return;



//    // debut de la frame, on saute des lignes
//    log      (  "\n\n" );

    logTitre ( "Actualiser");


    // on calcule la taille verticale des bandeaux ...
    sf::Vector2f decallage = {0,0};
/*    for ( auto MenuDeroulant : ms_calque_bandeauMenuDeroulants->getEnfants() )
    {
        MenuDeroulant->setPosition (decallage.x, decallage.y);
        MenuDeroulant->setTailleX ( m_fenetre->getSize().x );
        decallage.y += MenuDeroulant->getTaille().y;
    }
    for ( auto bandeau : ms_calque_bandeaux->getEnfants() )
    {
        bandeau->setPosition (decallage.x, decallage.y);
        bandeau->setTailleX ( m_fenetre->getSize().x );
        decallage.y += bandeau->getTaille().y;
    }

    for ( std::shared_ptr<Gadget> panneau : ms_calque_panneau_G->getEnfants() )
    {

        panneau->setPosition ( decallage.x , decallage.y );
        //panneau->setTailleX ( 250 );
        panneau->setTailleY ( m_fenetre->getSize().y - decallage.y );
        decallage.x += panneau->getTaille().x;

    }

    // ... pour décaller le calque du bureau ... à voir si c'est pas le bordel
    ms_calque_bureau->setPosition ( decallage.x , decallage.y );
    decallage.x = 0;
    for ( std::shared_ptr<Gadget> panneau : ms_calque_panneau_D->getEnfants() )
    {

        decallage.x += panneau->getTaille().x;
        panneau->setPosition ( m_fenetre->getSize().x -  decallage.x , decallage.y );
        //panneau->setTailleX ( 250 );
        panneau->setTailleY ( m_fenetre->getSize().y - decallage.y );

    }
*/

    ms_necessiteActualisation = false;


    // on actualise les enfants ( donc les calques)
    actualiserEnfants();


}

///////////////////////////////////////////////////
//void Interface::actualiser (sf::Time delta)
//{
//    for ( auto enfant : m_enfants )
//        enfant->actualiser( delta );
//}



/////////////////////////////////////////////////
void Interface::traiterEvenements( sf::Event evenement )
{
//    std::cout << "EVENEMTN--------------\n";
//    log ("Traiter les evenements");

    Gadget::traiterEvenements ( evenement );

    //////////////////////////////////////////
    // les evenements 'souris' de l'interface
    //////////////////////////////////////////
    auto boutonSurvoleBack = ms_boutonSurvole;
    ms_boutonSurvole = chercherGadgetSurvole ();



    switch ( evenement.type ){
        ///////// Deplacement souris /////////////////////////////////////////
        case sf::Event::MouseMoved :

            // On gere le cureur souris
            if (ms_curseurSouris->estVisible())
                ms_curseurSouris->traiterEvenements( evenement );

            // Info bulle, on relance le chrono
            if ( m_sourisPosBack != getPosSouris() ){
                m_chronoDeclenchementInfo.restart();
                m_infoBulle->setVisible ( false );
                m_infoActif = false;
            }
            m_sourisPosBack = getPosSouris();

            // On sort si on a pas changé de bouton survolé
            if ( ms_boutonSurvole ==  boutonSurvoleBack )
                return;


            if (ms_boutonPresse == nullptr )
            {

                // on gère le gadget anciennement survolé
                if (boutonSurvoleBack!=nullptr){
                    boutonSurvoleBack->setSurvol( false );
                    if ( boutonSurvoleBack->estInteractif() ){
                        logEvt ( "Sortir Bouton" , boutonSurvoleBack );
                        boutonSurvoleBack->declencher ( Evenement::on_sortir );
                    }
                }


                // on gère le gadget survolé
                if (ms_boutonSurvole != nullptr) {
                    ms_boutonSurvole->setSurvol( true );
                    if ( ms_boutonSurvole->estInteractif() ) {
                        ms_boutonSurvole->declencher ( Evenement::on_entrer );
                        logEvt ( "Entrer Bouton" , ms_boutonSurvole );
                    }
                }

            }





        break;

        ///////// Presser bouton souris /////////////////////////////////////////
        case sf::Event::MouseButtonPressed:


            // On declenche pour tout les autre boutons 'relacherDehors'
            if ( evenement.mouseButton.button == sf::Mouse::Left )
                declencherToutBoutons ( Evenement::onBtnG_presserDehors  , ms_boutonSurvole );
            else if ( evenement.mouseButton.button == sf::Mouse::Right )
                declencherToutBoutons ( Evenement::onBtnD_relacherDehors  , ms_boutonSurvole );

            // On sort si on a pas de bouton survolé
            if ( ms_boutonSurvole ==  nullptr )
                return;


            // on definie le bouton pressé
            ms_boutonPresse = ms_boutonSurvole;


            if ( ms_boutonPresse->estInteractif() ) {

                logEvt ( "Presser Bouton" , ms_boutonPresse );

                // On déclenche l'action en fonction du bouton de la souris
                if ( evenement.mouseButton.button == sf::Mouse::Left ) {
                    ms_boutonPresse->declencher ( Evenement::onBtnG_presser );
                    ms_boutonPresse->setPresse ( true );
                } else if ( evenement.mouseButton.button == sf::Mouse::Right ) {
                    ms_boutonPresse->declencher ( Evenement::onBtnD_presser );
                } else if ( evenement.mouseButton.button == sf::Mouse::Middle ) {
                    ms_boutonPresse->declencher ( Evenement::onBtnM_presser );
                }
            }
        break;

        ///////// Relacher bouton souris /////////////////////////////////////////
        case sf::Event::MouseButtonReleased:

            // on declenche l'evenement RELACHER DEHORS
            if ( evenement.mouseButton.button == sf::Mouse::Left )
                declencherToutBoutons  ( Evenement::onBtnG_relacherDehors , ms_boutonPresse );
            else if ( evenement.mouseButton.button == sf::Mouse::Right )
                declencherToutBoutons  ( Evenement::onBtnD_relacherDehors , ms_boutonPresse);
            else if ( evenement.mouseButton.button == sf::Mouse::Middle )
                declencherToutBoutons  ( Evenement::onBtnM_relacherDehors , ms_boutonPresse);


            // si on a pas pressé de bouton, on passe
            if ( ms_boutonPresse ==  nullptr )
                return;

            // On survol le bouton pressé
            if ( ms_boutonSurvole ==  ms_boutonPresse ){

                // on declenche l'evenement RELACHER DEDANS
                if ( evenement.mouseButton.button == sf::Mouse::Left )
                    ms_boutonPresse->declencher  ( Evenement::onBtnG_relacher );
                else if ( evenement.mouseButton.button == sf::Mouse::Right )
                    ms_boutonPresse->declencher  ( Evenement::onBtnD_relacher );
                else if ( evenement.mouseButton.button == sf::Mouse::Middle )
                    ms_boutonPresse->declencher  ( Evenement::onBtnM_relacher );

            // sinon c'est quon relache dehors
            } else {
                if ( evenement.mouseButton.button == sf::Mouse::Left )
                    ms_boutonPresse->declencher  ( Evenement::onBtnG_relacherDehors );
            }


            // on reset m_boutonPressé
            ms_boutonPresse->setPresse( false );
            ms_boutonPresse->setSurvol( false );
            ms_boutonPresse = nullptr;


        break;

        ///////// Presser roulette souris /////////////////////////////////////////
        case sf::Event::MouseWheelMoved :

            // Si on survole un bouton
            if ( ms_boutonSurvole != nullptr ){

                // On déclenche l'action en fonction
                if ( evenement.mouseWheel.delta > 0 )
                    ms_boutonSurvole->declencher ( Evenement::onBtnM_roulerHaut );
                else
                    ms_boutonSurvole->declencher ( Evenement::onBtnM_roulerBas );
            }

        break;

        ///////// on ne traite pas les autres types d'évènements /////////////////////////////////////////
        default: break;


    }

}


/////////////////////////////////////////////////
void Interface::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    // On dessine les gadgets de l'interface
    for (auto enfant : m_enfants )
        target.draw(*enfant, states);

    // On dessine l'affichage FPS si besoin
    if ( m_afficherFPS )
        target.draw( m_labelFPS, states);

    // On dessine le gadget survolé si beaoisn
    if ( m_afficherBoutonSurvol )
        target.draw( m_labelBoutonSurvol, states);

}

/////////////////////////////////////////////////
void Interface::majAffichage_BoutonSurvol(){
    std::string      txt;

    if ( ms_boutonSurvole != nullptr )
        txt =  ms_boutonSurvole->getHierarchie() + ms_boutonSurvole->getNom();
    else txt = "...";


    m_labelBoutonSurvol.setString ( m_textBoutonSurvol + txt );
    m_labelBoutonSurvol.setPosition     ( m_fenetre->getSize().x - 600 , 4 ) ;
}



/////////////////////////////////////////////////
void Interface::calculerFPS(){
    m_compteurFPS++;
    if ( m_chronoFPS.getElapsedTime().asSeconds() > 1)    {
        std::string txtAAfficher = m_textFPS;
        m_chronoFPS.restart();
        txtAAfficher += patch::to_string(m_compteurFPS);
        m_compteurFPS = 0;
        m_labelFPS.setString ( txtAAfficher );
    }

    m_labelFPS.setPosition              ( m_fenetre->getSize().x - 650 , 4 ) ;

}

/////////////////////////////////////////////////
void Interface::declencherToutBoutons ( Evenement evenement , std::shared_ptr<Gadget> saufGadget )
{
    if ( saufGadget != nullptr ){
        for ( auto bouton : Bouton::ms_boutons )
            if ( bouton->getNom() != saufGadget->getNom() )
                bouton->declencher( evenement );
    } else for ( auto bouton : Bouton::ms_boutons )
        bouton->declencher( evenement );

}

/////////////////////////////////////////////////
sf::Vector2i Interface::getTaille() const {
    return { ms_fenetreSFML->getSize().x, ms_fenetreSFML->getSize().y };
}

} // fin namespace
