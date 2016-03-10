#include "voronoigenerator.h"
#include <ctime>
#include <cstdlib>

#include <QDebug>

#define DRAND(min, max) (min) + ((double)std::rand() / RAND_MAX) * ((max) - (min))

VoronoiGenerator::VoronoiGenerator() :
    _cellNumber(0),
    _xMax(0),
    _yMax(0),
    _sites(),
    _corners(),
    _edges(),
    _events(),
    _sweepLine(0),
    _rootParabola(NULL)
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
        s->point.x = DRAND(0, _xMax);
        s->point.y = DRAND(0, _yMax);
        _sites.push_back(s);

        QedEvent *e = new QedEvent(s->point.x, QedEvent::POINT);
        e->site = s,
        _events.insert(std::pair<int, QedEvent *> (e->x, e));
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
        QedEvent *event = popNextEvent();
        _sweepLine = event->x;

        qDebug() << event->x;

        if (event->type == QedEvent::POINT)
            addParabola(event->site);
        else
            removeParabloa(event);
    }

    LloydRelaxation();
}

void    VoronoiGenerator::LloydRelaxation()
{

}

void    VoronoiGenerator::addParabola(Site *s)
{
    if (!_rootParabola)
    {
        _rootParabola = new Parabola(s);
        return;
    }

}

void    VoronoiGenerator::removeParabloa(QedEvent *e)
{
    // remove parabola
    // check new circles events
}

QedEvent    *VoronoiGenerator::popNextEvent()
{
    std::map<int, QedEvent*>::iterator it = _events.begin();
    QedEvent    *s = (*it).second;
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

    for (std::multimap<int, QedEvent *>::iterator it = _events.begin();
         it != _events.end(); ++it)
        delete (*it).second;

    _sites.clear();
    _corners.clear();
    _edges.clear();
    _events.clear();

    Site::indexMax = 0;
    Corner::indexMax = 0;
    CrossedEdge::indexMax = 0;
}
