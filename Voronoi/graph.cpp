#include "graph.h"

int Center::_indexMax = 0;
Center::Center() :
    _index(_indexMax),
    _neighbors(),
    _borders(),
    _corners()
{
    ++_indexMax;
}

int Corner::_indexMax = 0;
Corner::Corner() :
    _index(_indexMax)
{
    ++_indexMax;
}

int Edge::_indexMax = 0;
Edge::Edge() :
    _index(_indexMax)
{
    ++_indexMax;
}
