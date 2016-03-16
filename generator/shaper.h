#ifndef SHAPER_H
#define SHAPER_H

#include "generator.h"

namespace SHA {

///
/// \brief The Shaper class, transforming dirt into Mona Lisa
/// Based on the design found in https://github.com/amitp/mapgen2
///
class Shaper : public GEN::GenerationStep
{
public:
    Shaper();
    ~Shaper();

    virtual void run();

private:

    void        assignCornerLandPerlin(int seed);
    void        assignOceanCostAndLand();
};

}

#endif // SHAPER_H
