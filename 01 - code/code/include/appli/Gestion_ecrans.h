#ifndef GESTION_ECRANS_H
#define GESTION_ECRANS_H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "appli/Ecran.h"
#include <memory>
#include <map>
#include <functional>

namespace app{

/////////////////////////////////////////////////
/// \brief Classe qui s'occupe de gérer les écrans
///
/// L'idée c'est que chaque écran doit d'abords être enregistré dans la fabrique à l'initialisation de l'appli
/// L'enregistrement ne créer pas l'écran mais associe une ID et une fonction lambda dans un <map> qui le créera au moment voulu.
/// Les actions sur les écrans ne sont enregistrés dans une liste ( m_modifEnAttente ) et réalisé qu'à la fin de la frame (appliquerModifEnAttente()).
/// Cela permet par exemple qu'un écran se supprime lui-même sans tout faire planter.
///
/////////////////////////////////////////////////
class Gestion_ecrans
{
public:

    /////////////////////////////////////////////////
    /// \brief Les differentes actions réalisables sur les ecrans
    ///
    /////////////////////////////////////////////////
    enum Action    {
        Ajouter,
        Retirer,
        Vider
    };

    /////////////////////////////////////////////////
    /// \brief Constructeur (explicit, j'ai pas encore bien compris ce truc)
    ///
    /// \param le contexte courant transmit par l'application.
    /////////////////////////////////////////////////
    explicit Gestion_ecrans ( Ecran::Contexte contexte );



    /////////////////////////////////////////////////
    /// \brief fonction Template pour enregistrer les écrans dans m_factories.
    ///
    ///  Necessaire pour manipuler les écrans de tous les enregistrer au debut.
    ///  En gros ça fait un lien entre les Ecrans::ID et les classes Ecran proprement dites.
    ///  Pour enregister la classe Ecran concrete EcranAccueil :
    /// \code this.enregistrerEtat <EcranAccueil> ( Ecrans::ID::Accueil );
    /// \endcode
    ///
    /// \param ercanID L'identification de l'etat.
    /////////////////////////////////////////////////
    template    <typename T>
    void        enregistrerEcran( Ecrans::ID  ecranID );






    /////////////////////////////////////////////////
    /// \brief Ajouter un écran sur la pile
    ///
    /// \param ecranID L'ID de l'Ecran à ajouter à la pile active.
    /// \return Rien.
    /////////////////////////////////////////////////
    void    ajouter ( Ecrans::ID ecranID );

    /////////////////////////////////////////////////
    /// \brief Retirer l'écran du dessus de la pile.
    ///
    /// \return Rien.
    ///
    /////////////////////////////////////////////////
    void    retirer ();

    /////////////////////////////////////////////////
    /// \brief Retirer tout les écrans de la pile.
    ///
    /// \return Rien.
    ///
    /////////////////////////////////////////////////
    void    vider ();





    /////////////////////////////////////////////////
    /// \brief Demande si il y a encore des ecrans dans la pile
    ///
    /// \return bool true si vide.
    ///
    /////////////////////////////////////////////////
    bool    estVide () const;





    /////////////////////////////////////////////////
    /// \brief Gère les évenements  des écrans actifs.
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void traiter_evenements (sf::Event event );

    /////////////////////////////////////////////////
    /// \brief Actualiser les éléments.
    ///
    /// Actualiser les différents éléments du ou des écrans actifs.
    /// \param deltaT          Un \e float qui indique le delta du temps écoulé depuis la dernière actualisation.
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void actualiser ( sf::Time deltaT );

    /////////////////////////////////////////////////
    /// \brief Rendre les écrans de la pile.
    ///
    /// Dessine les différents éléments du ou des écrans de la pile.
    ///
    /// \return Rien
    ///
    /////////////////////////////////////////////////
    void dessiner ();

private:

    ///< le struct qui porte l'info de ce qu'il doit faire comme modif sur la pile
    struct ModifEnAttente
        {
            /////////////////////////////////////////////////
            /// \brief constructeur
            /// \param action l'action à effectuer
            /// \param etatID
            ///
            /////////////////////////////////////////////////
            explicit		ModifEnAttente(Action actionAEffectuer, Ecrans::ID ecranIDAMAnipuler = Ecrans::Vide)
                                        : action ( actionAEffectuer )
                                        , ecranID ( ecranIDAMAnipuler ){};
            Action          action;
            Ecrans::ID      ecranID;
        };

    /////////////////////////////////////////////////
    /// \brief Créer un Ecran.
    /// Va chercher dans la factory l'id demandé, et créer l'écran  grace à la fonction lambda associé à l'ID
    ///
    /// \param ecranID l'ID de l'Ecran à créer.
    ///
    /// \return un unique_ptr vers l'ecran créé.
    /////////////////////////////////////////////////
    std::unique_ptr<Ecran>   creerEcran( Ecrans::ID ecranID  );

    /////////////////////////////////////////////////
    /// \brief Appliquer les modifications de la pile de modifs.
    /// C'est là qu'on manipule réelement les écrans (création, destruction...)
    ///
    /// \return Rien
    /////////////////////////////////////////////////
    void        appliquerModifEnAttente();


private:

    /////////////////////////////////////////////////
    //  Membres
    /////////////////////////////////////////////////
    std::vector<std::unique_ptr<Ecran>>             m_pile;             ///< La pile des écrans actifs.
    std::vector<ModifEnAttente>                     m_modifEnAttente;   ///< La liste des modifications à éffectuer sur la pile des Ecrans.
    std::map<Ecrans::ID
        ,std::function<std::unique_ptr<Ecran>()>>   m_factories;        ///< C'est ce qui va créer les Ecrans à la volée. Un ID associé à une fonction Lambda qui va nous creer les écrans voulus.
    Ecran::Contexte                                 m_contexte;         ///< Le contexte de l'application (fenetre SFML, polices...) (à developper)

}; // Gestion_ecrans




/////////////////////////////////////////////////
template <typename T>
void Gestion_ecrans::enregistrerEcran( Ecrans::ID ecranID )
{
    m_factories[ ecranID ] = [this] ()
    {
        return std::unique_ptr<Ecran>( new T(*this, m_contexte ) );
    };
}




}; // namespace app






#endif // GESTION_ECRANS_H


////////////////////////////////////////////////////////////
/// \class app::Gestion_ecrans
/// \ingroup application
///
/// Gère les différents écrans de l'application.
/// C'est lui qui porte les écrans actifs du programme.
/// qui permet de passer d'un écran à l'autre, etc.
/// \see app::Ecran
///
////////////////////////////////////////////////////////////




