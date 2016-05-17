

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "ResourceMgr.h"
namespace app
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
void ResourceMgr<sf::Music,IDENTIFIANT>::load(const IDENTIFIANT& id,Args&& ... args)
{
    std::unique_ptr<sf::Music> ptr(new sf::Music);
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
sf::Music& ResourceMgr<sf::Music,IDENTIFIANT>::get(const IDENTIFIANT& id) const
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
void ResourceMgr<RESOURCE,IDENTIFIANT>::load(const IDENTIFIANT& id , Args&& ... args)
{
    std::unique_ptr<RESOURCE> ptr(new RESOURCE);
    if(not ptr->loadFromFile(std::forward<Args>(args)...))
        throw std::runtime_error("Impossible de charger le fichier");
    mPlan.emplace(id,std::move(ptr));
}



template<typename RESOURCE,typename IDENTIFIANT>
RESOURCE& ResourceMgr<RESOURCE,IDENTIFIANT>::get(const IDENTIFIANT& id)const
{
    return *mPlan.at(id);
}

} // fin app
