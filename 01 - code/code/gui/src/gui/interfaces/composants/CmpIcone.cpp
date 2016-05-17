#include "interfaces/composants/CmpIcone.h"

namespace gui {

CmpIcone::CmpIcone()
: m_icone   ( std::make_shared<AffIcone>())
{

    m_icone->setFondCouleur    ( sf::Color::White ) ;
    m_icone->setFondLigneEpaisseur ( 0 ) ;
}


/////////////////////////////////////////////////
void CmpIcone::initialiserComposants ( Gadget*     base ){
    m_base = base ;
    m_base->ajouterComposant ( m_icone );
};


/////////////////////////////////////////////////
void CmpIcone::setIndex( unsigned int val )    {
    m_icone->setIndex( val );
    m_base->demanderActuaStyle ();
}


/////////////////////////////////////////////////
void CmpIcone::setImage( std::string fichier )  {
    m_icone->setImage (fichier);
    m_base->demanderActuaGeom ();
}


/////////////////////////////////////////////////
void CmpIcone::setImage ( sf::Texture* texture )  {


//    printf ("SET IMAGE ICI\n");
    m_icone->setImage( texture );
    m_base->demanderActuaGeom ();
}



}
