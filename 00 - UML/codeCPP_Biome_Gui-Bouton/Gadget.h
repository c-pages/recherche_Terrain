#ifndef GADGET__H
#define GADGET__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>



namespace gui {

class Gadget;
class Gadget;


/////////////////////////////////////////////////
/// \brief Un gadget est la classe abstraite des �l�ments de l'interface.
///
/////////////////////////////////////////////////
class Gadget : public std::enable_shared_from_this, public sf::Transformable, public sf::NonCopyable, public sf::Drawable {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
    ///< Definir m_parent
    void setParent( Gadget* val ){ m_parent = val; };

    ///< Acceder � m_parent
    Gadget* getParent () const { return m_parent; };

    ///< Ajouter un �lement dans m_enfants
    void ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement ){ m_enfants.push_back( nouvelElement ); };

    ///< retirer l'�lement � la position id dans m_enfants
    void retirerEnfant ( int id ) { if ( id>=0 || id<m_enfants.size() ) m_enfants.erase( m_enfants.begin() + id ); };

    ///< Vider m_enfants
    void viderEnfants () { m_enfants.clear(); };

    ///< Accesseur � l'�l�ment de m_enfants d�sign� par un id.
    std::shared_ptr<Gadget> getEnfant ( int id ) const { if ( id>=0 || id<m_enfants.size() )  return m_enfants.at( id ); else return 0; };

    ///< Definir m_size
    void setSize( sf::Vector2i val ){ m_size = val; };

    ///< Acceder � m_size
    sf::Vector2i getSize () const { return m_size; };

    ///< Acceder � m_globalBounds
    sf::IntRect getGlobalBounds () const { return m_globalBounds; };

    ///< Acceder � m_localBounds
    sf::IntRect getLocalBounds () const { return m_localBounds; };

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur.
    ///
    /////////////////////////////////////////////////
    Gadget ();

    /////////////////////////////////////////////////
    /// \brief Cr�er un shared pointeur vers this.
    /// \return Un pointeur vers ce gadget.
    ///
    /////////////////////////////////////////////////
    std::shared_ptr<Gadget> thisPtr ();

    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    /// \return nullptr de base, fonction � surcharger pour �l�ments interactifs.
    ///
    /// \param posSouris		 La position � tester.
    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> testerSurvol (sf::Vector2i posSouris) const;

    /////////////////////////////////////////////////
    /// \brief Traitement des �venements clavier ou souris.
    ///
    /// \param evenement		 L'�venemnt � tratier.
    /////////////////////////////////////////////////
    virtual void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualiser les �l�ments de l'interface.
    ///
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine tout les �l�ments de l'interface.
    ///
    /// \param target		 
    /// \param states		 
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    Gadget* m_parent;    ///< Le gadget parent.    
    std::vector<std::shared_ptr<Gadget>> m_enfants;    ///< les liste des gadgets enfants.     
    sf::Vector2i m_size;    ///< La taille du gadget.    
    sf::IntRect m_globalBounds;    ///< Les limites globales du gadget (par rapport � la fen�tre principale).    
    sf::IntRect m_localBounds;    ///< Les limites locales du gadget (par rapport � son parent).    

}; // fin class Gadget

} // fin namespace gui

#endif
