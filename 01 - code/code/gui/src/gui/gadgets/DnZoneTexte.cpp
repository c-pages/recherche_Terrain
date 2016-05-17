/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/DnZoneTexte.h>
#include <gui.h>


#include <string>

namespace gui {

/////////////////////////////////////////////////
DnZoneTexte::DnZoneTexte ()
: m_bouton          ( std::make_shared<BtnRectangle>() )
//, m_boutonSortir    ( std::make_shared<BtnRectangle>() )
, m_curseur         ( std::make_shared<AffRectangle>() )

//, m_label   ( std::make_shared<AffLabel>() )
, m_ecritureActive  ( false )
, m_numerique       ( false )
, m_clignotte       ( true )
, m_curseurPos      ( 0 )
{
    creerNomUnique ( "ZoneTexte");

    // initialiser
    m_taille.x = 180;
    m_taille.y = 15;

    m_marge.x = 2;
    m_marge.y = 0;

//    ajouterComposant( m_boutonSortir );
    ajouterComposant( m_bouton );
    CmpTexte::initialiserComposants( this );
    ajouterComposant( m_curseur );

    // valeurs par defaut
    m_btnCouleurs.set       ( sf::Color( 0,0,0,0 ) );
    m_btnCouleurs.set       ( sf::Color( 255,255,255 , 10 ), Etat::survol );
    m_btnCouleurs.set       ( sf::Color( 255,255,255 ), Etat::press );
    m_btnLgnCouleurs.set    ( sf::Color( 255,255,255, 20 ) );
    m_btnLgnepaisseurs.set  ( 1 );

    m_curseurCouleurs          = sf::Color(0,0,0,200) ;
    m_curseurLgnCouleurs       = sf::Color( 255,255,0, 255 ) ;
    m_curseurLgnepaisseurs     = 0 ;


    m_textCouleur.set( sf::Color::White );
    m_textCouleur.set( sf::Color::Black, Etat::press  );


    // Declaration des fonctions de l'interface interne du gadget.
    fn_valider      = [this](){
        if ( m_ecritureActive ){
            logEvt ( "valider" );
            setModeEcritureActif ( false );

            if ( m_numerique )
                m_texte = m_valeur = patch::to_float( m_label->getTexte() ) ;
            else
                m_texte = m_valeur = m_label->getTexte() ;

            m_curseur->setVisible ( false );

        }
        demanderActualisation();
    };
    fn_annuler       = [this](){

        if ( m_ecritureActive ){
            logEvt ( "annuler" );
            setModeEcritureActif ( false );
            m_label->setTexte ( m_texte );
            m_curseur->setVisible ( false );
        }
        demanderActualisation();
    };
    fn_cliqueTexte  = [this](){

        logEvt ( "M_texte" , m_texte );

        sf::Vector2i    posSouris = getPosSouris();
        posSouris.x -= getPosAbs().x;
        posSouris.y -= getPosAbs().y;

        m_curseurPos = m_label->getTexte().size()    ;

        for ( int i = 0; i<= m_label->getTexte().size(); i++ ){
            sf::Vector2f posLettre = m_label->getSFTexte().findCharacterPos 	(  i ) ;
            if ( posLettre.x>posSouris.x){
                m_curseurPos = i-1;
                break;
            }
        }

        // on active la saisie clavier
        setModeEcritureActif ( true ) ;

        m_clignotte = true;
        m_clignotteChrono.restart();
        demanderActualisation();
    };


    // Action des boutons
    m_bouton->lier ( Evenement::onBtnG_presser , fn_cliqueTexte );
    m_bouton->lier ( Evenement::onBtnG_presserDehors , fn_valider );
    m_bouton->lier ( Evenement::onBtnD_relacherDehors , fn_annuler );

    m_bouton->lier ( Evenement::onBtnM_roulerHaut , [this](){ declencher ( Evenement::onBtnM_roulerHaut ) ;} );
    m_bouton->lier ( Evenement::onBtnM_roulerBas , [this](){ declencher ( Evenement::onBtnM_roulerBas ) ;} );

    m_bouton->lier ( Evenement::on_entrer , [this](){ demanderActuaStyle() ;} );
    m_bouton->lier ( Evenement::on_sortir , [this](){ demanderActuaStyle() ;} );

    m_curseur->setVisible ( false );

}



/////////////////////////////////////////////////
void DnZoneTexte::actualiserGeometrie ()
{
    log ("actualiserGeometrie");

    m_bouton->setTaille ( m_taille );
    m_label->setPosition    ( m_marge.x , m_marge.y/2);

//    sf::Vector2f pos = m_label->getSFTexte()->findCharacterPos 	(  m_label->getTexte().size() ) ;
    sf::Vector2f pos = m_label->getSFTexte().findCharacterPos 	(  m_curseurPos ) ;

    m_curseur->setPosition ( pos.x , pos.y );
    m_curseur->move( 1 , m_marge.y/2 );
    m_curseur->setTaille( { 1, 15 });

//    m_boutonSortir->setPosAbs ( { 0,0 });
//    m_boutonSortir->setTaille ( Interface::ms_fenetreSFML->getSize().x, Interface::ms_fenetreSFML->getSize().y );

    demanderActuaBounds();
}


/////////////////////////////////////////////////
void DnZoneTexte::actualiserStyle ()
{
    log ("actualiserStyle");

//    m_etat = m_bouton->etat();

//    log ("etat()", int( etat() ));
//    log ("m_bouton->etat()", int( m_bouton->etat() ));
//    log ("m_btnCouleurs.get( etat())", ( m_btnCouleurs.get( etat()) ) );
//    log ("m_btnCouleurs.repos",  m_btnCouleurs.repos  );
//    log ("m_btnCouleurs.survol",  m_btnCouleurs.survol  );

    if ( m_ecritureActive ) {
        m_bouton->setFondCouleur            ( m_btnCouleurs.press ) ;
        m_bouton->setFondLigneCouleur       ( m_btnLgnCouleurs.press  ) ;
        m_bouton->setFondLigneEpaisseur     ( m_btnLgnepaisseurs.press  );

        CmpTexte::appliquerEtat( Etat::press );

    } else {
        m_bouton->setFondCouleur            ( m_btnCouleurs.get( m_bouton->etat() ) ) ;
        m_bouton->setFondLigneCouleur       ( m_btnLgnCouleurs.get( m_bouton->etat() )  ) ;
        m_bouton->setFondLigneEpaisseur     ( m_btnLgnepaisseurs.get( m_bouton->etat())  );

        CmpTexte::appliquerEtat(  m_bouton->etat() );
    }

    m_curseur->setFondCouleur           ( m_curseurCouleurs.repos  );
    m_curseur->setFondLigneCouleur      ( m_curseurLgnCouleurs.repos );
    m_curseur->setFondLigneEpaisseur    ( m_curseurLgnepaisseurs.repos  );


}

/////////////////////////////////////////////////
void DnZoneTexte::actualiser ()
{
    Gadget::actualiser();

    if ( m_ecritureActive )
    {
        if ( m_clignotteChrono.getElapsedTime().asSeconds() > .5 ){
            m_clignotteChrono.restart();
            m_clignotte = ! m_clignotte;
        }
        //            m_curseur->setVisible ( m_clignotte );

        Interface::necessiteActualisation();
        m_curseur->setVisible ( m_clignotte );
        demanderActuaContenu();
    }
    //else m_curseur->setVisible ( false );
}

/////////////////////////////////////////////////
void DnZoneTexte::traiterEvenements(const sf::Event& evenement ){

    // gestion de la touche suppr
    if ( m_ecritureActive &&  evenement.type == sf::Event::KeyPressed ) {

        m_clignotteChrono.restart();
        m_clignotte = true;

        if ( evenement.key.code == sf::Keyboard::Delete ){
            std::string txt = m_label->getTexte() ;
            txt.erase ( m_curseurPos , 1);
            m_label->setTexte( txt  );
            declencher( Evenement::on_valeurChange );
            return;
        } else if ( evenement.key.code == sf::Keyboard::Left ){
            m_curseurPos--;
            demanderActuaGeom();
            return;
        } else if ( evenement.key.code == sf::Keyboard::Right ){
            m_curseurPos++;
            demanderActuaGeom();
            return;
        }



        // la gestion du clipboard  OS:WIN7
        // Copier
        if ( evenement.key.control
            && evenement.key.code == sf::Keyboard::C )
            {
//                logEvt ("CONTROL + C");
                /*
                auto glob = GlobalAlloc(GMEM_FIXED,32);
                memcpy(glob,"it works",9);

                OpenClipboard( NULL );
                EmptyClipboard();
                SetClipboardData(CF_TEXT,glob);
                CloseClipboard();
                */

                return;
            }

        //  Coller
        if ( evenement.key.control
            && evenement.key.code == sf::Keyboard::V )
            {
//                logEvt ("CONTROL + V");

                if (!IsClipboardFormatAvailable(CF_TEXT))
                    return;

                if (!OpenClipboard(NULL))
                    return;


                // Retrieve the Clipboard data (specifying that
                // we want ANSI text (via the CF_TEXT value).
                HANDLE hClipboardData = GetClipboardData(CF_TEXT);

                // Call GlobalLock so that to retrieve a pointer
                // to the data associated with the handle returned
                // from GetClipboardData.
                char * pchData = (char*)GlobalLock(hClipboardData);

                if (pchData != NULL ){
                    std::string str(pchData);

                    std::string  txt = m_label->getTexte(  );

                    txt.insert( m_curseurPos , str  );
                    m_label->setTexte( txt )  ;
                    declencher( Evenement::on_valeurChange );
                    m_curseurPos += str.size();
                    demanderActuaGeom();

                }

                // Unlock the global memory.
                GlobalUnlock(hClipboardData);

                // Finally, when finished I simply close the Clipboard
                // which has the effect of unlocking it so that other
                // applications can examine or modify its contents.
                CloseClipboard();

                return;
            }


    }









    // gestion de la saisie de texte
    if ( m_ecritureActive
        &&  evenement.type == sf::Event::TextEntered
        &&  ! sf::Keyboard::isKeyPressed(sf::Keyboard::RControl )
        &&  ! sf::Keyboard::isKeyPressed(sf::Keyboard::LControl ) ) {


        log ( "evenement.text.unicode" , evenement.text.unicode );

        // le texte avant modif dans le label
        std::string txt = m_label->getTexte() ;

        // touche Retour arriere : RETOUR ARRIERE  //////////////////////////////
        if ( evenement.text.unicode == 8 )  {
            // si le champ est vide on retourne.
            if ( txt.size()==0 ) return;

            // sinon on retire une lettre et on declenche l'action
            txt.erase ( m_curseurPos-1 , 1);
            m_label->setTexte( txt  );
            declencher( Evenement::on_valeurChange );
            m_curseurPos--;
        }

        // touche Entrée : VALIDER  //////////////////////////////
        else if ( evenement.text.unicode == 13 )
            fn_valider ();


        // touche Echappe : ANNULER  //////////////////////////////
        else if ( evenement.text.unicode == 27 )
            fn_annuler();



        // les autres touches  //////////////////////////////
        else {
            if ( m_numerique ){
                if ( evenement.text.unicode >= 46 && evenement.text.unicode <= 57 ){
                    char txtTmp = static_cast<char>( evenement.text.unicode );
                    txt.insert( m_curseurPos , &txtTmp , 1 );
                    m_label->setTexte( txt )  ;
                    m_curseurPos++;
                    declencher( Evenement::on_valeurChange );
                }
            } else  {
                char txtTmp = static_cast<char>( evenement.text.unicode );
                txt.insert( m_curseurPos , &txtTmp , 1 );
                m_label->setTexte( txt )  ;
                declencher( Evenement::on_valeurChange );
                m_curseurPos++;
            }

            // s'il ne reste plus de place pour ecrire on retourne
//            float largeurTexte = m_label->getSFTexte()->findCharacterPos 	(  m_label->getTexte().size() ).x;
//            if ( largeurTexte > m_btn->getSize().x - 1 )
//                m_label->setTexte( txt );


            // on déclenche et on ecrit.
//            declencher( onCha_ChangeValeur );
        }
        demanderActuaGeom();

    }


}




/*

/////////////////////////////////////////////////
void DnZoneTexte::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    //On applique la transformation
    states.transform *= getTransform();

    // On dessine les éléments
    target.draw( *m_bouton, states );
    target.draw( *m_label, states );

    if ( m_ecritureActive && m_clignotte )
        target.draw( *m_curseur, states );

//m_ClignotteChrono.restart();

}
*/

} // fin namespace gui

