#include "graph.h"

int Site::indexMax = 0;
Site::Site() :
    index(indexMax),
    neighbors(),
    borders(),
    corners()
{
    ++indexMax;
}

int Corner::_indexMax = 0;
Corner::Corner() :
    _index(_indexMax)
{
    ++_indexMax;
}

int CrossedEdge::indexMax = 0;
CrossedEdge::CrossedEdge() :
    index(indexMax)
{
    ++indexMax;
}
