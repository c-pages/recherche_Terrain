/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <interfaces/ActionClavier.h>
#include <iostream>




namespace gui {

/////////////////////////////////////////////////
void ActionClavier::lier ( sf::Keyboard::Key   touche, FctnAction fonction)
{
//    std::cout << "  -> nouvelle LIAISON Clavier !\n";
    m_evenementsClavier.insert( { touche , fonction } );
}


/////////////////////////////////////////////////
void ActionClavier::delier ( sf::Keyboard::Key   touche)
{
    m_evenementsClavier.erase( touche  );
}

/////////////////////////////////////////////////
void ActionClavier::viderLiaisons ( )
{
    m_evenementsClavier.clear();
}


/////////////////////////////////////////////////
void ActionClavier::traiterEvenementsClavier (sf::Event evenement)
{
    if ( evenement.type == sf::Event::KeyPressed )
        for (auto evt : m_evenementsClavier )
            if ( evenement.key.code == evt.first )
                evt.second();
}

} // fin namespace gui

