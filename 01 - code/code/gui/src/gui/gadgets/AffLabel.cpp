/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <gadgets/AffLabel.h>
#include <gui.h>



namespace gui {

/////////////////////////////////////////////////
AffLabel::AffLabel ()
: Affiche ()
, m_texteSFML   (  )
, m_textCouleur ( sf::Color::White )
, m_textStyle   ( sf::Text::Style::Regular )
, m_textTaille  ( 15 )
, m_textPolice  ( Interface::ms_polices.get ( "Defaut" ) )

, m_affContenant ( std::make_shared<sf::Sprite>() )
, m_aliasTexture ( 2 )

{
    // Creation du nom unique du gadget
    creerNomUnique( "Label" );




    actualiserStyle();
}

/////////////////////////////////////////////////
void AffLabel::actualiserGeometrie ()
{
    // Debuggage
    log ("actualiserGeometrie");

//    rendreTexte ();
//    m_texteSFML.setString ( m_texte );



}

/////////////////////////////////////////////////
void AffLabel::rendreTexte (){

    auto txtBounds = m_texteSFML.getLocalBounds();
    sf::Vector2i txtTaille = { txtBounds.left + txtBounds.width , txtBounds.top + txtBounds.height  };

    m_renderTexture.create      ( txtTaille.x  , txtTaille.y );

    // Render to texture des enfants
    m_renderTexture.clear   ( sf::Color::Transparent );

    m_renderTexture.draw    ( m_texteSFML );
    m_renderTexture.display ();
    m_renderTexture.setSmooth( true );

     // on applique la texture
    m_affContenant->setTexture( m_renderTexture.getTexture() );

}

/////////////////////////////////////////////////
void AffLabel::actualiserStyle ()
{
    // Debuggage
    log ("actualiserStyle");

    m_texteSFML.setFont            ( m_textPolice );
    m_texteSFML.setColor           ( m_textCouleur );
    m_texteSFML.setStyle           ( m_textStyle );
    m_texteSFML.setCharacterSize   ( m_textTaille );
//    m_texteSFML.setScale            ( m_aliasTexture ,m_aliasTexture );
//    m_texteSFML.setCharacterSize   ( m_textTaille * m_aliasTexture );

}



/////////////////////////////////////////////////
void AffLabel::setTexte( std::string val )
{
    // Debuggage
    log("setTexte");
    log("m_texte",  val  );
//    m_mute = false;

//    m_texte = val;
    m_texteSFML.setString( val );
    demanderActualisation();
};


/////////////////////////////////////////////////
void AffLabel::setTexteTaille( float val ){
    m_textTaille = val;
    m_texteSFML.setCharacterSize ( val ) ;
    // la taille du texte a changé alors on doit recalculé les bounds
    demanderActualisation();
};


/////////////////////////////////////////////////
void AffLabel::setTexteCouleur( sf::Color couleur ){
    m_textCouleur = couleur;
    m_texteSFML.setColor ( couleur );
    demanderActualisation();
};


/////////////////////////////////////////////////
void AffLabel::setTextePolice( sf::Font val ){
    std::string txtTmp =  m_texteSFML.getString( );
    m_textPolice = val;
    m_texteSFML.setString( txtTmp );
    // la taille du texte a changé alors on doit recalculé les bounds
    demanderActualisation();
};


/////////////////////////////////////////////////
void AffLabel::setTexteStyle( sf::Text::Style val ){
    m_textStyle = val;
    m_texteSFML.setStyle    ( m_textStyle );

    // la taille du texte a changé alors on doit recalculer les bounds
    demanderActualisation();
};


/////////////////////////////////////////////////
sf::Vector2i  AffLabel::getTaille() const{
    return { m_texteSFML.getGlobalBounds().width , m_texteSFML.getGlobalBounds().height };
}




/////////////////////////////////////////////////
void AffLabel::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    //On applique la transformation
    states.transform *= getTransform();


//    // On dessine le texte
    target.draw( m_texteSFML, states);

    // On dessine le sprtie qui contient le texte
//    target.draw( *m_affContenant, states);

}




} // fin namespace gui















