#ifndef ACTIONS__H
#define ACTIONS__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <map>
#include <SFML/Graphics.hpp>
#include <functional>



namespace gui {



/////////////////////////////////////////////////
/// \brief Classe abstraite qui g�re les �venements claviers et souris
///
/////////////////////////////////////////////////
class Actions {


/////////////////////////////////////////////////
// Enums & typedefs
/////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /// \brief les evenements de la souris qui d�clenchent une fonction lambda associ�e.
    /////////////////////////////////////////////////
    enum Evenement {
        onBtnG_dblCliquer,            ///< Double clique gauche
        onBtnG_relacher,            ///< Relache le bouton gauche de la souris.
        onBtnG_relacherDehors,            ///< Relache a cot� du gadget avec le bouton gauche de la souris apr�s avoir press� dedans.
        onBtnG_presser,            ///< Presse le bouton gauche de la souris.
        onBtnG_presserDehors,            ///< Presse a cot� du gadget avec le bouton gauche de la souris.
        onBtnD_relacher,            ///< Relache le bouton droit de la souris.
        onBtnD_relacherDehors,            ///< Relache le bouton droit de la souris.
        onBtnD_presser,            ///< Presse le bouton droit de la souris.
        onBtnM_relacher,            ///< Relache le bouton du milieu de la souris.
        onBtnM_relacherDehors,            ///< Relache le bouton du milieu de la souris.
        onBtnM_presser,            ///< Presse le bouton du milieu de la souris.
        onBtnM_roulerHaut,            ///< Roule vers le haut le bouton du milieu de la souris.
        onBtnM_roulerBas,            ///< Roule vers le bas le bouton du milieu de la souris.
        onBtn_entrer,            ///< Survol
        onBtn_sortir,            ///< Quitte le survol.
        onBtn_changerEtat,            ///< quand BoutonACocher change d'�tat
        onFen_fermer,            ///< Quand on ferme une fenetre.
        onFen_ouvrir,            ///< Quand on ferme une fenetre.
        onBool_changerValeur,            ///< Quand on change la valeur d'un champ de saisie de texte.
        onBool_validerValeur            ///< Quand on valide la valeur d'un champ de saisie de texte.
    };

    using FctnAction = std::function<void()>;    ///< le type de fonction associ� aux declenchements des evenements.


/////////////////////////////////////////////////
// M�thodes
/////////////////////////////////////////////////

public:
public:
    /////////////////////////////////////////////////
    /// \brief Contructeur
    ///
    /////////////////////////////////////////////////
    ActionSouris ();

    /////////////////////////////////////////////////
    /// \brief Cr�er une nouvelle liaison entre un evenement souris  et une fonction lambda.
    ///
    /// \param evenement		 evenement souris
    /// \param fonction		 Le fonction � d�clencher.
    /////////////////////////////////////////////////
    void lier  (Evenement evenement, FctnAction fonction);

    /////////////////////////////////////////////////
    /// \brief Cr�er une nouvelle liaison entre un evenement clavier  et une fonction lambda.
    ///
    /// \param touche		 la touche du clavier.
    /// \param fonction		 Le fonction � d�clencher.
    /////////////////////////////////////////////////
    void lier ( sf::Keyboard  touche, FctnAction fonction);

    /////////////////////////////////////////////////
    /// \brief Supprime une liaison entre un evenement souris  et une fonction lambda.
    ///
    /// \param evenement		 L'�venement � supprimer
    /////////////////////////////////////////////////
    void delier (Evenement evenement);

    /////////////////////////////////////////////////
    /// \brief Supprime une liaison entre un evenement clavier  et une fonction lambda.
    ///
    /// \param touche		 La touche de l'action � supprimer.
    /////////////////////////////////////////////////
    void delier ( sf::Keyboard  touche);

    /////////////////////////////////////////////////
    /// \brief Supprime toutes les actions du gadget.
    ///
    /////////////////////////////////////////////////
    void vider ();

protected:
    /////////////////////////////////////////////////
    /// \brief D�clencher un �venement souris (les �venement claviers sont g�rer.
    ///
    /// \param evenement		 
    /////////////////////////////////////////////////
    void declencher (Evenement evenement);

    /////////////////////////////////////////////////
    /// \brief D�clencher un �venement souris (les �venement claviers sont g�rer.
    ///
    /// \param touche		 La touche enregistr�e � une action.
    /////////////////////////////////////////////////
    void declencher (sf::Keyboard touche);

    /////////////////////////////////////////////////
    /// \brief Regarde si l'�ven�ment clavier envoy� correspond � une action li�e au gadget, et la d�clenche le cas �ch�ant.
    ///
    /// \param evenement		 L'�venement � analyser.
    /////////////////////////////////////////////////
    void traiterEvenements (sf::Event evenement);



/////////////////////////////////////////////////
// Membres
/////////////////////////////////////////////////
private:
    std::map < Evenement , FctnAction > m_evenementsSouris;    ///< la liste des evenements souris enregistr�s.    
    std::map < sf::Keyboard  , FctnAction > m_evenementsClavier;    ///<  la liste des evenements claviers enregistr�s.    

}; // fin class Actions

} // fin namespace gui

#endif
