/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <interfaces/Filiation.h>
//#include <Contenant.h>

#include <interfaces/Gadget.h>
#include <gui.h>
#include <stdio.h>

namespace gui {

/////////////////////////////////////////////////
void Filiation::ajouter (std::shared_ptr<Gadget> enfant)
{

    // si l'enfant avait un parent on le retire de sa liste des enfants
    auto parentBack = enfant->getParent();
    if ( parentBack != nullptr )
        parentBack->retirer ( enfant );

    m_enfants.push_back( enfant );

    auto _this = static_cast<Gadget*>( this );
    enfant->setParent ( _this );


    log ("AJOUTER ENFANT" );

    enfant->demanderActualisation();
    enfant->actualiserGeometrie();
//    _this->actualiser();

    _this->demanderActualisation();
    _this->actualiserGeometrie();
}


/////////////////////////////////////////////////
std::string Filiation::getHierarchie() const {
    if (m_parent!=nullptr) {
        if ( m_parent->getNom()[0] == '_' )    {
            return ""  ;
        } else return m_parent->getHierarchie()  + m_parent->getNom() + " / "  ;
    } else return "";
};


/////////////////////////////////////////////////
std::string Filiation::getCalqueNom()  {

    std::string nom = static_cast<Gadget*>(this)->getNom();

    if ( nom[0] == '_' )    {
        nom.erase(0, 1);
        return nom ;
    } else if (m_parent!=nullptr)
        return m_parent->getCalqueNom();
    else if ( static_cast<Gadget*>(this)->estInterface () )
        return "";
    else return "-";

};

//
///////////////////////////////////////////////////
//void Filiation::actualiserContenu (){
//    // on demande juste au parent d'actualiser son contenu ...
//    if ( m_parent != nullptr ) m_parent->actualiserContenu();
//};

///////////////////////////////////////////////////
//void Filiation::actualiserMasque () {
//
//    // on demande juste au parent d'actualiser son contenu ...
//    if ( m_parent != nullptr ) m_parent->actualiserMasque();
//}

/////////////////////////////////////////////////
void Filiation::ajouter ( std::shared_ptr<Gadget> enfant, unsigned int index )    {

    // si l'enfant avait un parent on le retire de sa liste des enfants
    auto parentBack = enfant->getParent();
    if ( parentBack != nullptr )
        parentBack->retirer ( enfant );

    m_enfants.insert ( m_enfants.begin() + index, enfant );

    auto _this = static_cast<Gadget*>( this );
    enfant->setParent ( _this );


    enfant->demanderActualisation();
    enfant->actualiserGeometrie();
//    _this->actualiser();

    _this->demanderActualisation();
    _this->actualiserGeometrie();

//    std::cout <<"Filiation::ajouter reussi\n";
};

/////////////////////////////////////////////////
void Filiation::setParent( Gadget* val )
{
    m_parent = val;
//    m_parent->actualiser();
};


/////////////////////////////////////////////////
std::shared_ptr<Gadget> Filiation::retirer ( std::shared_ptr<Gadget> gadget )
{
//    std::cout << "Filiation::retirer\n";
    int i = 0;
    for ( auto enfant : m_enfants ){
        if ( enfant == gadget ) {
            m_enfants.erase( m_enfants.begin()+i );
            return enfant;
        }
        i++;
    }
    static_cast<Gadget*>(this)->actualiser();
}

/////////////////////////////////////////////////
void Filiation::demander_aEtre_supprimer (){
//    std::cout << static_cast<Gadget*>(this)->getNom() << " -> demander_aEtre_supprimer\n";
    log ("m_parent", m_parent );

    m_parent->demanderASupprimer ( thisPtr() );
}



/////////////////////////////////////////////////
std::shared_ptr<Gadget> Filiation::testerSurvolEnfants ( sf::Vector2i position )
{
//    std::cout << "testerSurvolEnfants\n";
    for ( int i =0; i< m_enfants.size(); i++ )
    {
//        std::cout << "..." << i << " : " <<position.x <<", " << position.y <<  "\n";
        int index = m_enfants.size() - (i+1);
        auto  enfant = m_enfants[ index ];

        auto testEnfant = enfant->testerSurvol( position );
        if ( testEnfant != nullptr )
            return testEnfant;
    }
    return nullptr;
}


/////////////////////////////////////////////////
void Filiation::viderEnfants (){
//    printf ("viderEnfants\n");
    for (auto enfant : m_enfants) {
//        std::cout << "   Enfant : " << enfant->getNom() << "\n";
        enfant->demander_aEtre_supprimer();

    }

//    static_cast<Gadget*>(this)->demanderActualisation();

//    static_cast<Gadget*>(this)->actualiser();
//    actualiserListes();
    static_cast<Gadget*>(this)->demanderActualisation();
}




/////////////////////////////////////////////////
void Filiation::demanderASupprimer (std::shared_ptr<Gadget> gadget ){

    log("demanderASupprimer");
//    std::cout << static_cast<Gadget*>(this)->getNom() << " -> demanderASupprimer : " << gadget->getNom() << "\n";

    m_enfantsASupprimer.push_back( gadget );
//    std::cout << static_cast<Gadget*>(this)->getNom() << " -> m_enfantsASupprimer : " << m_enfantsASupprimer.size() << "\n";


    static_cast<Gadget*>(this)->demanderActualisation();
}

/////////////////////////////////////////////////
void Filiation::supprimer (std::shared_ptr<Gadget> gadget ){

    int i = 0;
    int result = 0;
    for ( auto enfant : m_enfants ){
        if ( enfant == gadget ) {
            result = i;
            break;
        }
        i++;
    }
    log ( "supprimer : " + gadget->getNom() );

//    std::cout << "   supprimer : " << gadget->getNom() << "\n";

    Interface::vider_msBoutons () ;

    m_enfants.erase( m_enfants.begin()+result );



//    Interface::ms_boutonSurvole != nullptr ;
    //Interface::ms_boutonSurvole != nullptr

}

/////////////////////////////////////////////////
void Filiation::actualiserListes ( ){
//printf("actualiserListes\n");
    log("actualiserListes");
    if ( m_enfantsASupprimer.empty() ) return ;

    for ( auto enfant : m_enfantsASupprimer )
        supprimer ( enfant );

    m_enfantsASupprimer.clear();

    static_cast<Gadget*>(this)->demanderActualisation();
//    static_cast<Gadget*>(this)->actualiser();
}


/////////////////////////////////////////////////
sf::IntRect  Filiation::boundgingB_enfants()
{
        sf::IntRect result;
        if ( m_enfants.size() == 0 )
            return result;

        int minX = 90000;
        int minY = 90000;
        int maxX = -90000;
        int maxY = -90000;

        for ( auto enfant : m_enfants )
        {
            sf::FloatRect LB = enfant->getLocalBounds();

            if (LB.left < minX) minX = LB.left;
            if (LB.top  < minY) minY = LB.top;
            if (LB.left + LB.width > maxX ) maxX = LB.left + LB.width;
            if (LB.top  + LB.height> maxY ) maxY = LB.top  + LB.height;

        }

        result.left     = minX;
        result.top      = minY;
        result.width    = maxX - minX;
        result.height   = maxY - minY;

        return result;
}

/////////////////////////////////////////////////
void Filiation::actualiserEnfants (){
    for ( auto enfant : m_enfants )
        enfant->actualiser();
}

/////////////////////////////////////////////////
void Filiation::actualiserEnfants ( sf::Time delta ){
    for ( auto enfant : m_enfants )
        enfant->actualiser( delta );
}

/////////////////////////////////////////////////
void Filiation::dessinerEnfants (sf::RenderTarget& target, sf::RenderStates states) const
{
    for ( auto enfant : m_enfants )
        target.draw( *enfant , states);
}

/////////////////////////////////////////////////
void Filiation::demander_aEtre_auDessus ()
{
    m_parent->mettre_auDessus ( thisPtr() );
}

/////////////////////////////////////////////////
void Filiation::mettre_auDessus ( std::shared_ptr<Gadget> gadget )
{
//    std::cout << "Mettre au dessus\n";
    // on supprime le gadget de sa place dans le tableau
    int i = 0;
    int result = 0;
    for ( auto enfant : m_enfants ){
        if ( enfant == gadget ) {
            result = i;
            break;
        }
        i++;
    }
    m_enfants.erase( m_enfants.begin()+result );

    // puis on le replace à la fin du tableau
    m_enfants.push_back( gadget );

}



} // fin namespace gui



