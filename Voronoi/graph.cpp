#include "graph.h"

int Site::indexMax = 0;
Site::Site(double x, double y) :
    index(indexMax),
    point(x, y),
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
    midpoint(0, 0),
    d0(NULL),
    d1(NULL),
    v0(NULL),
    v1(NULL)
{
    ++indexMax;
}
