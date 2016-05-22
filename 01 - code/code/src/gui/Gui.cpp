/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////

#include <iostream>

#include <gui/Gui.h>
#include <gui/Calque.h>
#include <gui/Fabrique.h>


namespace gui {

sf::RenderWindow *  Gui::ms_fenetre = nullptr;



/////////////////////////////////////////////////
Gui::Gui ( sf::RenderWindow* fenetre )
: creer             ( this )
, m_calqueFond      ( std::make_shared<Calque>() )
, m_calqueFenetres  ( std::make_shared<Calque>() )
, m_gadgetSurvole   ( nullptr )
, m_gadgetPresse    ( nullptr )
{

    // la fenetre SFML
    ms_fenetre = fenetre;

    /// Initialisation des claques
    ajouterEnfant( m_calqueFond );
    ajouterEnfant( m_calqueFenetres );

    m_calqueFond->setSize ( { ms_fenetre->getSize().x, ms_fenetre->getSize().y } );
    m_calqueFenetres->setSize ( { ms_fenetre->getSize().x, ms_fenetre->getSize().y } );
}


/////////////////////////////////////////////////
void Gui::retirerEnfant ( std::shared_ptr<Gadget> cible )
{
    /// on ne retire pas directement l'enfant dans m_enfants mais dans les calques.
    m_calqueFenetres->retirerEnfant ( cible );
    m_calqueFond->retirerEnfant     ( cible );
}












/////////////////////////////////////////////////
Gadget* Gui::chercherGadgetSurvole ()
//std::shared_ptr<Gadget> Gui::chercherGadgetSurvole ()
{
//                std::cout << "chercherGadgetSurvole\n";
    sf::Vector2i posSouris = sf::Mouse::getPosition( *ms_fenetre );

    for (  int i =  m_enfants.size()-1 ; i>=0 ; i--){
        auto enfant = m_enfants[i];
        if ( enfant->testerSurvol ( posSouris ) != nullptr )
            return enfant->testerSurvol ( posSouris );
    }



    return nullptr;
}

/////////////////////////////////////////////////
void Gui::traiterEvenements (sf::Event evenement)
{
    /// on gère les actions liés au claviers
    if ( evenement.type == sf::Event::KeyPressed )
        traiterEvenementsClavier( evenement );

    /// on traite les évènements des enfants
    Gadget::traiterEvenements ( evenement );

    /// les gadgets survolé et survolé back
    auto boutonSurvoleBack = m_gadgetSurvole;
    m_gadgetSurvole = chercherGadgetSurvole ();


    /// les evenements 'souris' de l'interface
    switch ( evenement.type ){

        ///////// Deplacement souris /////////////////////////////////////////
        case sf::Event::MouseMoved :

            // On sort si on a pas changé de bouton survolé
            if ( m_gadgetSurvole ==  boutonSurvoleBack )
                return;

            // on gère le gadget anciennement survolé
            if (m_gadgetPresse == nullptr )
                if ( boutonSurvoleBack!=nullptr)
                    boutonSurvoleBack->setEtat( Gadget::Etat::Repos );

            // on gère le gadget survolé
            if (m_gadgetSurvole != nullptr)
                m_gadgetSurvole->setEtat( Gadget::Etat::Survol );

//          if ( m_gadgetSurvole->estInteractif() )*/ {
//              m_gadgetSurvole->declencher ( Evenement::on_entrer );
//          }

        break;

        ///////// Presser bouton souris /////////////////////////////////////////
        case sf::Event::MouseButtonPressed:

//            // On declenche pour tout les autre boutons 'relacherDehors'
//            if ( evenement.mouseButton.button == sf::Mouse::Left )
//                declencherToutBoutons ( Evenement::onBtnG_presserDehors  , m_gadgetSurvole );
//            else if ( evenement.mouseButton.button == sf::Mouse::Right )
//                declencherToutBoutons ( Evenement::onBtnD_relacherDehors  , m_gadgetSurvole );

            // On sort si on a pas de bouton survolé
            if ( m_gadgetSurvole ==  nullptr )
                return;

            // on definie le bouton pressé
            m_gadgetPresse = m_gadgetSurvole;

//            if ( m_gadgetPresse->estInteractif() ) {
//
////                logEvt ( "Presser Bouton" , m_gadgetPresse );
//
                // On déclenche l'action en fonction du bouton de la souris
                if ( evenement.mouseButton.button == sf::Mouse::Left ) {
                    m_gadgetPresse->declencher ( Evenement::onBtnG_presser );
                    m_gadgetPresse->setEtat ( Gadget::Etat::Presse );
                } else if ( evenement.mouseButton.button == sf::Mouse::Right ) {
                    m_gadgetPresse->declencher ( Evenement::onBtnD_presser );
                } else if ( evenement.mouseButton.button == sf::Mouse::Middle ) {
                    m_gadgetPresse->declencher ( Evenement::onBtnM_presser );
                }
//            }
        break;

        ///////// Relacher bouton souris /////////////////////////////////////////
        case sf::Event::MouseButtonReleased:

//            // on declenche l'evenement RELACHER DEHORS
//            if ( evenement.mouseButton.button == sf::Mouse::Left )
//                declencherToutBoutons  ( Evenement::onBtnG_relacherDehors , m_gadgetPresse );
//            else if ( evenement.mouseButton.button == sf::Mouse::Right )
//                declencherToutBoutons  ( Evenement::onBtnD_relacherDehors , m_gadgetPresse);
//            else if ( evenement.mouseButton.button == sf::Mouse::Middle )
//                declencherToutBoutons  ( Evenement::onBtnM_relacherDehors , m_gadgetPresse);


            // si on a pas pressé de bouton, on passe
            if ( m_gadgetPresse ==  nullptr )
                return;

            // On survol le bouton pressé
            if ( m_gadgetSurvole ==  m_gadgetPresse ){


                // on declenche l'evenement RELACHER DEDANS
                if ( evenement.mouseButton.button == sf::Mouse::Left )
                    m_gadgetPresse->declencher  ( Evenement::onBtnG_relacher );
                else if ( evenement.mouseButton.button == sf::Mouse::Right )
                    m_gadgetPresse->declencher  ( Evenement::onBtnD_relacher );
                else if ( evenement.mouseButton.button == sf::Mouse::Middle )
                    m_gadgetPresse->declencher  ( Evenement::onBtnM_relacher );

            // sinon c'est quon relache dehors
            } else {
                if ( evenement.mouseButton.button == sf::Mouse::Left )
                    m_gadgetPresse->declencher  ( Evenement::onBtnG_relacherDehors );
            }


            // on reset m_boutonPressé
            m_gadgetPresse->setEtat(Gadget::Etat::Repos);
            m_gadgetPresse = nullptr;


        break;

        ///////// Presser roulette souris /////////////////////////////////////////
        case sf::Event::MouseWheelMoved :

            // Si on survole un bouton
            if ( m_gadgetSurvole != nullptr ){

                // On déclenche l'action en fonction
                if ( evenement.mouseWheel.delta > 0 )
                    m_gadgetSurvole->declencher ( Evenement::onBtnM_roulerHaut );
                else
                    m_gadgetSurvole->declencher ( Evenement::onBtnM_roulerBas );
            }

        break;

        ///////// on ne traite pas les autres types d'évènements /////////////////////////////////////////
        default: break;


    }


}


/////////////////////////////////////////////////
void Gui::actualiser ()
{
//    std::cout << "Gui::actualiser\n";

}



/////////////////////////////////////////////////
sf::Vector2i Gui::getSourisPosition ()
{
    return sf::Mouse::getPosition( *ms_fenetre );
}

/////////////////////////////////////////////////
sf::RenderWindow* Gui::getFenetreSFML (){
    return ms_fenetre;
}

} // fin namespace gui

