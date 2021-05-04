/**
 * @file trackbase/TrkrClusterHitAssocv3.cc
 * @author D. McGlinchey
 * @date June 2018
 * @brief TrkrClusterHitAssoc implementation
 */

#include "TrkrClusterHitAssocv3.h"
#include "TrkrDefs.h"

#include <ostream>  // for operator<<, endl, basic_ostream, ostream, basic_o...

namespace
{
  TrkrClusterHitAssocv3::Map dummy_map;
}

//_________________________________________________________________________
void TrkrClusterHitAssocv3::Reset()
{ m_map.clear(); }

//_________________________________________________________________________
void TrkrClusterHitAssocv3::identify(std::ostream &os) const
{
  std::multimap<TrkrDefs::cluskey, TrkrDefs::hitkey>::const_iterator iter;
  os << "-----TrkrClusterHitAssocv3-----" << std::endl;
  os << "Number of associations: " << size() << std::endl;
  for( const auto& map_pair:m_map )
  {
    for( const auto& pair:map_pair.second )
    {
      os << "clus key " << pair.first << std::dec
        << " layer " << (unsigned int) TrkrDefs::getLayer(pair.first)
        << " hit key: " << pair.second << std::endl;
    }
  }
  os << "------------------------------" << std::endl;

  return;

}

//_________________________________________________________________________
void TrkrClusterHitAssocv3::addAssoc(TrkrDefs::cluskey ckey, unsigned int hidx)
{ 
  // get hitset key from cluster
  const TrkrDefs::hitsetkey hitsetkey = TrkrDefs::getHitSetKeyFromClusKey( ckey );
  
  // find relevant association map, create one if not found
  Map& clusterMap = m_map[hitsetkey];
  
  // insert association
  clusterMap.insert(std::make_pair(ckey, hidx));
}

//_________________________________________________________________________
TrkrClusterHitAssocv3::Map* TrkrClusterHitAssocv3::getClusterMap(TrkrDefs::hitsetkey hitsetkey)
{
  // find relevant association map, create one if not found, and return adress
  return &m_map[hitsetkey];
}

//_________________________________________________________________________
TrkrClusterHitAssocv3::ConstRange TrkrClusterHitAssocv3::getHits(TrkrDefs::cluskey ckey)
{
  // get hitset key from cluster
  const TrkrDefs::hitsetkey hitsetkey = TrkrDefs::getHitSetKeyFromClusKey( ckey );

  // find relevant association map, create one if not found
  const Map& clusterMap = m_map[hitsetkey];
  
  // return range matching cluster key
  return std::make_pair( clusterMap.lower_bound(ckey), clusterMap.upper_bound(ckey) );
}

//_________________________________________________________________________
unsigned int TrkrClusterHitAssocv3::size(void) const
{  
  unsigned int size = 0;
  for( const auto& map_pair:m_map )
  { size += map_pair.second.size(); }

  return size;
}
