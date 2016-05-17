#include "gadgets/outils/AffCurseurSouris.h"
#include "gui.h"




namespace gui {


/////////////////////////////////////////////////
AffCurseurSouris::AffCurseurSouris( Interface *     interfacePArent )
: m_interface ( interfacePArent )
{
    m_nom = "CurseurSouris";
    setVisible ( false);

}


/////////////////////////////////////////////////
void AffCurseurSouris::traiterEvenements( sf::Event evenement )
{
    setPosAbs( {getPosSouris().x , getPosSouris().y} );
}



/////////////////////////////////////////////////
void AffCurseurSouris::setCurseur ( Curseurs    curseur   )
{

    setPosAbs( {getPosSouris().x , getPosSouris().y} );

    switch ( curseur ){
        case Curseurs::Defaut:
            setVisible(  false );
            m_interface->getFenetre()->setMouseCursorVisible( true );
            break;
        case Curseurs::Redim_vertical:
            setVisible(  true );
            m_interface->getFenetre()->setMouseCursorVisible( false );
            setImage ( &Interface::ms_curseurs.get( "Redimensionnement" ));
            setIndex( 2 );
            m_rectangle.setPosition(-15,-15);
            break;
        case Curseurs::Redim_horizontal:
            setVisible(  true );
            m_interface->getFenetre()->setMouseCursorVisible( false );
            setImage ( &Interface::ms_curseurs.get( "Redimensionnement" ));
            setIndex( 1 );
            m_rectangle.setPosition(-15,-15);
            break;
        case Curseurs::Redim_diag1:
            setVisible(  true );
            m_interface->getFenetre()->setMouseCursorVisible( false );
            setImage ( &Interface::ms_curseurs.get( "Redimensionnement" ));
            setIndex( 3 );
            m_rectangle.setPosition(-15,-15);
            break;
        case Curseurs::Redim_diag2:
            setVisible(  true );
            m_interface->getFenetre()->setMouseCursorVisible( false );
            setImage ( &Interface::ms_curseurs.get( "Redimensionnement" ));
            setIndex( 4 );
            m_rectangle.setPosition(-15,-15);
            break;
    }

}


}; // fin namespace gui
