#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "generator.hpp"

namespace ELE {

///
/// \brief The Elevator class, propelling floor to space like a rocketeer
/// Based on the design found in https://github.com/amitp/mapgen2
///
class Elevator : public GEN::GenerationStep
{
public:
    Elevator();
    ~Elevator();

    virtual void run();

private:

    void        assignCornerElevation();
    void        redistributeElevation();
    void        setPolygonElevation();
    void        calculateDownSlopes();

};

}

#endif // ELEVATOR_H
