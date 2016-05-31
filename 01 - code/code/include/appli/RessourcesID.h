#ifndef RESSOURCESID_H
#define RESSOURCESID_H

/////////////////////////////////////////////////
/// \todo cette lise d'enum n'est pas encore utilisé ( cf. SFML Game development )
/// RAII à implémenter corrsctement. Question sur les shaders quand on les utilise sans pointeurs... (cf gui::Gadget).
///
/////////////////////////////////////////////////
namespace app {

/////////////////////////////////////////////////
/// \brief les polices enregistrables dans le manager de polices
///
/////////////////////////////////////////////////

namespace Polices {
    enum  ID    {   police_1
                ,   police_2
                ,   log
                };
}
/////////////////////////////////////////////////
/// \brief les images enregistrables dans le manager de texture
///
/////////////////////////////////////////////////
namespace Images {
    enum ID     {   image_1
                ,  image_2
                ,  fenetreFond1
                ,  FondAccueil
                };
}

/////////////////////////////////////////////////
/// \brief les shaders enregistrables dans le manager de shaders
///
/////////////////////////////////////////////////
namespace Shaders {
    enum ID     {  clipping
                };

    }

} // fin namespace app

#endif // RESSOURCESID_H
