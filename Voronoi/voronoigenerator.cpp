#include "voronoigenerator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>

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
    _root(NULL)
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

        QedEvent *e = new QedEvent(s->point.y, QedEvent::POINT);
        e->site = s,
                _events.insert(std::pair<double, QedEvent *> (e->y, e));
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
        _sweepLine = event->y;

        std::cout << event->y << std::endl;

        if (event->type == QedEvent::POINT)
            addParabola(event->site);
        else
            removeParabola(event);
    }

    LloydRelaxation();
}

void    VoronoiGenerator::LloydRelaxation()
{

}

void    VoronoiGenerator::addParabola(Site *site)
{
    if (!_root)
    {
        _root = new Parabola(site);
        return;
    }

    // cutting parabola ?
    if (_root->isLeaf && _root->site->point.y - site->point.y < 1) // why < 1 ?
    {
        // Creating an intersection
        Site    *rootsite = _root->site;
        _root->isLeaf = false;
        _root->setLeft(new Parabola(rootsite));
        _root->setRight(new Parabola(site));

        CrossedEdge *e = new CrossedEdge();
        if (site->point.x  > rootsite->point.x)
        { e->d0 = rootsite; e->d1 = site; } // not sure if i need to keep track of the direction yet
        else
        { e->d0 = site; e->d1 = rootsite; }
        _root->edge = e;
        _edges.push_back(e);
        return;
    }

    // non-cutting parabola ?

    Parabola    *p = getParabolaByX(site->point.x);
    //do things

}

void    VoronoiGenerator::removeParabola(QedEvent *e)
{
    Parabola    *p1 = e->arch;

    Parabola    *pLeft = Parabola::getLeftParent(p1);
    Parabola    *pRight = Parabola::getRightParent(p1);

    Parabola    *p0 = Parabola::getLeftChild(pLeft);
    Parabola    *p2 = Parabola::getRightChild(pRight);

    if (p0 == p2)
        std::cout << "erreur inconnue (je parle pas le russe / whatever)\n";

}

double      VoronoiGenerator::getXofEdge(Parabola *parabola, double y)
{
    Parabola    *pLeft = parabola->left();
    Parabola    *pRight = parabola->right();

    Site        *sLeft = pLeft->site;
    Site        *sRight = pRight->site;

    // périmetre, enfin je crois
    double per;

    // 1 = parabole gauche ; 2 = parabole droite ; vide = intersection
    // ax² + bx + c
    double a, a1, a2, b, b1, b2, c, c1, c2;

    // b² - 4ac, resolution d'equation du second defrée
    bool   delta, x1, x2;

    double result;

    per = 2.0 * (sLeft->point.y - y);
    a1 = 1.0 / per;
    b1 = -2.0 * sLeft->point.x / per;
    c1 = y + per / 4 + sLeft->point.x * sLeft->point.x / per;

    per = 2.0 * (sRight->point.y - y);
    a2 = 1.0 / per;
    b2 = -2.0 * sRight->point.y / per;
    c2 = _sweepLine + per / 4 + sRight->point.y * sRight->point.y / per;

    a = a1 - a2;
    b = b1 - b2;
    c = c1 - c2;

    delta = b*b - 4 * a * c;
    x1 = (-b + sqrt(delta)) / (2*a);
    x2 = (-b - sqrt(delta)) / (2*a);

    if(sLeft->point.y < sRight->point.y )
        result = std::max(x1, x2);
    else
        result = std::min(x1, x2);

    return result;
}

Parabola    *VoronoiGenerator::getParabolaByX(double nx)
{
    Parabola * p = _root;
    double x = 0.0;

    while(!p->isLeaf)
    {
        x = getXofEdge(p, _sweepLine);
        if (x > nx)
            p = p->left();
        else
            p = p->right();
    }
    return p;
}

QedEvent    *VoronoiGenerator::popNextEvent()
{
    std::map<double, QedEvent*>::iterator it = _events.begin();
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

    for (std::multimap<double, QedEvent *>::iterator it = _events.begin();
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
