/////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////
#include <Terrain.h>

#include <Etage.h>


namespace jeu {

/////////////////////////////////////////////////
Terrain::Terrain ()
: m_etages (  )
, m_indexEtageCourant ( 0 )
, m_taille (  )
, m_shaderGrille (  )
, m_shaderHachures (  )
, m_shaderOmbre (  )
, m_shaderAO (  )
, m_couleurSol (  )
, m_couleurTerre (  )
, m_couleurOmbres (  )
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

