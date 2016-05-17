/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "gadgets/outils/CntSimple.h"
#include "Enums.h"



namespace gui {

/////////////////////////////////////////////////
CntSimple::CntSimple ()
: Contenant ()
{
    m_taille = { 400 , 200 };
    actualiser ();
}
//
///////////////////////////////////////////////////
//void CntSimple::actualiserGeometrie (){
//
//
//
//}
//
///////////////////////////////////////////////////
//void CntSimple::actualiserStyle (){
//
//    m_fond->setFillColor (    m_fndCouleur ) ;
//    m_fond->setOutlineColor (    m_fndLgnCouleur  ) ;
//    m_fond->setOutlineThickness ( m_fndLgnepaisseur  );
//
//    actualiserContenu();
//    actualiserBounds ();
//
//    if ( m_parent != nullptr ) m_parent->actualiserContenu();
//}

///////////////////////////////////////////////////
//void CntSimple::actualiser ()
//{
//
//    m_fond->setTaille(m_taille);
//    m_contenant->setSize({ m_taille.x , m_taille.y });
//
////    m_fond->setStyle ( m_skin->getStyle ( Styles::fond ) );
//
//    actualiserContenu();
//
//    actualiserBounds ();
//
//    if ( m_parent != nullptr ) m_parent->actualiserContenu();
//}


/////////////////////////////////////////////////
void CntSimple::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

    if ( estVisible() ) {

        //On applique la transformation
        states.transform *= getTransform();

//        target.draw( *m_fond , states );
        target.draw( *m_affContenant , states );

    }

}


} // fin namespace gui

