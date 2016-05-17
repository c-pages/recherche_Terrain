/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gui.h"
#include "interfaces/gadgets/Support.h"



namespace gui {

/////////////////////////////////////////////////
Support::Support ()
: m_interface   ( nullptr )
, m_fond        ( std::make_shared<AffRectangle>() )
//, m_panneaux    ( std::make_shared<CntSimple>() )
{
    ajouterComposant ( m_fond );
//    ajouterComposant ( m_panneaux );

    m_taille = { 800 , 280 };

    m_fndCouleur        = sf::Color( 60, 60, 60 );
    m_fndCouleurSurvol  = sf::Color( 80, 80, 80 );
    m_fndLgnCouleur     = sf::Color( 90,90,90 );
    m_fndLgnEpaisseur   = 1 ;

//    ajouterComposant ( m_panneau );
}

/////////////////////////////////////////////////
void Support::setInterface ( Interface *     interfacePArent )    {
    m_interface = interfacePArent;
    actualiser();
};


/////////////////////////////////////////////////
void Support::actualiserGeometrie ()
{

//        std::cout << " BAH IL PASS PAR ICI ON DIRAIT BIEN\n";
    if (m_interface != nullptr)
    {
        auto tailleFenetre = m_interface->getFenetre()->getSize();
        m_taille = {tailleFenetre.x , m_taille.y };
    }
    m_fond->setTaille ( m_taille );
//    m_panneaux->setTaille ( { m_taille.x - 2*m_marge.x , m_taille.y - 2*m_marge.y });

}




/////////////////////////////////////////////////
void Support::actualiserStyle ()
{
    if ( estAbsorbable() )
        m_fond->setFondCouleur ( m_fndCouleurSurvol );
    else
        m_fond->setFondCouleur ( m_fndCouleur );

    m_fond->setFondLigneCouleur ( m_fndLgnCouleur );
    m_fond->setFondLigneEpaisseur (m_fndLgnEpaisseur);
}


/*
/////////////////////////////////////////////////
void Support::ajouter (std::shared_ptr<Gadget> enfant)
{
    m_panneaux->ajouter ( enfant );
}*/


} // fin namespace gui

