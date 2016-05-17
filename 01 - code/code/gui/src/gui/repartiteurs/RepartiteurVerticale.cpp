/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <repartiteurs/RepartiteurVerticale.h>



namespace gui {

/////////////////////////////////////////////////
RepartiteurVerticale::RepartiteurVerticale ( Gadget* racine )
: Repartiteur   ( racine )
{

}


/////////////////////////////////////////////////
void RepartiteurVerticale::repartir (std::vector<std::shared_ptr<Gadget>> groupe)
{
//    std::cout << "repartir verticalement\n";
    sf::Vector2i pos = {0,0};
    /*switch ( m_cote ) {
        case Cote::Droite:
            pos = { m_largeurBtnTaille  ,  m_marge.y };
            break;
        case Cote::Gauche:
            pos = { m_marge.x ,  m_marge.y };
            break;
    }*/
    for ( auto enfant : m_racine->getEnfants() )
    {
//        if ( enfant->getPosition ().x !=  pos.x && enfant->getPosition().y !=  pos.y )
        enfant->setPosition( pos.x , pos.y );
        if ( enfant->getTaille().x != m_racine->getTailleContenant().x  )
            enfant->setTailleX( m_racine->getTailleContenant().x  );
        pos.y += enfant->getTaille().y;
    }
}


} // fin namespace gui

