#ifndef GUI__H
#define GUI__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "Gadget.h"
#include <memory>
#include  "Fabrique.h"



namespace gui {

class Gui;
class Calque;
class Calque;


/////////////////////////////////////////////////
/// \brief Le Gui g�re l'ensemble des interactions homme-machine du jeu.
/// D'un cot� un syst�me de fen�tre, boutons basique g�rant les diff�rents menus de l'appli.
/// De l'autre, le menu ph�romones, syst�me central de l'interaction du joueur avec ses fourmis.
/// Une seul instance possible ( design pattern :Singleton)
///
/////////////////////////////////////////////////
class Gui : public gui::Gadget {



/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
public:
    /////////////////////////////////////////////////
    /// \brief Appel � l'instance de l'interface, la cr�er si par encore appel�.
    ///
    /////////////////////////////////////////////////
    static std::shared_ptr<Gui> getInstance ();

    /////////////////////////////////////////////////
    /// \brief Traitement g�n�ral des �venements clavier ou souris de tout les gadgets de l'interface.
    ///
    /// \param evenement		 L'�venemnt � tratier.
    /////////////////////////////////////////////////
    void traiterEvenements (sf::Event evenement);

    /////////////////////////////////////////////////
    /// \brief Actualiser les �l�ments de l'interface.
    ///
    /////////////////////////////////////////////////
    void actualiser ();

    /////////////////////////////////////////////////
    /// \brief Dessine tout les �l�ments de l'interface.
    ///
    /// \param target		 
    /// \param states		 
    /////////////////////////////////////////////////
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

private:
    /////////////////////////////////////////////////
    /// \brief Constructeur priv�e pour enp�cher les doublons.
    ///
    /////////////////////////////////////////////////
    Gui ();

    /////////////////////////////////////////////////
    /// \brief Constructeur par copie, bloqu� car priv�.
    ///
    /// \param copie		 
    /////////////////////////////////////////////////
    Gui (const Gui& copie);



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    static std::shared_ptr<Gui> ms_instance;    ///< L'unique instance de l'interface.    
    Calque m_calqueFond;    ///< Le calque regroupant les gadgets les plus au fond de la vue.    
    Calque m_calqueFenetres;    ///< Le calque regroupant les fenetres.    
public:
    gui::Fabrique creer;     ///< La fabrique des gadget.

}; // fin class Gui

} // fin namespace gui

#endif
