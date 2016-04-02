#ifndef RIVEROR_H
#define RIVEROR_H

#include "generator.hpp"
#include "map/map.hpp"

namespace RIV {

///
/// \brief The Riveror class, daughter of rain and mother of rivers and watersheds
/// Based on the design found in https://github.com/amitp/mapgen2
///
class Riveror : public GEN::GenerationStep
{
public:
    Riveror();
    ~Riveror();

    virtual void run();

private:
    void                createRivers();
    void                calculateWatersheds();
    MAP::CrossedEdge *  lookupEdgeFromCorner(MAP::Corner * from, MAP::Corner * to);

};

}

#endif // RIVEROR_H
