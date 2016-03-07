#include "voronoigenerator.h"
#include <ctime>
#include <cstdlib>

#include <QDebug>

VoronoiGenerator::VoronoiGenerator() :
    _cellNumber(0),
    _xMax(0),
    _yMax(0),
    _points(),
    _centers(),
    _corners(),
    _edges(),
    _events()
{
}

VoronoiGenerator::~VoronoiGenerator()
{
    reset();
}

void    VoronoiGenerator::launch(int number, int xMax, int yMax)
{
    reset();

    _cellNumber = number;
    _xMax = xMax;
    _yMax = yMax;

    generateRandomPoints();
    fortuneAlgo();
}

void    VoronoiGenerator::generateRandomPoints()
{
    for (int i = 0; i < _cellNumber; ++i)
        _points.push_back(Point(std::rand() % _xMax + 1,
                          std::rand() % _yMax + 1));
}

void    VoronoiGenerator::fortuneAlgo()
{
    std::map<Point, Center *>   centerLookup;
    for (const auto &p : _points)
    {
        Center *c = new Center();
        c->_point = p;
        _centers.push_back(c);
        centerLookup[p] = c;
    }

    while (!_events.empty())
    {
        Event e = _events.front();
        // Handle event (two type)
        // add next events
        _events.pop_front();
    }
}

void    VoronoiGenerator::reset()
{
    for(std::vector<Center *>::iterator it = _centers.begin();
        it != _centers.end(); ++it)
        delete (*it);

    for(std::vector<Corner *>::iterator it = _corners.begin();
        it != _corners.end(); ++it)
        delete (*it);

    for(std::vector<Edge *>::iterator it = _edges.begin();
        it != _edges.end(); ++it)
        delete (*it);

    _points.clear();
    _centers.clear();
    _corners.clear();
    _edges.clear();

    Center::_indexMax = 0;
    Corner::_indexMax = 0;
    Edge::_indexMax = 0;
}
