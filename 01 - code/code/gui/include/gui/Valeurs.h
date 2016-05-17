#ifndef VALEURS_H
#define VALEURS_H

#include "Enums.h"

namespace gui{


/////////////////////////////////////////////////
/// \brief Valeurs porte les valeurs pour une proprieté du style correspondants aux états possible du gadgets.
///
/////////////////////////////////////////////////
template <typename T>
struct Valeurs {

    /////////////////////////////////////////////////
    /// \brief Constructeur par copie d'ensemble de valeurs
    ///
    /// \param autre l'autre ensemble de valeurs a copier
    /// \return
    ///
    /////////////////////////////////////////////////
    Valeurs & operator= (const Valeurs & autre)
    {
        // copie des valeurs
        desactive = autre.get(Etat::desactive);
        repos = autre.get(Etat::repos);
        survol = autre.get(Etat::survol);
        press = autre.get(Etat::press);

        return *this;
    };

    /////////////////////////////////////////////////
    /// \brief Constructeur par copie d'une valeur unique
    ///
    /// \param valeur l'autre ensemble de valeurs a copier
    /// \return
    ///
    /////////////////////////////////////////////////
    Valeurs & operator= ( T  valeur )
    {
        // copie des valeurs
        desactive = valeur;
        repos = valeur;
        survol = valeur;
        press = valeur;

        return *this;
    };

    /////////////////////////////////////////////////
    void set ( Valeurs val , Etat etat = Etat::tous )    {
        if ( etat == Etat::tous)
        {
            desactive = val.get(Etat::desactive);
            repos = val.get(Etat::repos);
            survol = val.get(Etat::survol);
            press = val.get(Etat::press);
        }
        else switch ( etat ){
            case Etat::repos :
                repos = val.get(Etat::repos); break;
            case Etat::survol :
                survol = val.get(Etat::survol); break;
            case Etat::press :
                press = val.get(Etat::press); break;
            case Etat::desactive :
                desactive = val.get(Etat::desactive); break;
            default : break;
        }
    };

    /////////////////////////////////////////////////
    void set ( T val , Etat etat = Etat::tous )    {
        if ( etat == Etat::tous)
            repos = survol = press = desactive = val;
        else switch ( etat ){
            case Etat::repos :
                repos = val; break;
            case Etat::survol :
                survol = val; break;
            case Etat::press :
                press = val; break;
            case Etat::desactive :
                desactive = val; break;
            default : break;
        }
    };
    /////////////////////////////////////////////////
    T get ( Etat etat ) const {
         switch ( etat ){
            case Etat::repos :
                return repos; break;
            case Etat::survol :
                return survol; break;
            case Etat::press :
                return press; break;
            case Etat::desactive :
                return desactive; break;
            case Etat::tous :
                return repos; break;
            default : break;

        }
    };
    /////////////////////////////////////////////////
    T repos;
    T survol;
    T press;
    T desactive;

}; // fin Valeurs

}; // fin namespace


#endif // VALEURS_H
