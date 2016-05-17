#ifndef GEOMETRIE__H
#define GEOMETRIE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Filiation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enums.h"



namespace gui {

/////////////////////////////////////////////////
/// \brief Concerne la partie geometrique des gadgets, comme la taille, contient, position absolue...
///
/////////////////////////////////////////////////
class Geometrie : public sf::Transformable, public gui::Filiation {


/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////
public:

/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    ///< Definir m_taille
    virtual void setTaille( float x, float y );
    virtual void setTaille( sf::Vector2i val );
    virtual void setTailleX( float val );
    virtual void setTailleY( float val );

    virtual void demanderActualisation(){};

    ///< Acceder à m_taille
    virtual sf::Vector2i getTaille () const { return m_taille;  };

    ///< Acceder à m_localBounds
    sf::FloatRect getLocalBounds () const { return m_localBounds; };

    ///< Acceder à m_globalBounds
    sf::FloatRect getGlobalBounds () const { return m_globalBounds; };

    ///< Definir m_opacite
    void setOpacite( double val ){ m_opacite = val; actualiserStyle();  };

    ///< Acceder à m_taille
    double getOpacite () const { return m_opacite; };

    ///< reDefinir setPosition
    virtual     void setPosition( float x , float y );

    ///< reDefinir setPosition
    virtual     void setPosition( sf::Vector2f pos );


    /////////////////////////////////////////////////
    void setPosAbs (sf::Vector2f posAbsDest );


    /////////////////////////////////////////////////
    /// \brief Calculer la position absolue du gadget.
    ///
    /////////////////////////////////////////////////
    sf::Vector2f getPosAbs () const;

    /////////////////////////////////////////////////
    /// \brief S'aligner sur un autre gadget.
    ///
    /// \param cible		    gadget cible sur lequel s'aligner.
    /// \param alignementThis   L'endroit du gadget à aligner sur la cible.
    /// \param alignementCible	L'endroit de la cible sur lequel aligner le gadget.
    /////////////////////////////////////////////////
    void alignerSur ( std::shared_ptr<Gadget> cible, Alignement alignementThis = Alignement::Centre , Alignement alignementCible = Alignement::Centre );

    /////////////////////////////////////////////////
    /// \brief Actualiser .
    ///
    /////////////////////////////////////////////////
    virtual void actualiser (){std::cout << "ACTUALISER GEOMETRIE_H\n";};

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie (){};

    /////////////////////////////////////////////////
    virtual void actualiserStyle (){};

    /////////////////////////////////////////////////
    /// \brief Actualiser les membres bounds local et global.
    ///
    /////////////////////////////////////////////////
    virtual void actualiserBounds ();

/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:
//    sf::Vector2i    m_position;           ///< la taille permet d'organiser la disposition des éléments graphiques du gadget.
    sf::Vector2i    m_taille;           ///< la taille permet d'organiser la disposition des éléments graphiques du gadget.
    sf::FloatRect   m_localBounds;      ///< la rectangle englobant du gadget en coordonnés locales.
    sf::FloatRect   m_globalBounds;     ///< la rectangle englobant du gadget en coordonnés globales.
    double          m_opacite = 1;      ///< L'opacité du gadget ( entre 0 et 1 )


}; // fin class Geometrie

} // fin namespace gui

#endif
