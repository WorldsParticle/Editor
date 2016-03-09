#include "graph.h"

int Face::_indexMax = 0;
Face::Face() :
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

int DoubleEdge::_indexMax = 0;
DoubleEdge::DoubleEdge() :
    _index(_indexMax)
{
    ++_indexMax;
}
