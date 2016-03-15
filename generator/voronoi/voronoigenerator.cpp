#include "voronoigenerator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>

#include "parabola.h"
#include "edge.h"

#define DRAND(min, max) (min) + ((double)std::rand() / RAND_MAX) * ((max) - (min))

namespace VOR
{

VoronoiGenerator::VoronoiGenerator() :
    _tempEdges(),
    _events(),
    _deleted(),
    _sweepLine(0),
    _root(NULL)
{
}

VoronoiGenerator::~VoronoiGenerator()
{
}

void    VoronoiGenerator::run()
{
    _root = NULL;
    Parabola::indexMax = 0;


    //generateRandomSites();
    generateTestSites();

    fortuneAlgo();
    LloydRelaxation(); // en gros equilibrer les point et relancer fortune

    std::cout << "Done" << std::endl;
}

void    VoronoiGenerator::generateRandomSites()
{
    for (unsigned int i = 0; i < _zoneNumber; ++i)
    {
        // mettre la gestion des sites;
        Event *e = new Event(Point(DRAND(0, _xMax), DRAND(0, _yMax)), Event::POINT);
        _events.push(e);
    }
}

void    VoronoiGenerator::generateTestSites()
{
    Event    *e;

    e = new Event(Point(100, 50), Event::POINT);
    _events.push(e);

    e = new Event(Point(30, 80), Event::POINT);
    _events.push(e);

    e = new Event(Point(200, 100), Event::POINT);
    _events.push(e);

    e = new Event(Point(120, 150), Event::POINT);
    _events.push(e);

    e = new Event(Point(250, 200), Event::POINT);
    _events.push(e);

    e = new Event(Point(50, 300), Event::POINT);
    _events.push(e);

    e = new Event(Point(400, 300), Event::POINT);
    _events.push(e);

    e = new Event(Point(230, 400), Event::POINT);
    _events.push(e);
}

void    VoronoiGenerator::fortuneAlgo()
{
    while (!_events.empty())
    {
        Event *event = _events.top();
        _events.pop();

        _sweepLine = event->y;

        if(_deleted.find(event) != _deleted.end())
        {
            delete(event);
            _deleted.erase(event);
            continue;
        }

        std::cout << std::endl << "<event type : " << event->type << "; y = " << event->y << ">" << std::endl;
        if (event->type == Event::POINT)
            addParabola(event->point);
        else
            removeParabola(event);
    }

    finishEdge(_root);
    for(std::vector<Edge *>::iterator it = _tempEdges.begin(); it != _tempEdges.end(); ++it)
    {
        if( (*it)->neighbour)
        {
            (*it)->start = (*it)->neighbour->end;
            delete (*it)->neighbour;
        }
    }
}

void    VoronoiGenerator::LloydRelaxation()
{

}

void	VoronoiGenerator::finishEdge(Parabola * p)
{
    if(p->isLeaf) {delete p; return;}
    double mx;
    if(p->edge->direction.x > 0.0)
        mx = std::max(_xMax, p->edge->start.x + 10 );
    else
        mx = std::min(0.0, p->edge->start.x - 10);

    p->edge->end.x = mx;
    p->edge->end.y = mx * p->edge->f + p->edge->g;

    finishEdge(p->left());
    finishEdge(p->right());
    delete p;
}


void    VoronoiGenerator::addParabola(const Point &site)
{
    std::cout << "<===== addParabola(" << site << ") =====>" << std::endl << std::endl;
    if (!_root) { _root = new Parabola(site); return; }

    // Still not sure
    /*if (_root->isLeaf && _root->site->point.y - site->point.y < 1) // why second condition ?
    {
        _root->isLeaf = false;
        _root->setLeft(new Parabola(_root->site));
        _root->setRight(new Parabola(site));

        if (site->point.x  > _root->site->point.x)
            _root->edge = createEdge(_root->site, site);
        else
            _root->edge = createEdge(site, _root->site);

        // Add midpoint

        return;
    }*/

    Parabola    *topParabola = getParabolaAtX(site.x); // get first parabola above the new site
    if (topParabola->cEvent) // Event annulé car bouffé par une nouvelle parabole
    {
        _deleted.insert(topParabola->cEvent);
        topParabola->cEvent = NULL;
    }

    Point   start(0, 0);
    start.x = site.x;
    start.y = getY(topParabola->site, site.x);

    Edge    *el = new Edge(start, topParabola->site, site);
    Edge    *er = new Edge(start, site, topParabola->site);
    el->neighbour = er;
    _tempEdges.push_back(el);
    topParabola->edge = er;
    topParabola->isLeaf = false;

    Parabola    *p0 = new Parabola(topParabola->site); // Gauche
    Parabola    *p1 = new Parabola(site);              // Nouvelle, celle qui coupe
    Parabola    *p2 = new Parabola(topParabola->site); // Droite

    topParabola->setRight(p2);
    topParabola->setLeft(new Parabola());
    topParabola->left()->edge = el;
    topParabola->left()->setLeft(p0);
    topParabola->left()->setRight(p1);

    checkCircle(p0);
    checkCircle(p2);

}

void    VoronoiGenerator::removeParabola(Event *e)
{
    std::cout << "<===== removeParabola(" << *e->arch << ") =====>" << std::endl << std::endl;
    Parabola    *p1 = e->arch;

    Parabola    *pLeft = Parabola::getLeftParent(p1);
    Parabola    *pRight = Parabola::getRightParent(p1);
    Parabola    *p0 = Parabola::getLeftChild(pLeft);
    Parabola    *p2 = Parabola::getRightChild(pRight);

    if (p0 == p2)
        std::cout << "error : same focal point\n";

    if (p0->cEvent)
    {
        _deleted.insert(p0->cEvent);
        p0->cEvent = NULL;
    }
    if (p2->cEvent)
    {
        _deleted.insert(p2->cEvent);
        p2->cEvent = NULL;
    }

    Point   p(0, 0);
    p.x = e->point.x;
    p.y = getY(p1->site, e->point.x);

    pLeft->edge->end.x = p.x;
    pLeft->edge->end.y = p.y;
    pRight->edge->end.x = p.x;
    pRight->edge->end.y = p.y;

    std::cout << "pLeft : " << *pLeft << "pRight" << *pRight << std::endl;

    Parabola * higher;
    Parabola * par = p1;
    while(par != _root)
    {
        par = par->parent;
        std::cout << *par << std::endl;
        if(par == pLeft) higher = pLeft;
        if(par == pRight) higher = pRight;
    }

    higher->edge = new Edge(p, p0->site, p2->site);
    _tempEdges.push_back(higher->edge);

    Parabola * gparent = p1->parent->parent;
    if(p1->parent->left() == p1)
    {
        if(gparent->left()  == p1->parent) gparent->setLeft ( p1->parent->right() );
        if(gparent->right() == p1->parent) gparent->setRight( p1->parent->right() );
    }
    else
    {
        if(gparent->left()  == p1->parent) gparent->setLeft ( p1->parent->left()  );
        if(gparent->right() == p1->parent) gparent->setRight( p1->parent->left()  );
    }

    delete p1->parent;
    delete p1;

    std::cout << " gp final : " << *gparent << " gp left : " << *gparent->left() << " gp right : " << *gparent->right() << std::endl;
    checkCircle(p0);
    checkCircle(p2);
}

double      VoronoiGenerator::getXofEdge(Parabola *p, double y)
{
    const Point &sLeft = Parabola::getLeftChild(p)->site;
    const Point &sRight = Parabola::getRightChild(p)->site;

    std::cout << "<- getXofEdge(" << *p << ", " << y << ") ->" << std::endl;
    std::cout << "fils gauche : " << *Parabola::getLeftChild(p) << "; fils droite : " << *Parabola::getRightChild(p) << std::endl;
    std::cout << "site fils gauche : " << sLeft << "; site fils droite : " << sRight << std::endl;

    // justifier
    double dp;

    // 1 = parabole gauche ; 2 = parabole droite ; vide = intersection
    // ax² + bx + c
    double a, a1, a2, b, b1, b2, c, c1, c2;

    // b² - 4ac, resolution d'equation du second defrée
    double   delta, x1, x2;

    double result;

    // REVERIFIER
    dp = 2.0 * (sLeft.y - y);
    a1 = 1.0 / dp;
    b1 = -2.0 * sLeft.x / dp;
    c1 = y + dp / 4 + sLeft.x * sLeft.x / dp;

    dp = 2.0 * (sRight.y - y);
    a2 = 1.0 / dp;
    b2 = -2.0 * sRight.x / dp;
    c2 = _sweepLine + dp / 4 + sRight.x * sRight.x / dp; // why _sweepline ?

    a = a1 - a2;
    b = b1 - b2;
    c = c1 - c2;

    delta = b*b - 4 * a * c;
    x1 = (-b + sqrt(delta)) / (2*a);
    x2 = (-b - sqrt(delta)) / (2*a);

    if(sLeft.y < sRight.y)
        result = std::max(x1, x2);
    else
        result = std::min(x1, x2);

    std::cout << "x1 : " << x1 << "; x2 : " << x2 << "; result : " << result << std::endl;
    return result;
}

Parabola    *VoronoiGenerator::getParabolaAtX(double nx)
{
    std::cout << "<--- getParabolaAtX(" << nx << ") --->" << std::endl;
    Parabola *p = _root;
    double x = 0.0;

    while(!p->isLeaf)
    {
        x = getXofEdge(p, _sweepLine);
        if (x > nx)
            p = p->left();
        else
            p = p->right();
    }
    std::cout << "parabola founded = " << *p << std::endl;
    return p;
}

double      VoronoiGenerator::getY(const Point &s, double x)
{
    // Formule d'intersection, à reviser
    double dp = 2 * (s.y - _sweepLine);
    double a1 = 1 / dp;
    double b1 = -2 * s.x / dp;
    double c1 = _sweepLine + dp / 4 + s.x * s.x / dp;

    double result = a1*x*x + b1*x + c1;

    std::cout << "<- getY(" << s << ", " << x << ") : " << result << " ->" << std::endl;
    return(result);
}

void        VoronoiGenerator::checkCircle(Parabola *b)
{
    std::cout << std::endl << "<--- checkCircle(" << *b << ") --->" << std::endl;
    Parabola    *leftParent = Parabola::getLeftParent(b);
    Parabola    *rightParent = Parabola::getRightParent(b);

    Parabola    *a = Parabola::getLeftChild(leftParent);
    Parabola    *c = Parabola::getRightChild(rightParent);

    std::cout << "leftParent : ";
    if (leftParent) std::cout << *leftParent;
    else std::cout << "Nan";
    std::cout << "; rightParent : ";
    if (rightParent) std::cout << *rightParent;
    else std::cout << "Nan";
    std::cout << std::endl << "leftChild site : ";
    if (a) std::cout << a->site;
    else std::cout << "Nan";
    std::cout << "; rightChild site : ";
    if (c) std::cout << c->site;
    else std::cout << "Nan";
    std::cout << std::endl;

    if (!a || !c || a->site == c->site)
        return;

    Point s(0, 0);
    if (!getEdgeIntersection(leftParent->edge, rightParent->edge, s))
        return;

    // REVOIR
    /*double dx = a->site->point.x - s->x;
    double dy = a->site->point.y - s->y;

    double d = sqrt( (dx * dx) + (dy * dy) );

    if(s->y - d >= _sweepLine) { return;}*/

    Event * e = new Event(s/* - d*/, Event::INTERSECTION);
    b->cEvent = e;
    e->arch = b;

    std::cout << "Added a circle event at y = " << e->y << std::endl;
    _events.push(e);
}

bool VoronoiGenerator::getEdgeIntersection(Edge *a, Edge *b, Point &result)
{
    std::cout << "<- getEdgeIntersection(" << *a << ", " << *b << ") ->" << std::endl;

    double x = (b->g - a->g) / (a->f - b->f);
    double y = a->f * x + a->g;

    if((x - a->start.x)/a->direction.x < 0) return false;
    if((y - a->start.y)/a->direction.y < 0) return false;
    if((x - b->start.x)/b->direction.x < 0) return false;
    if((y - b->start.y)/b->direction.y < 0) return false;

    std::cout << "result : " << x << "; " << y << std::endl;
    result.x = x;
    result.y = y;
    return true;
}

}
