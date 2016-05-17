#ifndef AFFLABEL__H
#define AFFLABEL__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////

#include "interfaces/gadgets/Affiche.h"


#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>



namespace gui {



/////////////////////////////////////////////////
/// \brief Classe concrète d'affichage d'un simple texte.
///
/////////////////////////////////////////////////
class AffLabel : public gui::Affiche {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:

    virtual sf::Vector2i  getTaille() const;


    ///< Acceder au text SFML
    sf::Text     getSFTexte () const { return m_texteSFML; };



    ///< Definir m_texte
    virtual void setTexte( std::string val );

    ///< Acceder à m_texte
    std::string getTexte () const { return m_texteSFML.getString( ); };

    ///< Definir m_texteTaille
    void setTexteTaille( float val );

    ///< Definir m_police
    void setTexteCouleur( sf::Color couleur );

    ///< Definir m_police
    void setTextePolice( sf::Font val );

    ///< Definir m_police
    void setTexteStyle( sf::Text::Style val );

    ///< Acceder à m_police
    sf::Font getPolice () const { return m_textPolice; };

    ///< Rendre le texet dans une texture pour l'utilisation du shader de mask...
    void rendreTexte ();

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur par défaut.
    ///
    /////////////////////////////////////////////////
    AffLabel ();

    /////////////////////////////////////////////////
    virtual void actualiserGeometrie ();

    /////////////////////////////////////////////////
    virtual void actualiserStyle ();

    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;


/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:

    // les composants de l'interface du gadget
    sf::Text            m_texteSFML;        ///< Le shape SFML qui affiche le texte.

    // les proprietés graphiques
    sf::Color           m_textCouleur;
    sf::Text::Style     m_textStyle;
    float               m_textTaille;
    sf::Font            m_textPolice;



    // proprietes pour rendu texture
    sf::Texture                         m_contenu;          ///< La texture SFML qui affiche le contenu du panneau.
    sf::RenderTexture                   m_renderTexture;
    std::shared_ptr<sf::Sprite>         m_affContenant;
    int                                 m_aliasTexture;

}; // fin class AffLabel

} // fin namespace gui

#endif
