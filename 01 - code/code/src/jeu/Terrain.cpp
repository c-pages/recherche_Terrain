/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <jeu/Terrain.h>

#include <jeu/Etage.h>


namespace jeu {

/////////////////////////////////////////////////
Terrain::Terrain ()
: m_etages ( 0 )
, m_indexEtageCourant ( 0 )
, m_taille ( {0,0} )
//, m_shaderGrille (  )
//, m_shaderHachures (  )
//, m_shaderOmbre (  )
//, m_shaderAO (  )
//, m_couleurSol (  )
//, m_couleurTerre (  )
//, m_couleurOmbres (  )
{

}


/////////////////////////////////////////////////
void Terrain::genererEtages (int seed)
{

}


/////////////////////////////////////////////////
void Terrain::initialiser ()
{

}


/////////////////////////////////////////////////
void Terrain::draw (sf::RenderTarget& target, sf::RenderStates states) const
{

}


} // fin namespace jeu

