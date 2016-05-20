#ifndef STYLE__H
#define STYLE__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <SFML/Graphics.hpp>



namespace gui {



/////////////////////////////////////////////////
/// \brief Regroupe les couleurs, polices et style de texte de l'interface.
///
/////////////////////////////////////////////////
class Style {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    ///< Definir m_fondCouleur_1
    void setFondCouleur_1( sf::Color val ){ m_fondCouleur_1 = val; };

    ///< Acceder à m_fondCouleur_1
    sf::Color getFondCouleur_1 () const { return m_fondCouleur_1; };

    ///< Definir m_fondCouleur_2
    void setFondCouleur_2( sf::Color val ){ m_fondCouleur_2 = val; };

    ///< Acceder à m_fondCouleur_2
    sf::Color getFondCouleur_2 () const { return m_fondCouleur_2; };

    ///< Definir m_fondCouleur_3
    void setFondCouleur_3( sf::Color val ){ m_fondCouleur_3 = val; };

    ///< Acceder à m_fondCouleur_3
    sf::Color getFondCouleur_3 () const { return m_fondCouleur_3; };

    ///< Definir m_ligneCouleur
    void setLigneCouleur( sf::Color val ){ m_ligneCouleur = val; };

    ///< Acceder à m_ligneCouleur
    sf::Color getLigneCouleur () const { return m_ligneCouleur; };

    ///< Definir m_boutonCouleur_repos
    void setBoutonCouleur_repos( sf::Color val ){ m_boutonCouleur_repos = val; };

    ///< Acceder à m_boutonCouleur_repos
    sf::Color getBoutonCouleur_repos () const { return m_boutonCouleur_repos; };

    ///< Definir m_boutonCouleur_survol
    void setBoutonCouleur_survol( sf::Color val ){ m_boutonCouleur_survol = val; };

    ///< Acceder à m_boutonCouleur_survol
    sf::Color getBoutonCouleur_survol () const { return m_boutonCouleur_survol; };

    ///< Definir m_boutonCouleur_press
    void setBoutonCouleur_press( sf::Color val ){ m_boutonCouleur_press = val; };

    ///< Acceder à m_boutonCouleur_press
    sf::Color getBoutonCouleur_press () const { return m_boutonCouleur_press; };

    ///< Definir m_texteCouleur_1
    void setTexteCouleur_1( sf::Color val ){ m_texteCouleur_1 = val; };

    ///< Acceder à m_texteCouleur_1
    sf::Color getTexteCouleur_1 () const { return m_texteCouleur_1; };

    ///< Definir m_texteCouleur_2
    void setTexteCouleur_2( sf::Color val ){ m_texteCouleur_2 = val; };

    ///< Acceder à m_texteCouleur_2
    sf::Color getTexteCouleur_2 () const { return m_texteCouleur_2; };

    ///< Definir m_texteCouleur_3
    void setTexteCouleur_3( sf::Color val ){ m_texteCouleur_3 = val; };

    ///< Acceder à m_texteCouleur_3
    sf::Color getTexteCouleur_3 () const { return m_texteCouleur_3; };

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /////////////////////////////////////////////////
    Style ();



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    sf::Color m_fondCouleur_1;    ///< La couleur principale.    
    sf::Color m_fondCouleur_2;    ///< La couleur secondaire.    
    sf::Color m_fondCouleur_3;    ///< La couleur tertiare.    
    sf::Color m_ligneCouleur;    ///< La couleur des lignes du contour.    
    sf::Color m_boutonCouleur_repos;    ///< La couleur des boutons au repos.    
    sf::Color m_boutonCouleur_survol;    ///< La couleur des boutons survolés.    
    sf::Color m_boutonCouleur_press;    ///< La couleur des boutons pressés.    
    sf::Color m_texteCouleur_1;    ///< La couleur des textes principaux.    
    sf::Color m_texteCouleur_2;    ///< La couleur des textes secondaires.    
    sf::Color m_texteCouleur_3;    ///< La couleur des textes tertiaires.    

}; // fin class Style

} // fin namespace gui

#endif
