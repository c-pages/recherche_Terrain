#ifndef CMPTEXTE_H
#define CMPTEXTE_H

#include <string>
#include <SFML/Graphics.hpp>

#include "Composant.h"
#include "Enums.h"
#include "Valeurs.h"

#include "gadgets/AffLabel.h"

namespace gui {

class CmpTexte : public Composant
{
public:

    CmpTexte();

public:

    virtual void            setTexte    ( std::string val );                                ///< Definir m_texte
    virtual std::string     getTexte    ( ) const;

    virtual void setTexteTaille         ( float val , Etat etat = Etat::tous );             ///< Definir m_texteTaille
    virtual void setTexteTaille         ( Valeurs<float> val );                             ///< Definir m_texteTaille

    virtual void setTexteCouleur        ( sf::Color couleur , Etat etat = Etat::tous);      ///< Definir m_police
    virtual void setTexteCouleur        ( Valeurs<sf::Color> couleur  );                    ///< Definir m_police

    virtual void setTextePolice         ( sf::Font val , Etat etat = Etat::tous);           ///< Definir m_police
    virtual void setTextePolice         ( Valeurs<sf::Font> val  );                         ///< Definir

    virtual void setTexteStyle          ( sf::Text::Style val , Etat etat = Etat::tous);    ///< Definir
    virtual void setTexteStyle          ( Valeurs<sf::Text::Style> val  );                  ///< Definir

    virtual void appliquerEtat( Etat etat );

protected :

    /////////////////////////////////////////////////
    virtual void initialiserComposants ( Gadget*     base );


/////////////////////////////////////////////////
// les membres
/////////////////////////////////////////////////
protected:

    std::shared_ptr<AffLabel>       m_label;

    std::string                     m_texte;

    // les proprietés graphiques
    Valeurs<sf::Color>              m_textCouleur;
    Valeurs<sf::Text::Style>        m_textStyle;
    Valeurs<float>                  m_textTaille;
    Valeurs<sf::Font>               m_textPolice;

};

};

#endif // CMPTEXTE_H
