
/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <Application.h>
#include <windows.h> /* pour les fonctions GetConsoleOutputCP et associ�es */




/////////////////////////////////////////////////
/// Point d'�ntr�e de l'application
///
/// \return Sortie de l'application.
///
/////////////////////////////////////////////////
int main()
{

    // pour les accents dans la console
    ///< \todo trouver un truc pour les accents
    //    SetConsoleOutputCP(1252);

    //  creation de l'application.
    app::Application     appli;

    //  execution de l'application
    appli.executer();

    // fin de l'pplication
    return 0;
}



