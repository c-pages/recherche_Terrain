#ifndef FILIATION__H
#define FILIATION__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Log.h"
#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include <iostream>



namespace gui {

class Gadget;


/////////////////////////////////////////////////
/// \brief Gestion des enfants, parent (GOF4: Filiation)
///
/////////////////////////////////////////////////
class Filiation : public Log {



/////////////////////////////////////////////////
// Méthodes
/////////////////////////////////////////////////

public:
    ///< Definir m_parent
    virtual void setParent( Gadget* val );

    ///< Acceder à m_parent
    Gadget* getParent () const { return m_parent; };

    virtual std::string     getHierarchie() const;
    std::string             getCalqueNom() ;




    virtual sf::Vector2i    getTailleContenant (){};

    virtual std::shared_ptr<Gadget> thisPtr(){
        std::cout << "DEMANDE DE thisPtr PROBLEMATIQUE\n";
        //return static_cast<std::shared_ptr<Gadget>> shared_from_this();
        return nullptr;
    };

public:
    /////////////////////////////////////////////////
    /// \brief Ajouter un gadget à la liste de gadgets enfant.
    ///
    /// \param enfant		 L'enfant à ajouter.
    /////////////////////////////////////////////////
    virtual void ajouter (std::shared_ptr<Gadget> enfant);

    virtual void ajouter ( std::shared_ptr<Gadget> enfant, sf::Vector2i positionEcran ){};
    virtual void ajouter ( std::shared_ptr<Gadget> enfant, unsigned int index );

    /////////////////////////////////////////////////
    /// \brief Retirer un enfant de la liste des enfants de ce gadget sans le supprimer.
    ///
    /// \param enfant		 L'enfant à retirer de la liste des enfants.
    /// \return L'enfant supprimer des enfants.
    /////////////////////////////////////////////////
    virtual std::shared_ptr<Gadget> retirer (std::shared_ptr<Gadget> enfant);

    virtual std::vector<std::shared_ptr<Gadget>>   getEnfants() const { return  m_enfants; } ;


    bool aDesEnfants () { return ( m_enfants.size() > 0 ); };


    /////////////////////////////////////////////////
    /// \brief Demander au parent de nous supprimer.
    ///
    /////////////////////////////////////////////////
    virtual void demander_aEtre_supprimer ();

    void demanderASupprimer ( std::shared_ptr<Gadget> gadget );

    virtual void actualiserEnfants( );

    virtual void actualiserEnfants( sf::Time delta );

//    virtual void actualiserContenu ();
//
//    void    actualiserMasque ();

    void actualiserListes ( );

    /////////////////////////////////////////////////
    /// \brief Supprimer un gadget.
    ///
    /// \param enfant		 L'enfant à supprimer.
    /////////////////////////////////////////////////
    virtual void supprimer (std::shared_ptr<Gadget> enfant);

    /////////////////////////////////////////////////
    /// \brief Supprime tout les enfants du gadget
    ///
    /////////////////////////////////////////////////
    void viderEnfants ();


    /////////////////////////////////////////////////
    /// \brief Demander au parent d'être mis au dessus des autres gadgets ( mouvements de la liste des enfants).
    ///
    /////////////////////////////////////////////////
    void demander_aEtre_auDessus ();

    /////////////////////////////////////////////////
    /// \brief Mettre au dessus des autres gadgets ( mouvements de la liste des enfants).
    ///
    /// \param gadget		 le pointeur vers le gadget à mettre au dessus des autres parmis m_enfants.
    /////////////////////////////////////////////////
    virtual void mettre_auDessus ( std::shared_ptr<Gadget> gadget);

    /////////////////////////////////////////////////
    /// \brief Dessiner les enfants du gadget.
    ///
    /// \param target
    /// \param states
    /////////////////////////////////////////////////
    virtual void dessinerEnfants (sf::RenderTarget& target, sf::RenderStates states) const ;

    std::shared_ptr<Gadget> testerSurvolEnfants (sf::Vector2i position);

    sf::IntRect  boundgingB_enfants();

    virtual bool aEnfants() { return  ( m_enfants.size()>0) ;};


/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
protected:


    std::vector<std::shared_ptr<Gadget>>    m_enfants;          ///< Les enfants du gadget.
    Gadget*                                 m_parent = nullptr; ///< Le gadget parent.

    std::vector<std::shared_ptr<Gadget>>    m_enfantsASupprimer;          ///< Les enfants du gadget.
}; // fin class Filiation

} // fin namespace gui

#endif
