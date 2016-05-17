

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "ResourcesMgr.h"
namespace gui
{
/////////////////////////////////////////////////
// les templates pour la gestion des ressources musicales
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/// \brief Manager de ressource.
///
/// Classe template des musiques
///
/////////////////////////////////////////////////
template<typename IDENTIFIANT>
template<typename ... Args>
void ResourcesMgr<sf::Music,IDENTIFIANT>::load(const IDENTIFIANT& id,Args&& ... args)
{
//    std::shared_ptr<sf::Music> ptr = std::make_shared<sf::Music>();
    std::unique_ptr<sf::Music> ptr ( new sf::Music );
    if(not ptr->openFromFile(std::forward<Args>(args)...))
        throw std::runtime_error("Impossible de charger le fichier");
    mPlan.emplace(id,std::move(ptr));
};

/////////////////////////////////////////////////
/// \brief Manager de ressource.
///
/// Class template des musiques
///
/////////////////////////////////////////////////
template<typename IDENTIFIANT>
sf::Music& ResourcesMgr<sf::Music,IDENTIFIANT>::get(const IDENTIFIANT& id) const
{
    return *mPlan.at(id);
}




/////////////////////////////////////////////////
// les templates pour la gestion des ressources types images/polices
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/// \brief Manager de ressource.
///
/// Class template des polices, images
///
/////////////////////////////////////////////////
template<typename RESOURCE,typename IDENTIFIANT>
template<typename ... Args>
void ResourcesMgr<RESOURCE,IDENTIFIANT>::load(const IDENTIFIANT& id , Args&& ... args)
{

    std::unique_ptr<RESOURCE> ptr ( new RESOURCE );
    if(not ptr->loadFromFile(std::forward<Args>(args)...))
        throw std::runtime_error("Impossible de charger le fichier");
    mPlan.emplace(id,std::move(ptr));

}



template<typename RESOURCE,typename IDENTIFIANT>
RESOURCE& ResourcesMgr<RESOURCE,IDENTIFIANT>::get(const IDENTIFIANT& id)const
{

//    std::cout << "ResourcesMgr : get " << id << " : " << mPlan.size() <<"\n";
    return *mPlan.at(id);
}


template<typename RESOURCE,typename IDENTIFIANT>
bool ResourcesMgr<RESOURCE,IDENTIFIANT>::existe(const IDENTIFIANT& id)const
{
    if ( mPlan.find (id) == mPlan.end())
         return false;
    else return true;
}

template<typename RESOURCE,typename IDENTIFIANT>
std::string ResourcesMgr<RESOURCE,IDENTIFIANT>::nomDefautSuivant()
{
    std::string nomImageDefaut = "ImageDefaut_";
    bool test = false;
    int ind = 1;
    while ( !test )
    {
        if ( ! existe ( nomImageDefaut + patch::to_string( ind ) ) )
            return (  nomImageDefaut + patch::to_string(ind ) );
        ind++;
    }
};



} // fin app










