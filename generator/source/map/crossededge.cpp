#include "map/crossededge.hpp"

namespace MAP
{

int CrossedEdge::indexMax = 0;
CrossedEdge::CrossedEdge() :
    index(indexMax),
    z0(NULL),
    z1(NULL),
    c0(NULL),
    c1(NULL),
    midpoint(0, 0)
{
    ++indexMax;
}

}
