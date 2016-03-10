#include "voronoigenerator.h"
#include <ctime>
#include <cstdlib>

#include <QDebug>

QueuedEvent::QueuedEvent(Point p, Type t) :
    point(p),
    type(t)
{

}

VoronoiGenerator::VoronoiGenerator() :
    _cellNumber(0),
    _xMax(0),
    _yMax(0),
    _sites(),
    _corners(),
    _edges(),
    _events(),
    _sweepLine(0)
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

    generateRandomSites();
    fortuneAlgo();
}

void    VoronoiGenerator::generateRandomSites()
{
    for (int i = 0; i < _cellNumber; ++i)
    {
        Site    *s = new Site();
        s->point.first = std::rand() % _xMax + 1;
        s->point.second = std::rand() % _yMax + 1;
        _sites.push_back(s);

        _events.insert(std::pair<int, QueuedEvent *>
                       (s->point.first, new QueuedEvent(s->point)));
    }
}

void    VoronoiGenerator::fortuneAlgo()
{
    /*
    std::map<Point, Face *>   centerLookup;
    for (const auto &s : _sites)
        centerLookup[s->_point] = s;
    */


    while (!_events.empty())
    {
        QueuedEvent *event = popNextEvent();
        _sweepLine = event->point.first;

        qDebug() << event->point.first << "|" << event->point.second;

        if (event->type == QueuedEvent::POINT)
            addParabola(event->point);
        else
            removeParabloa(event);
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

void    VoronoiGenerator::removeParabloa(QueuedEvent *e)
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
    for (std::vector<Site *>::iterator it = _sites.begin();
         it != _sites.end(); ++it)
        delete (*it);

    for (std::vector<Corner *>::iterator it = _corners.begin();
         it != _corners.end(); ++it)
        delete (*it);

    for (std::vector<CrossedEdge *>::iterator it = _edges.begin();
         it != _edges.end(); ++it)
        delete (*it);

    for (std::multimap<int, QueuedEvent *>::iterator it = _events.begin();
         it != _events.end(); ++it)
        delete (*it).second;

    _sites.clear();
    _corners.clear();
    _edges.clear();
    _events.clear();

    Site::indexMax = 0;
    Corner::_indexMax = 0;
    CrossedEdge::indexMax = 0;
}
