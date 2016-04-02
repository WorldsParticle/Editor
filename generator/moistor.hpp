#ifndef MOISTOR_H
#define MOISTOR_H

#include "generator.hpp"

namespace MOI {

///
/// \brief The Moistor class, probably a male for being such an accurate moist hunter
/// Based on the design found in https://github.com/amitp/mapgen2
///
class Moistor : public GEN::GenerationStep
{
public:
    Moistor();
    ~Moistor();

    virtual void run();

    void    assignCornerMoisture();
    void    redistributeMoisture();
    void    assignPolygonMoisture();

private:

};

}

#endif // MOISTOR_H
