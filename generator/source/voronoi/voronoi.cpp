#include "include/voronoi/voronoi.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>

#include "include/map/map.hpp"

#include "include/voronoi/parabola.hpp"
#include "include/voronoi/edge.hpp"

#define DRAND(min, max) (min) + ((double)std::rand() / RAND_MAX) * ((max) - (min))

namespace VOR
{

Voronoi::Voronoi() :
    _sites(),
    _edges(),
    _points(),
    _events(),
    _deleted(),
    _sweepLine(0),
    _root(NULL)
{
    _step = FILL;
}

Voronoi::~Voronoi()
{
}

void    Voronoi::run()
{
    generateRandomSites();

    std::cout << "Generating Voronoi edges .." << std::endl;
    fortuneAlgo();
    std::cout << "Done !" << std::endl;

    /*
    LloydRelaxation();
    fortuneAlgo();*/

    std::cout << "Translating into dual graph .." << std::endl;
    computeFinalMap();
    std::cout << "Done !" << std::endl;

}

void    Voronoi::clearData()
{
    for(std::vector<Point *>::iterator it = _points.begin(); it != _points.end(); ++it)
        delete (*it);
    for(std::vector<Edge *>::iterator it = _edges.begin(); it != _edges.end(); ++it)
        delete (*it);
    _points.clear();
    _edges.clear();

    _root = NULL;
    Parabola::indexMax = 0;
}

void    Voronoi::generateRandomSites()
{
    for(std::vector<Point *>::iterator it = _sites.begin(); it != _sites.end(); ++it)
        delete (*it);
    _sites.clear();

    for (unsigned int i = 0; i < _map->zoneNumber(); ++i)
        _sites.push_back(new Point(DRAND(0, _map->xMax()), DRAND(0, _map->yMax())));
}

void    Voronoi::fortuneAlgo()
{
    clearData();

    for (std::vector<Point *>::iterator it = _sites.begin(); it != _sites.end(); ++it)
        _events.push(new Event(*it, true));

    while (!_events.empty())
    {
        Event *event = _events.top();
        _events.pop();

        _sweepLine = event->point->y;

        if(_deleted.find(event) != _deleted.end())
        {
            delete(event);
            _deleted.erase(event);
            continue;
        }

        if (event->is_par_event)
            addParabola(event->point);
        else
            removeParabola(event);
    }

    finishEdge(_root);

    for(std::vector<Edge *>::iterator it = _edges.begin(); it != _edges.end(); ++it)
    {
        if( (*it)->neighbour)
        {
            (*it)->start = (*it)->neighbour->end;
            delete (*it)->neighbour;
        }
    }
}

void    Voronoi::LloydRelaxation() // NOT WORKING FOR NOW
{
    // filling neighbors temporarly.. ugly for now. will have to remove totally Zone from this algorythme
    /*for (const auto &e: _edges)
    {
        if (!e->left->haveNeighbor(e->right))
            e->left->neighbors.push_back(e->right);
        if (!e->right->haveNeighbor(e->left))
            e->right->neighbors.push_back(e->left);
    }

    for (const auto &z: _points)
    {
        z->point.x = 0;
        z->point.y = 0;
        for (const auto &n: z->neighbors)
        {
            z->point.x += n->point.x;
            z->point.y += n->point.y;
        }
        z->point.x /= z->neighbors.size();
        z->point.y /= z->neighbors.size();
        z->neighbors.clear();
        _events.push(new Event(z));
    }*/
}

void	Voronoi::finishEdge(Parabola * p)
{
    if(p->isLeaf) {delete p; return;}

    double mx;
    if(p->edge->direction->x > 0.0)
        mx = std::max(_map->xMax(), p->edge->start->x + 10 );
    else
        mx = std::min(0.0, p->edge->start->x - 10);

    p->edge->end = new Point(mx, mx * p->edge->f + p->edge->g);
    _points.push_back(p->edge->end);

    finishEdge(p->left());
    finishEdge(p->right());
    delete p;
}

void        Voronoi::computeFinalMap()// TOOOOODOOOOOOO
{
    for (const auto &e: _edges)
    {
        MAP::CrossedEdge    *edge = new MAP::CrossedEdge();
        MAP::Zone   *left = _map->findZone(e->left);
        MAP::Zone   *right = _map->findZone(e->right);
        MAP::Corner *c0;
        MAP::Corner *c1;

        // Ugly workaround
        if (!left)
        {
            left = new MAP::Zone(e->left->x, e->left->y);
            _map->zones().insert(std::pair<int, MAP::Zone *>(left->index, left));
        }
        if (!right)
        {
            right = new MAP::Zone(e->right->x, e->right->y);
            _map->zones().insert(std::pair<int, MAP::Zone *>(right->index, right));
        }

        if (!left->haveNeighbor(right))
            left->neighbors.push_back(right);
        if (!right->haveNeighbor(left))
            right->neighbors.push_back(left);

        edge->z0 = left;
        edge->z1 = right;
        left->borders.push_back(edge);
        right->borders.push_back(edge);

        if (!(c0 = checkCorner(left, *e->start)))
        {
            if (!(c0 = checkCorner(right, *e->start)))
            {
                c0 = new MAP::Corner();
                _map->corners().insert(std::pair<int, MAP::Corner *>(c0->index, c0));

                c0->point.x = e->start->x;
                c0->point.y = e->start->y;
                right->corners.push_back(c0);
                c0->faces.push_back(right);
            }
            left->corners.push_back(c0);
            c0->faces.push_back(left);
        }

        if (!(c1 = checkCorner(left, *e->end)))
        {
            if (!(c1 = checkCorner(right, *e->end)))
            {
                c1 = new MAP::Corner();
                _map->corners().insert(std::pair<int, MAP::Corner *>(c1->index, c1));

                c1->point.x = e->end->x;
                c1->point.y = e->end->y;
                right->corners.push_back(c1);
                c1->faces.push_back(right);
            }
            left->corners.push_back(c1);
            c1->faces.push_back(left);
        }


        edge->c0 = c0;
        edge->c1 = c1;
        c0->edges.push_back(edge);
        c1->edges.push_back(edge);
        c0->adjacent.push_back(c1);
        c1->adjacent.push_back(c0);

        _map->edges().insert(std::pair<int, MAP::CrossedEdge *>(edge->index, edge));
    }
}

MAP::Corner *Voronoi::checkCorner(MAP::Zone *z, Point &p)
{
    for (std::vector<MAP::Corner *>::iterator it = z->corners.begin(); it != z->corners.end(); ++it)
        if ((*it)->point.x == p.x && (*it)->point.y == p.y)
            return (*it);
    return NULL;
}


void    Voronoi::addParabola(Point *site)
{
    if (!_root) { _root = new Parabola(site); return; }

    // Nop
    /*if (_root->isLeaf && _root->site->point.y - site->point.y < 1)
    {
        _root->isLeaf = false;
        _root->setLeft(new Parabola(_root->site));
        _root->setRight(new Parabola(site));
        Point   s((site->point.x + _root->site->point.x) / 2, _yMax);

        if (site->point.x  > _root->site->point.x)
            _root->edge = new Edge(s, _root->site, site);
        else
            _root->edge = new Edge(s, site, _root->site);

        _tempEdges.push_back(_root->edge);

        return;
    }*/

    Parabola    *topParabola = getParabolaAtX(site->x); // get first parabola above the new site
    if (topParabola->cEvent) // Event annulé car bouffé par une nouvelle parabole
    {
        _deleted.insert(topParabola->cEvent);
        topParabola->cEvent = NULL;
    }

    Point   *start = new Point(site->x, getY(topParabola->site, site->x));
    _points.push_back(start);

    Edge    *el = new Edge(start, topParabola->site, site);
    Edge    *er = new Edge(start, site, topParabola->site);
    el->neighbour = er;
    _edges.push_back(el);
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

void    Voronoi::removeParabola(Event *e)
{
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

    Point   *p = new Point(e->point->x, getY(p1->site, e->point->x));
    _points.push_back(p);

    pLeft->edge->end = p;
    pRight->edge->end = p;

    Parabola * higher;
    Parabola * par = p1;
    while(par != _root)
    {
        par = par->parent;
        if(par == pLeft) higher = pLeft;
        if(par == pRight) higher = pRight;
    }

    higher->edge = new Edge(p, p0->site, p2->site);
    _edges.push_back(higher->edge);

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

    checkCircle(p0);
    checkCircle(p2);
}

double      Voronoi::getXofEdge(Parabola *p, double y)
{
    const Point *sLeft = Parabola::getLeftChild(p)->site;
    const Point *sRight = Parabola::getRightChild(p)->site;

    // justifier
    double dp;

    // 1 = parabole gauche ; 2 = parabole droite ; vide = intersection
    // ax² + bx + c
    double a, a1, a2, b, b1, b2, c, c1, c2;

    // b² - 4ac, resolution d'equation du second defrée
    double   delta, x1, x2;

    double result;

    // REVERIFIER
    dp = 2.0 * (sLeft->y - y);
    a1 = 1.0 / dp;
    b1 = -2.0 * sLeft->x / dp;
    c1 = y + dp / 4 + sLeft->x * sLeft->x / dp;

    dp = 2.0 * (sRight->y - y);
    a2 = 1.0 / dp;
    b2 = -2.0 * sRight->x / dp;
    c2 = _sweepLine + dp / 4 + sRight->x * sRight->x / dp; // why _sweepline ?

    a = a1 - a2;
    b = b1 - b2;
    c = c1 - c2;

    delta = b*b - 4 * a * c;
    x1 = (-b + sqrt(delta)) / (2*a);
    x2 = (-b - sqrt(delta)) / (2*a);

    if(sLeft->y < sRight->y)
        result = std::max(x1, x2);
    else
        result = std::min(x1, x2);

    return result;
}

Parabola    *Voronoi::getParabolaAtX(double nx)
{
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
    return p;
}

double      Voronoi::getY(const Point *s, double x)
{
    // Formule d'intersection, à reviser
    double dp = 2 * (s->y - _sweepLine);
    double a1 = 1 / dp;
    double b1 = -2 * s->x / dp;
    double c1 = _sweepLine + dp / 4 + s->x * s->x / dp;

    double result = a1*x*x + b1*x + c1;

    return(result);
}

void        Voronoi::checkCircle(Parabola *b)
{
    Parabola    *leftParent = Parabola::getLeftParent(b);
    Parabola    *rightParent = Parabola::getRightParent(b);

    Parabola    *a = Parabola::getLeftChild(leftParent);
    Parabola    *c = Parabola::getRightChild(rightParent);

    if (!a || !c || a->site == c->site)
        return;

    Point *s = NULL;
    if (!(s = getEdgeIntersection(leftParent->edge, rightParent->edge)))
        return;

    // Trouver la future distance de la sweepline quand intersection
    double dx = a->site->x - s->x;
    double dy = a->site->y - s->y;
    double d = sqrt( (dx * dx) + (dy * dy) );
    if(s->y - d >= _sweepLine)
        return;

    Event *e = new Event(new Point(s->x, s->y - d), false);
    _points.push_back(e->point);
    b->cEvent = e;
    e->arch = b;

    _events.push(e);
}

Point   *Voronoi::getEdgeIntersection(Edge *a, Edge *b)
{
    double x = (b->g - a->g) / (a->f - b->f);
    double y = a->f * x + a->g;

    if((x - a->start->x)/a->direction->x < 0) return NULL;
    if((y - a->start->y)/a->direction->y < 0) return NULL;
    if((x - b->start->x)/b->direction->x < 0) return NULL;
    if((y - b->start->y)/b->direction->y < 0) return NULL;

    Point   *result = new Point(x, y);
    _points.push_back(result);
    return result;
}

}
