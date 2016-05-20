#ifndef THEME__H
#define THEME__H

/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <map>



namespace gui {

class Style;


struct Theme {
    std::map<string, Texte::Style> texte;
};

} // fin namespace gui

#endif
