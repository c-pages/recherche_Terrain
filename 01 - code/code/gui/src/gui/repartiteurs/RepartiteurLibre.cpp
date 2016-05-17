/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <repartiteurs/RepartiteurLibre.h>



namespace gui {

/////////////////////////////////////////////////
RepartiteurLibre::RepartiteurLibre ( Gadget* racine )
: Repartiteur   ( racine )
{

}


/////////////////////////////////////////////////
void RepartiteurLibre::repartir (std::vector<std::shared_ptr<Gadget>> groupe)
{
    // bon bah on fait rien ici puisqu'on est libre ...
//    std::cout << "repartir librement\n";
}


} // fin namespace gui

