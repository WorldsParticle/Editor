#include "voronoigenerator.h"
#include <ctime>
#include <cstdlib>

#include <QDebug>

QueuedEvent::QueuedEvent(Point p, Type t) :
    _point(p),
    _type(t)
{

}

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
    std::map<Point, Face *>   centerLookup;
    for (const auto &p : _points)
    {
        Face *c = new Face();
        c->_point = p;
        _centers.push_back(c);
        centerLookup[p] = c;

        _events.insert(std::pair<int, QueuedEvent *>
                       (p.first, new QueuedEvent(p)));
    }

    while (!_events.empty())
    {
        QueuedEvent    *site = popNextEvent();
        qDebug() << site->_point.first << "|" << site->_point.second;
        if (site->_type == QueuedEvent::POINT)
            addParabola(site->_point);
        else
            removeParabloa();
    }

    LloydRelaxation();
}

void    VoronoiGenerator::LloydRelaxation()
{

}

void    VoronoiGenerator::addParabola(Point p)
{
    // add parabola to beachline
    // check new circle (intersections) events
}

void    VoronoiGenerator::removeParabloa()
{
    // remove parabola
    // check new circles events
}

QueuedEvent    *VoronoiGenerator::popNextEvent()
{
    std::map<int, QueuedEvent*>::iterator it = _events.begin();
    QueuedEvent    *s = (*it).second;
    _events.erase(it);
    return s;
}

void    VoronoiGenerator::reset()
{
    for(std::vector<Face *>::iterator it = _centers.begin();
        it != _centers.end(); ++it)
        delete (*it);

    for(std::vector<Corner *>::iterator it = _corners.begin();
        it != _corners.end(); ++it)
        delete (*it);

    for(std::vector<CrossedEdge *>::iterator it = _edges.begin();
        it != _edges.end(); ++it)
        delete (*it);

    _points.clear();
    _centers.clear();
    _corners.clear();
    _edges.clear();

    Face::_indexMax = 0;
    Corner::_indexMax = 0;
    CrossedEdge::_indexMax = 0;
}
