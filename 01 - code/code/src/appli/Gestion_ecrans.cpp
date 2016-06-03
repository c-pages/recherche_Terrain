
/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include "appli/Gestion_ecrans.h"
#include <iostream>
#include <cassert>

namespace app
{

/////////////////////////////////////////////////
Gestion_ecrans::Gestion_ecrans ( Ecran::Contexte contexte )
: m_contexte ( contexte )
{ };



/////////////////////////////////////////////////
Ecran&    Gestion_ecrans::at ( unsigned int index )
{
    if ( index< m_pile.size() )
        return *m_pile[ index ];
}


/////////////////////////////////////////////////
unsigned int    Gestion_ecrans::size ( )
{
   return m_pile.size();
}



/////////////////////////////////////////////////
void        Gestion_ecrans::ajouter(Ecrans::ID ecranID)
{
    m_modifEnAttente.push_back(ModifEnAttente(Ajouter, ecranID));
//    std::cout << "Gestion_ecrans::ajouter" << std::endl;
}


/////////////////////////////////////////////////
void        Gestion_ecrans::retirer()
{
	m_modifEnAttente.push_back(ModifEnAttente(Retirer));
//    std::cout << " Gestion_ecrans::retirer()" << std::endl;
}


/////////////////////////////////////////////////
void        Gestion_ecrans::vider()
{

    m_modifEnAttente.push_back(ModifEnAttente(Vider));
//    std::cout << "Gestion_ecrans::vider()" << std::endl;
}


/////////////////////////////////////////////////
bool        Gestion_ecrans::estVide() const
{
    //std::cout << "eeeeeeeeeeeeeeestVide ? : " << std::endl;
    return m_pile.empty();
}






/////////////////////////////////////////////////
std::unique_ptr<Ecran>    Gestion_ecrans::creerEcran(Ecrans::ID ecranID)
{
    auto trouve = m_factories.find(ecranID);

    /// ---> assertion: Pour gestion erreurs ... :
    /// si pas trouve => on fait l'assert
    assert( trouve != m_factories.end() );

    /// et on retourne  le resultat de l'execution de la fonction lambda associée( créée dans Gestion_ecrans::enregistrerEtat), qui créé
    /// un nouvel ecran et retourne un pointeur vers celui ci.
    return trouve->second();
}



/////////////////////////////////////////////////
void        Gestion_ecrans::appliquerModifEnAttente()
{
    int i = 0 ;
    for (auto itr = m_modifEnAttente.begin(); itr != m_modifEnAttente.end(); ++itr)
    {
        i++;
        switch ((*itr).action)
        {
            case Ajouter:
                m_pile.push_back( creerEcran((*itr).ecranID) );
                break;
            case Retirer:
                m_pile.pop_back();
                break;
            case Vider:
                m_pile.clear();
                break;
        }
    }
    m_modifEnAttente.clear();
}







/////////////////////////////////////////////////
void    Gestion_ecrans::traiter_evenements (sf::Event event )
{

    for (auto itr = m_pile.rbegin(); itr != m_pile.rend(); ++itr)
        (*itr)->traiter_evenements(event);

    appliquerModifEnAttente();
}


/////////////////////////////////////////////////
void    Gestion_ecrans::actualiser ( sf::Time deltaT )
{

    for (auto itr = m_pile.rbegin(); itr != m_pile.rend(); ++itr)
        (*itr)->actualiser(deltaT);


    appliquerModifEnAttente();
}


/////////////////////////////////////////////////
void    Gestion_ecrans::dessiner ()
{
    for (auto itr = m_pile.begin(); itr != m_pile.end(); ++itr)
        (*itr)->dessiner();

}





}// fin app
