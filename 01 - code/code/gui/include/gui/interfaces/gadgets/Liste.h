#ifndef LISTE__H
#define LISTE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "interfaces/ActionEvenement.h"
#include "Valeurs.h"
#include <vector>



namespace gui {



template <typename T>
class Liste : public ActionEvenement {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:


//    Liste<T>();

    ///< Ajouter un élement dans la liste
    virtual void ajouterElement ( T nouvelElement ){ m_elements.push_back( nouvelElement ); };

    ///< retirer l'élement à la position id de la liste
    virtual void retirerElement ( int id ) { if ( id>=0 || id<m_elements.size() ) m_elements.erase( m_elements.begin() + id ); };

    ///< Accesseur à l'élément de m_elements désigné par un id.
    T getElement ( int id ) const { if ( id>=0 || id<m_elements.size() )  return m_elements.at( id ); else return 0; };

    ///< Accesseur à l'élément de m_elements désigné par un id.
    std::vector<T> getElements ( ) const { return m_elements; };

    ///< Definir m_selection
    void setSelection( int val ){ if ( val < m_elements.size()) m_selection = val; actualiser(); declencher( Evenement::on_valeurChange ); };

    ///< Acceder à m_selection
    int getSelection () const { return m_selection; };



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:
    std::vector<T>  m_elements;     ///<
    int             m_selection;    ///< Renvois -1 si aucune selection. #G#S

    // les proprietés graphiques
    sf::Color                   m_fndCouleur;
    sf::Color                   m_fndLignesCouleur;
    float                       m_fndLignesEpaisseur;

    Valeurs<sf::Color>          m_btnCouleurs;
    Valeurs<sf::Color>          m_btnLignesCouleurs;
    Valeurs<float>              m_btnLignesEpaisseurs;

    Valeurs<sf::Color>          m_textCouleur;
    Valeurs<sf::Text::Style>    m_textStyle;
    Valeurs<float>              m_textTaille;
    Valeurs<sf::Font>           m_textPolice;
}; // fin class Liste

} // fin namespace gui

#endif
