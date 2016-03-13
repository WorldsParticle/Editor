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

        std::cout << *s;

        QedEvent *e = new QedEvent(s->point.y, QedEvent::POINT);
        e->site = s,
                _events.insert(std::pair<double, QedEvent *> (e->y, e));
    }
    std::cout << std::endl;
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

        std::cout << "=====\nevent type : " << event->type << "; y = " << event->y << std::endl;

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
    std::cout << "---\naddParabola(" << *site << std::endl;
    if (!_root)
    {
        _root = new Parabola(site);
        return;
    }

    // Apparently it is a degenerate event. will make it if trouble
    /*
    if (_root->isLeaf && _root->site->point.y - site->point.y < 1)
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
        _root->corner = e;
        _edges.push_back(e);
        return;
    }*/

    Parabola    *topParabola = getParabolaByX(site->point.x); // get first parabola above the new site
    if (topParabola->cEvent) // Event annulé car bouffé par une nouvelle parabole
    {
        //_events.erase(_events.find(topParabola->cEvent));
        //topParabola->cEvent = NULL;
    }

    CrossedEdge  *edge = new CrossedEdge();
    edge->d0 = topParabola->site;
    edge->d1 = site;
    // temporarely use the edge midpoint until the edge is formed
    edge->midpoint.x = site->point.x;
    edge->midpoint.y = getY(topParabola->site, site->point.x);
    _edges.push_back(edge);
    topParabola->edge = edge;
    topParabola->isLeaf = false;

    Parabola    *p0 = new Parabola(topParabola->site); // Gauche
    Parabola    *p1 = new Parabola(site);              // Nouvelle, celle qui coupe
    Parabola    *p2 = new Parabola(topParabola->site); // Droite

    topParabola->setRight(p2);
    topParabola->setLeft(new Parabola());
    topParabola->left()->edge = edge;
    topParabola->left()->setLeft(p0);
    topParabola->left()->setRight(p1);

    checkCircle(p0);
    checkCircle(p2);

}

void    VoronoiGenerator::removeParabola(QedEvent *e)
{
    std::cout << "---\nRemoving parabola\n";
    Parabola    *p1 = e->arch;

    Parabola    *pLeft = Parabola::getLeftParent(p1);
    Parabola    *pRight = Parabola::getRightParent(p1);
    Parabola    *p0 = Parabola::getLeftChild(pLeft);
    Parabola    *p2 = Parabola::getRightChild(pRight);

    if (p0 == p2)
        std::cout << "error : same focal point\n";

    if (p0->cEvent)
        ; // delete
    if (p2->cEvent)
        ; // delete

    Corner  *corner = new Corner();
    _corners.push_back(corner);

    corner->point.x = e->arch->site->point.x;           // à revoir
    corner->point.y = getY(p1->site, e->site->point.x); // à revoir
    pLeft->edge->v1 = corner;
    pRight->edge->v0 = corner;

    // TOUT CE QUI SUIT EST DU CTRL V, REFAIRE !!!!
    Parabola * higher;
    Parabola * par = p1;
    while(par != _root)
    {
        par = par->parent;
        if(par == pLeft) higher = pLeft;
        if(par == pRight) higher = pRight;
    }
    higher->edge = new CrossedEdge(/*p, p0->site, p2->site*/);
    higher->edge->d0 = p0->site;
    higher->edge->d1 = p2->site;
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

double      VoronoiGenerator::getXofEdge(CrossedEdge *edge, double y)
{
    std::cout << "-\ngetXofEdge(" << *edge << ", " << y << ")" << std::endl;

    Site        *sLeft = edge->d0;
    Site        *sRight = edge->d1;

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
    std::cout << "---\ngetParabolaByX(" << nx << ")" << std::endl;
    Parabola *p = _root;
    double x = 0.0;

    while(!p->isLeaf)
    {
        x = getXofEdge(p->edge, _sweepLine);
        if (x > nx)
            p = p->left();
        else
            p = p->right();
    }
    std::cout << "parabola founded = " << *p << std::endl;
    return p;
}

double      VoronoiGenerator::getY(Site *s, double x)
{
    double dp = 2 * (s->point.y - _sweepLine);
    double a1 = 1 / dp;
    double b1 = -2 * s->point.x / dp;
    double c1 = _sweepLine + dp / 4 + s->point.x * s->point.x / dp;

    double result = a1*x*x + b1*x + c1;

    std::cout << "-\ngetY(" << *s << ", " << x << ") => " << result << std::endl;
    return(result);
}

void        VoronoiGenerator::checkCircle(Parabola *b)
{
    std::cout << "---\ncheckCircle with par.site : " << *(b->site) << std::endl;
    std::cout << "leftChild : " << b->left() << "; rightChild : " << b->right() << std::endl;
    Parabola    *leftParent = Parabola::getLeftParent(b);
    Parabola    *rightParent = Parabola::getLeftParent(b);

    Parabola    *a = Parabola::getLeftChild(b);
    Parabola    *c = Parabola::getRightChild(b);

    if (!a || !c || a->site == c->site)
        return;

    Point * s = 0;
    s = getEdgeIntersection(leftParent->edge, rightParent->edge);
    if(!s)
        return;

    double dx = a->site->point.x - s->x;
    double dy = a->site->point.y - s->y;

    double d = sqrt( (dx * dx) + (dy * dy) );

    if(s->y - d >= _sweepLine) { return;}

    QedEvent * e = new QedEvent(s->y - d, QedEvent::INTERSECTION);
    b->cEvent = e;
    e->arch = b;
    _events.insert(std::pair<double, QedEvent *>(e->y, e));

}

Point       *VoronoiGenerator::getEdgeIntersection(CrossedEdge *a, CrossedEdge *b)
{
    // d0 = top = left; d1 = bot = right
    // f* | g* = coeff directeur de la droite contenant l'edge (y = f*x + g)
    // a refaire absolument

    double fa = (a->d1->point.x - a->d0->point.x) /
            (a->d1->point.y - a->d0->point.y);
    double fb = (b->d1->point.x - b->d0->point.x) /
            (b->d1->point.y - b->d0->point.y);

    double ga = a->midpoint.y - fa * a->midpoint.x;
    double gb = b->midpoint.y - fb * b->midpoint.x;

    double dax = a->d1->point.y - a->d0->point.y;
    double dbx = b->d1->point.y - b->d0->point.y;
    double day = -(a->d1->point.x - a->d0->point.x);
    double dby = -(b->d1->point.y - b->d0->point.y);

    double x = (gb-ga) / (fa - fb);
    double y = fa * x + ga;

    if((x - a->midpoint.x)/dax < 0) return 0;
    if((y - a->midpoint.y)/day < 0) return 0;

    if((x - b->midpoint.x)/dbx < 0) return 0;
    if((y - b->midpoint.y)/dby < 0) return 0;

    return new Point(x, y);
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
