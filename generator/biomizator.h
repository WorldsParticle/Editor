#ifndef BIOMIZATOR_H
#define BIOMIZATOR_H

#include "generator.h"
#include "map/map.h"

namespace BIO {

///
/// \brief The Biomizator class, transforming dirt into Mona Lisa
/// Based on the design found in https://github.com/amitp/mapgen2
///
class Biomizator : public GEN::GenerationStep
{
public:
    Biomizator();
    ~Biomizator();

    virtual void run();

    MAP::Biome      getBiome(MAP::Zone * z);
    void            assignBiomes();

private:

};

}

#endif // BIOMIZATOR_H
