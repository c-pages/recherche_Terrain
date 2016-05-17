#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H


/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

namespace app
{

/////////////////////////////////////////////////
/// \brief Manager de ressource (polices, images).
///
/// Classe template des polices, images
///
/////////////////////////////////////////////////
template<typename RESOURCE,typename IDENTIFIANT = int>
class ResourceMgr
{
    public:
        /////////////////////////////////////////////////
        /// \brief constructeur par copie
        ///
        ///  "= delete" c'est une mani�re de dire non copyable si j'ai bien compris, cf le bouquin SFML ...
        ///
        /////////////////////////////////////////////////
        ResourceMgr             ( const ResourceMgr& ) = delete;

        /////////////////////////////////////////////////
        /// \brief Constructeur
        ///
        ///  "= default" cf le bouquin SFML ...
        ///
        /////////////////////////////////////////////////
        ResourceMgr             ( ) = default;

        /////////////////////////////////////////////////
        /// \brief Surcharge de =
        ///
        ///  "= delete" cf le bouquin SFML, mais je crois que c'est pour dire ope= c'est copy...bref pas super claire encore
        ///
        /////////////////////////////////////////////////
        ResourceMgr& operator=  ( const ResourceMgr& ) = delete;

        /////////////////////////////////////////////////
        /// \brief Charger une image ou une police depuis un fichier et l'associe � un identifiant.
        ///
        /// \param id l'identenfiant
        /// \param args le fichier
        ///
        /////////////////////////////////////////////////
        template<typename ... Args>
        void        load(const IDENTIFIANT& id,Args&& ... args);

        /////////////////////////////////////////////////
        /// \brief demande une image ou une police � partir de son identifiant.
        ///
        /// \param id l'identenfiant
        /// \return la ressource demand�.
        ///
        /////////////////////////////////////////////////
        RESOURCE&   get(const IDENTIFIANT& id)const;

    private:

        std::unordered_map<IDENTIFIANT,std::unique_ptr<RESOURCE>>       mPlan;  ///< les resources enregistr�s avec leur identifiant.
};


/////////////////////////////////////////////////
/// \brief Manager de ressource (music).
///
/// Classe template des musiques
///
/////////////////////////////////////////////////
template<typename IDENTIFIANT>
class ResourceMgr<sf::Music,IDENTIFIANT>
{
    public:
        /////////////////////////////////////////////////
        /// \brief constructeur
        ///
        ///  "= delete" c'est une mani�re de dire non copyable si j'ai bien compris, cf le bouquin SFML ...
        ///
        /////////////////////////////////////////////////
        ResourceMgr(const ResourceMgr&) = delete;

        /////////////////////////////////////////////////
        /// \brief Constructeur
        ///
        ///  "= default" cf le bouquin SFML ...
        ///
        /////////////////////////////////////////////////
        ResourceMgr() = default;

        /////////////////////////////////////////////////
        /// \brief Surcharge de =
        ///
        ///  "= delete" cf le bouquin SFML, mais je crois que c'est pour dire ope= c'est copy...bref pas super claire encore
        ///
        /////////////////////////////////////////////////
        ResourceMgr& operator=(const ResourceMgr&) = delete;

        /////////////////////////////////////////////////
        /// \brief Charger une musique depuis un fichier et l'associe � un identifiant.
        ///
        /// \param id l'identifiant
        /// \param args le fichier
        ///
        /////////////////////////////////////////////////
        template<typename ... Args>
        void load(const IDENTIFIANT& id,Args&& ... args);

        /////////////////////////////////////////////////
        /// \brief demande une musique � partir de son identifiant.
        ///
        /// \param id l'identifiant
        /// \return la musique demand�.
        ///
        /////////////////////////////////////////////////
        sf::Music& get(const IDENTIFIANT& id)const;
    private:
        std::unordered_map<IDENTIFIANT,std::unique_ptr<sf::Music>> mPlan; ///< les resources enregistr�s avec leur identifiant.
};


}; // fin app

#include <ResourceMgr.inl>



#endif // RESOURCEMGR_H

////////////////////////////////////////////////////////////
/// \class app::ResourceMgr
/// \ingroup application
///
/// G�re les ressource fa�on RAII
///
/// \see app::Ecran, app::Gestion_ecrans
///
////////////////////////////////////////////////////////////
