#ifndef GADGET__H
#define GADGET__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

#include "gui/Actions.h"

#include <iostream>

namespace gui {





/////////////////////////////////////////////////
/// \brief les 9 endroits d'alignement entre gadgets
/////////////////////////////////////////////////
enum class Alignement {
    Centre,
    Gauche,
    Droite,
    Haut,
    Bas,
    GaucheHaut,
    GaucheBas,
    DroiteHaut,
    DroiteBas
};

/////////////////////////////////////////////////
/// \brief Un gadget est la classe abstraite des éléments de l'interface.
///
/////////////////////////////////////////////////
class Gadget :  public std::enable_shared_from_this<Gadget>,
                public sf::NonCopyable,
                public sf::Transformable,
                public sf::Drawable,
                public Actions
{
/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////

public:
    ///< \brief Les differents états du bouton.
    enum Etat {
        Repos,      ///< Le bouton est au repos.
        Survol,     ///< Le bouton est survolé par la souris.
        Presse,     ///< Le bouton est pressé.
        Fin
    };


/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur.
    ///
    /////////////////////////////////////////////////
    Gadget ();





    /////////////////////////////////////////////////
    /// \brief Teste le survol du gadget par la souris.
    ///
    /// \param posSouris		 La position à tester.
    /// \return nullptr de base, fonction à surcharger pour éléments interactifs.
    /////////////////////////////////////////////////
    virtual Gadget* testerSurvol (sf::Vector2i posSouris) ;

    /////////////////////////////////////////////////
    /// \brief Traitement des évenements clavier ou souris.
    ///
    /// \param evenement		 L'évenemnt à tratier.
    /////////////////////////////////////////////////
    virtual void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualise les parametres du shader clipping.
    ///
    /// \param bounds le rectangle de découpe
    /////////////////////////////////////////////////
    void actualiserClipping ( sf::IntRect bounds );

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments de l'interface.
    ///
    /////////////////////////////////////////////////
    virtual void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine tout les éléments de l'interface.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;






public:
    /// Accesseurs / mutateur    /////////////////////

    /////////////////////////////////////////////////
    /// \brief Definie la visibilité du gadget
    ///
    /// \param visible La nouvelle visibilité
    /////////////////////////////////////////////////
    virtual void setVisible ( bool visible ){ m_visible = visible; };

    /////////////////////////////////////////////////
    /// \brief SAvoir si le gadget est visible
    ///
    /// \return true si visible, false si caché
    /////////////////////////////////////////////////
    bool estVisible () const { return m_visible; };


    /////////////////////////////////////////////////
    /// \brief Definie la taille de la marge
    ///
    /// \param marge La nouvelle marge
    /////////////////////////////////////////////////
    virtual void setMarge ( sf::Vector2f marge ){ m_marge = marge; };

    /////////////////////////////////////////////////
    /// \brief recuperer la taille de la marge
    ///
    /////////////////////////////////////////////////
    sf::Vector2f setMarge (  ){ return m_marge; };


    /////////////////////////////////////////////////
    /// \brief Definie l'état du gadget , surtout pour les éléments interactifs, ici ne fait rien.
    ///
    /// \param etat Le nouvel état
    /////////////////////////////////////////////////
    virtual void setEtat (Etat etat){ };

    /////////////////////////////////////////////////
    /// \brief Definir m_parent.
    ///
    /// \param parent Le nouveau parent
    /////////////////////////////////////////////////
    virtual void setParent( Gadget* parent ){ m_parent = parent; };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_parent.
    ///
    /////////////////////////////////////////////////
    virtual Gadget* getParent () const { return m_parent; };

    /////////////////////////////////////////////////
    /// \brief Ajouter un élement dans m_enfants.
    ///
    /////////////////////////////////////////////////
    virtual void ajouterEnfant ( std::shared_ptr<Gadget> nouvelElement );


    /////////////////////////////////////////////////
    /// \brief Vider m_enfants.
    ///
    /////////////////////////////////////////////////
    virtual void viderEnfants () { m_enfants.clear(); };

    /////////////////////////////////////////////////
    /// \brief Accesseur à l'élément de m_enfants désigné par un id.
    ///
    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> getEnfant ( unsigned int id ) const { if ( id>=0 || id<m_enfants.size() )  return m_enfants.at( id ); else return 0; };

    /////////////////////////////////////////////////
    /// \brief demanderau perent à être au dessus des autres enfants.
    ///
    /////////////////////////////////////////////////
    void demander_etreDevant ();

    /////////////////////////////////////////////////
    /// \brief demande au parent de supprimer le gadget.
    ///
    /// Le parent va l'ajouter dans sa liste des gadgets à supprimer (supprimerEnfant()) et
    /// supprimera effectivement le gadget à la fin du traitement des evenements du Gui (actuaListeSuppression())
    /////////////////////////////////////////////////
    virtual void supprimer () { m_parent->supprimerEnfant ( thisPtr() ); };


//protected:
    /////////////////////////////////////////////////
    /// \brief Créer un shared pointeur vers this.
    /// \return Un pointeur vers ce gadget.
    ///
    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> thisPtr ()  { return shared_from_this(); };

    /////////////////////////////////////////////////
    /// \brief Mettre le gadget au dessus des autres enfants de son parent.
    ///
    /// \param gadget le gadget à mettre devant
    /////////////////////////////////////////////////
    void mettreDevant ( std::shared_ptr<Gadget> gadget );


    /////////////////////////////////////////////////
    /// \brief retirer un enfant du gadget
    /// \param cible le gadget à retirer
    ///
    /////////////////////////////////////////////////
    virtual void supprimerEnfant ( std::shared_ptr<Gadget> cible );

    /////////////////////////////////////////////////
    /// \brief supprimer le gadget.
    ///
    /////////////////////////////////////////////////
    virtual void actuaListeSuppression () ;



//public:

    ////////////////////////////////////////////////////////////
    /// \brief place le gadget à la meme position qu'un autre.
    ///
    /// \param cible
    ////////////////////////////////////////////////////////////
    void setPosition( std::shared_ptr<Gadget> cible );

    ////////////////////////////////////////////////////////////
    /// \brief override (un peu a l'arrache) de la fonction sf::Transformable::setPosition().
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(int x, int y);

    ////////////////////////////////////////////////////////////
    /// \brief override (un peu a l'arrache) de la fonction sf::Transformable::setPosition().
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(float x, float y);

    ////////////////////////////////////////////////////////////
    /// \brief override (un peu a l'arrache) de la fonction sf::Transformable::setPosition().
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(const sf::Vector2f& position);

    ////////////////////////////////////////////////////////////
    /// \brief override (un peu a l'arrache) de la fonction sf::Transformable::setPosition().
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(const sf::Vector2i& position);

    /////////////////////////////////////////////////
    /// \brief Acceder à la position absolue du gadget.
    ///
    /////////////////////////////////////////////////
    sf::Vector2f getPosAbs () const;

    /////////////////////////////////////////////////
    /// \brief Surcharge du SFML
    ///
    /////////////////////////////////////////////////
    void move(float offsetX, float offsetY);

    ////////////////////////////////////////////////////////////
    /// \brief Surcharge du SFML
    ///
    ////////////////////////////////////////////////////////////
    void move(const sf::Vector2f& offset);

    /////////////////////////////////////////////////
    /// \brief S'aligner sur un autre gadget.
    ///
    /// \param cible		    gadget cible sur lequel s'aligner.
    /// \param alignementThis   L'endroit du gadget à aligner sur la cible.
    /// \param alignementCible	L'endroit de la cible sur lequel aligner le gadget.
    /////////////////////////////////////////////////
    void aligner ( std::shared_ptr<Gadget> cible, Alignement alignementThis = Alignement::Centre , Alignement alignementCible = Alignement::Centre );







    /////////////////////////////////////////////////
    /// \brief Definir m_size.
    ///
    /////////////////////////////////////////////////
    virtual void setSize( sf::Vector2i val );

    /////////////////////////////////////////////////
    /// \brief Definir m_size.
    ///
    /////////////////////////////////////////////////
    virtual void setSize( int x , int y );

    /////////////////////////////////////////////////
    /// \brief Acceder à m_size.
    ///
    /////////////////////////////////////////////////
    sf::Vector2i getSize () const { return m_size; };

//protected:
    /////////////////////////////////////////////////
    /// \brief Acceder à m_globalBounds.
    ///
    /////////////////////////////////////////////////
    sf::IntRect getGlobalBounds () const { return m_globalBounds; };

    /////////////////////////////////////////////////
    /// \brief Acceder à m_localBounds.
    ///
    /////////////////////////////////////////////////
    sf::IntRect getLocalBounds () const { return m_localBounds; };

    /////////////////////////////////////////////////
    /// \brief Acceder à au bounds total des enfants.
    ///
    /// \return le bounds des enfnats
    /////////////////////////////////////////////////
    sf::IntRect getEnfantsLocalBounds () ;








/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:

    /// Propriétés diverses /////////////////////
    bool            m_visible; ///< La visibilité du gadget ( true :visible, false: caché )


    /// Composite /////////////////////
    Gadget*                                 m_parent;               ///< Le gadget parent.
    std::vector<std::shared_ptr<Gadget>>    m_enfants;              ///< les liste des gadgets enfants.
    std::vector<std::shared_ptr<Gadget>>    m_enfantsASupprimer;    ///< les liste des gadgets enfants à supprimer dans le traitement des evenements.


    /// Geométrie /////////////////////
    sf::Vector2i    m_size;             ///< La taille du gadget.
    sf::IntRect     m_globalBounds;     ///< Les limites globales du gadget (par rapport à la fenêtre principale).
    sf::IntRect     m_localBounds;      ///< Les limites locales du gadget (par rapport à son parent).
    sf::Vector2f    m_marge;            ///< la marge est l'espace entre texte ou icone et le fond par exemple.


    /// le shader /////////////////
    sf::Shader      m_shaderClipImage;  ///< Le shader qui permet de clipper les enfants de la fenêtre qui sortent de la zone d'affichage \todo Reintegrer en RAII les shaders!!
    sf::Shader      m_shaderClip;       ///< Le shader qui permet de clipper les enfants de la fenêtre qui sortent de la zone d'affichage \todo Reintegrer en RAII les shaders!!


}; // fin class Gadget

} // fin namespace gui

#endif



