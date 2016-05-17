/**
* \file     Application.h
* \brief    La classe principale du programme.
* \author   Christophe Pages
* \version  0.1
* \date     2015
* \details  Programme minimal g�rant differents �crans (intro, accueil, jeu, options...)
*/


#ifndef APPLICATION_H
#define APPLICATION_H

/////////////////////////////////////////////////
//  Headers
/////////////////////////////////////////////////
#include <Ecran.h>
#include <Gestion_ecrans.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "gui.h"

namespace app {  ///<  app Espace de l'application.

class Ecran;

/////////////////////////////////////////////////
/// \brief  La classe de base du programme.
///
/////////////////////////////////////////////////
class Application
{
    public:

        enum Ecrans {
            Accueil,
            Jeu

        };

        /////////////////////////////////////////////////
        /// \brief Constructeur
        ///
        /////////////////////////////////////////////////
        Application();

        /////////////////////////////////////////////////
        /// \brief Destructeur
        ///
        /////////////////////////////////////////////////
        virtual ~Application();

    public:



        /////////////////////////////////////////////////
        /// \brief Changer d'�cran
        ///
        /// \return Rien
        ///
        /////////////////////////////////////////////////
        void changerEcran( Ecrans ecran );

        /////////////////////////////////////////////////
        /// \brief ajouter un �cran
        ///
        /// \return Rien
        ///
        /////////////////////////////////////////////////
        void ajouterEcran( Ecrans ecran );

        /////////////////////////////////////////////////
        /// \brief retirer un �cran
        ///
        /// \return Rien
        ///
        /////////////////////////////////////////////////
        void retirerEcran(  );


        /////////////////////////////////////////////////
        /// \brief La boucle principale.
        ///
        /// \return Rien
        ///
        /////////////////////////////////////////////////
        void executer();

        /////////////////////////////////////////////////
        /// \brief La gestion des �v�nements utilisateurs.
        ///
        ///  G�re les entr�es claviers, souris, fenetre ...
        /// \return Rien
        ///
        /////////////////////////////////////////////////
        void traiter_evenements ();

        /////////////////////////////////////////////////
        /// \brief Actualiser les �l�ments.
        ///
        /// Actualiser les diff�rents �l�ments du ou des �crans actifs.
        /// \param deltaT          Un \e float qui indique le delta du temps �coul� depuis la derni�re actualisation.
        /// pour ponderer les mouvements en fonction du temps et ainsi avoir une ind�pendance entre animation et frame rate.
        ///
        /////////////////////////////////////////////////
        void actualiser ( float deltaT );

        /////////////////////////////////////////////////
        /// \brief Rendre les �l�ments.
        ///
        /// Dessiner les diff�rents �l�ments du ou des �crans actifs.
        /// \return Rien
        ///
        /////////////////////////////////////////////////
        void dessiner ( );

        /////////////////////////////////////////////////
        /// \brief renvois la fenetre sfml de l'application
        ///
        /// \return la fenetre sfml de l'application
        ///
        /////////////////////////////////////////////////
        sf::RenderWindow*    getFenetre();


        /////////////////////////////////////////////////
        /// \brief renvois le gestionnaire d'interface
        ///
        /// \return le gestionnaire d'interface
        ///
        /////////////////////////////////////////////////
        std::shared_ptr<gui::Interface>    getInterface() {return m_interface;};


        /////////////////////////////////////////////////
        /// \brief renvois le gestionnaire d'interface
        ///
        /// \return le gestionnaire d'interface
        ///
        /////////////////////////////////////////////////
        std::shared_ptr<gui::Interface>    getEcran( int i ) {return m_interface;};

    private:

        /////////////////////////////////////////////////
        // Les membres
        /////////////////////////////////////////////////
        Gestion_ecrans                      m_ecrans;       ///< Le gestionnaire des �crans.
        sf::RenderWindow*                   m_fenetre;      ///< La fen�tre SFML
        std::shared_ptr<gui::Interface>     m_interface;    ///< Le gestionnaire d'interface

};
}; // fin namespace app


#endif // APPLICATION_H


////////////////////////////////////////////////////////////
/// \class app::Application
/// \ingroup application
/// \defgroup application Module pour Application
///
/// G�re les diff�rents �crans du programme
/// (�cran d'introduction, accueil, pause, �cran du jeu ....)
///
/// Peut-�tre pour tester d'autre trucs, comme la bibilo d'interface graphique... ou comme base pour demarrer un nouveau projet.
///
/// Manipule les diff�rents �crans de l'application � l'aide d'une boucle infernalede type :
/// \li Ecouter les �venements utilisateurs ( claviers, cliques...).
/// \li Actualiser les parametres de tout les �l�ments ( position, couleurs, points de vies ... ).
/// \li Dessiner les �l�ments dans la fenetre
///
/// C'est le gestionnaire des �crans ( m_ecrans app:Gestion_Ecrans ) qui se charge du traitement de la pile des �crans.
///
/// Quand il n'y a plus d'�crans dans la pile, l'application se ferme.
///
/// \see app::Ecran, app::EcranDemo, app::Gestion_ecrans
///
////////////////////////////////////////////////////////////
