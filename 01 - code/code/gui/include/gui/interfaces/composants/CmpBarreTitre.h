#ifndef CMPBARRETITRE_H
#define CMPBARRETITRE_H

#include <string>
#include <SFML/Graphics.hpp>

#include "Composant.h"
#include "Enums.h"
#include "Valeurs.h"

#include "gadgets/AffLabel.h"
#include "gadgets/BtnIcone.h"

namespace gui {

class CmpBarreTitre : public Composant
{
public:

    CmpBarreTitre();

public:

    virtual void            setTitre    ( std::string val );                                ///< Definir m_texte
    virtual std::string     getTitre    ( ) const;

    virtual void setTitreTxtTaille      ( float val );             ///< Definir m_texteTaille
    virtual void setTitreTxtCouleur     ( sf::Color couleur );     ///< Definir m_police
    virtual void setTitreTxtPolice      ( sf::Font val);           ///< Definir m_police//
    virtual void setTitreTxtStyle       ( sf::Text::Style val );   ///< Definir
    virtual void setTitreIcone          ( std::string fichier );
    virtual void setTitreIcone          ( sf::Texture* texture );


protected :

    /////////////////////////////////////////////////
    virtual void initialiserComposants ( Gadget*     base );

    void actualiserGeometrie ();
    void actualiserStyle ();

/////////////////////////////////////////////////
// les membres
/////////////////////////////////////////////////
protected:

    // valeurs par defaut
    sf::Vector2i        m_titreTaille;
    sf::Vector2i        m_titreMarge;
    sf::Vector2i        m_taillebouton;


    // les composants de l'interface du gadget
    std::shared_ptr<AffRectangle>   m_titreFond;
    std::shared_ptr<AffLabel>       m_titreLabel;
    std::shared_ptr<AffIcone>       m_titreIcone;
    std::shared_ptr<BtnIcone>       m_btnFermer;
    std::shared_ptr<BtnIcone>       m_btnReduire;

    // les proprietés graphiques
    sf::Color               m_titreFondCouleur;
    sf::Color               m_titreFondLgnCouleur;
    float                   m_titreFondLgnepaisseur;

    sf::Color               m_titreTextCouleur;
    sf::Text::Style         m_titreTextStyle;
    float                   m_titreTextTaille;
    sf::Font                m_titreTextPolice;

    Valeurs<sf::Color>               m_titreBtnCouleur;
    Valeurs<sf::Color>               m_titreBtnLgnCouleur;
    Valeurs<float>                   m_titreBtnLgnepaisseur;
};

};

#endif // CMPBARRETITRE_H
