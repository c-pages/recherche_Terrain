#ifndef RESOURCESMGR_H
#define RESOURCESMGR_H


/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <unordered_map>
#include <memory>
#include <Patch.h>

#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <string>
#include <sstream>

namespace gui
{

/////////////////////////////////////////////////
/// \brief Manager de ressource (polices, images).
///
/// Classe template des polices, images
///
/////////////////////////////////////////////////
template<typename RESOURCE,typename IDENTIFIANT = std::string>
class ResourcesMgr
{
    public:
        /////////////////////////////////////////////////
        /// \brief constructeur par copie
        ///
        ///  "= delete" c'est une manière de dire non copyable si j'ai bien compris, cf le bouquin SFML ...
        ///
        /////////////////////////////////////////////////
        ResourcesMgr             ( const ResourcesMgr& ) = delete;

        /////////////////////////////////////////////////
        /// \brief Constructeur
        ///
        ///  "= default" cf le bouquin SFML ...
        ///
        /////////////////////////////////////////////////
        ResourcesMgr             ( ) = default;

        /////////////////////////////////////////////////
        /// \brief Surcharge de =
        ///
        ///  "= delete" cf le bouquin SFML, mais je crois que c'est pour dire ope= c'est copy...bref pas super claire encore
        ///
        /////////////////////////////////////////////////
        ResourcesMgr& operator=  ( const ResourcesMgr& ) = delete;

        /////////////////////////////////////////////////
        /// \brief Charger une image ou une police depuis un fichier et l'associe à un identifiant.
        ///
        /// \param id l'identenfiant
        /// \param args le fichier
        ///
        /////////////////////////////////////////////////
        template<typename ... Args>
        void        load(const IDENTIFIANT& id,Args&& ... args);

        /////////////////////////////////////////////////
        /// \brief demande une image ou une police à partir de son identifiant.
        ///
        /// \param id l'identenfiant
        /// \return la ressource demandé.
        ///
        /////////////////////////////////////////////////
        RESOURCE&   get(const IDENTIFIANT& id)const;

        bool existe (const IDENTIFIANT& id)const;


        std::string nomDefautSuivant();

    private:

        std::unordered_map<IDENTIFIANT,std::unique_ptr<RESOURCE>>       mPlan;  ///< les resources enregistrés avec leur identifiant.
};


/////////////////////////////////////////////////
/// \brief Manager de ressource (music).
///
/// Classe template des musiques
///
/////////////////////////////////////////////////
template<typename IDENTIFIANT>
class ResourcesMgr<sf::Music,IDENTIFIANT>
{
    public:
        /////////////////////////////////////////////////
        /// \brief constructeur
        ///
        ///  "= delete" c'est une manière de dire non copyable si j'ai bien compris, cf le bouquin SFML ...
        ///
        /////////////////////////////////////////////////
        ResourcesMgr(const ResourcesMgr&) = delete;

        /////////////////////////////////////////////////
        /// \brief Constructeur
        ///
        ///  "= default" cf le bouquin SFML ...
        ///
        /////////////////////////////////////////////////
        ResourcesMgr() = default;

        /////////////////////////////////////////////////
        /// \brief Surcharge de =
        ///
        ///  "= delete" cf le bouquin SFML, mais je crois que c'est pour dire ope= c'est copy...bref pas super claire encore
        ///
        /////////////////////////////////////////////////
        ResourcesMgr& operator=(const ResourcesMgr&) = delete;

        /////////////////////////////////////////////////
        /// \brief Charger une musique depuis un fichier et l'associe à un identifiant.
        ///
        /// \param id l'identifiant
        /// \param args le fichier
        ///
        /////////////////////////////////////////////////
        template<typename ... Args>
        void load(const IDENTIFIANT& id,Args&& ... args);

        std::string nomDefautSuivant()
        {
            std::string nomImageDefaut = "ImageDefaut";
            bool test = false;
            int ind = 1;
            while ( !test )
            {
                if ( get (  nomImageDefaut + patch::to_string(ind ) ) == mPlan.end() )
                    return (  nomImageDefaut + patch::to_string(ind ) );
                ind++;
            }
        };


        /////////////////////////////////////////////////
        /// \brief demande une musique à partir de son identifiant.
        ///
        /// \param id l'identifiant
        /// \return la musique demandé.
        ///
        /////////////////////////////////////////////////
        sf::Music& get(const IDENTIFIANT& id)const;
    private:
        std::unordered_map<IDENTIFIANT,std::unique_ptr<sf::Music>> mPlan; ///< les resources enregistrés avec leur identifiant.
};


}; // fin gui

#include <ResourcesMgr.inl>



#endif // RESOURCEMGR_H

////////////////////////////////////////////////////////////
/// \class app::ResourcesMgr
/// \ingroup application
///
/// Gère les ressource façon RAII
///
/// \see app::Ecran, app::Gestion_ecrans
///
////////////////////////////////////////////////////////////
