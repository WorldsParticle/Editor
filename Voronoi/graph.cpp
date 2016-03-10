#include "graph.h"

int Site::indexMax = 0;
Site::Site() :
    index(indexMax),
    point(0, 0),
    neighbors(),
    borders(),
    corners()
{
    ++indexMax;
}

int Corner::indexMax = 0;
Corner::Corner() :
    index(indexMax),
    point(0, 0)
{
    ++indexMax;
}

int CrossedEdge::indexMax = 0;
CrossedEdge::CrossedEdge() :
    index(indexMax),
    midpoint(0, 0)
{
    ++indexMax;
}
