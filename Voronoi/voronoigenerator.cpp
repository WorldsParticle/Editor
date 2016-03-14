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

    //generateRandomSites();
    generateTestSites();

    fortuneAlgo();

    std::cout << "FINISH" << std::endl;
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
        e->site = s;
        _events.insert(std::pair<double, QedEvent *> (e->y, e));
    }
    std::cout << std::endl;
}

void    VoronoiGenerator::generateTestSites()
{
    Site        *s;
    QedEvent    *e;

    s = new Site(100, 50);
    _sites.push_back(s);
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.insert(std::pair<double, QedEvent *> (e->y, e));

    s = new Site(200, 100);
    _sites.push_back(s);
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.insert(std::pair<double, QedEvent *> (e->y, e));

    s = new Site(120, 150);
    _sites.push_back(s);
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.insert(std::pair<double, QedEvent *> (e->y, e));

    s = new Site(180, 200);
    _sites.push_back(s);
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.insert(std::pair<double, QedEvent *> (e->y, e));

    s = new Site(50, 300);
    _sites.push_back(s);
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.insert(std::pair<double, QedEvent *> (e->y, e));

}

void    VoronoiGenerator::fortuneAlgo()
{
    while (!_events.empty())
    {
        QedEvent *event = popNextEvent();
        _sweepLine = event->y;

        std::cout << "===================\nevent type : " << event->type << "; y = " << event->y << std::endl;
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

void	VoronoiGenerator::finishEdges(Parabola * p)
{
    if(p->isLeaf) {delete p; return;}

    /*double mx;
    if(p->direction->x > 0.0)
        mx = std::max(width, p->edge->midpoint->x + 10);
    else
        mx = std::min(0.0, p->edge->midpoint->x - 10);

    VPoint * end = new VPoint(mx, mx * n->edge->f + n->edge->g);
    n->edge->end = end;
    points.push_back(end);*/

    finishEdges(p->left());
    finishEdges(p->right());
    delete p;
}


void    VoronoiGenerator::addParabola(Site *site)
{
    std::cout << "---\naddParabola(" << *site << std::endl;
    if (!_root)
    {
        _root = new Parabola(site);
        return;
    }

    // Still not sure
    if (_root->isLeaf && _root->site->point.y - site->point.y < 1) // why second condition ?
    {
        _root->isLeaf = false;
        _root->setLeft(new Parabola(_root->site));
        _root->setRight(new Parabola(site));

        if (site->point.x  > _root->site->point.x)
            _root->edge = createEdge(_root->site, site);
        else
            _root->edge = createEdge(site, _root->site);
        return;
    }

    Parabola    *topParabola = getParabolaByX(site->point.x); // get first parabola above the new site
    if (topParabola->cEvent) // Event annulé car bouffé par une nouvelle parabole
    {
        deleteEvent(topParabola->cEvent);
        topParabola->cEvent = NULL;
    }

    Parabola    *p0 = new Parabola(topParabola->site); // Gauche
    Parabola    *p1 = new Parabola(site);              // Nouvelle, celle qui coupe
    Parabola    *p2 = new Parabola(topParabola->site); // Droite

    topParabola->setRight(p2);
    topParabola->setLeft(new Parabola());
    topParabola->left()->setLeft(p0);
    topParabola->left()->setRight(p1);

    CrossedEdge *edge = createEdge(topParabola->site, site);
    topParabola->edge = edge;
    topParabola->left()->edge = edge;
    // à refaire en plus propre
    topParabola->direction.x = edge->d1->point.y - edge->d0->point.y;
    topParabola->direction.y = edge->d0->point.x - edge->d1->point.x;
    topParabola->left()->direction.x = - topParabola->direction.x;
    topParabola->left()->direction.y = - topParabola->direction.y;

    topParabola->isLeaf = false;

    checkCircle(p0);
    checkCircle(p2);

}

void    VoronoiGenerator::removeParabola(QedEvent *e)
{
    std::cout << "---\nremoveParabola(" << *e->arch << ")" << std::endl;
    Parabola    *p1 = e->arch;

    Parabola    *pLeft = Parabola::getLeftParent(p1);
    Parabola    *pRight = Parabola::getRightParent(p1);
    Parabola    *p0 = Parabola::getLeftChild(pLeft);
    Parabola    *p2 = Parabola::getRightChild(pRight);

    if (p0 == p2)
        std::cout << "error : same focal point\n";

    if (p0->cEvent)
    {
        deleteEvent(p0->cEvent);
        p0->cEvent = NULL;
    }
    if (p2->cEvent)
    {
        deleteEvent(p2->cEvent);
        p2->cEvent = NULL;
    }

    Corner  *corner = new Corner();
    _corners.push_back(corner);

    std::cout << "pLeft : " << *pLeft << "pRight" << *pRight << std::endl;

    corner->point.x = p1->corner->x;
    corner->point.y = p1->corner->y;
    pLeft->edge->v1 = corner;
    pRight->edge->v0 = corner;
    // todo rajouter site corner et corner site

    // REFAIRE !!
    Parabola * higher;
    Parabola * par = p1;
    while(par != _root)
    {
        par = par->parent;
        std::cout << *par << std::endl;
        if(par == pLeft) higher = pLeft;
        if(par == pRight) higher = pRight;
    }

    std::cout << *p0->site << "\n" << *p2->site << std::endl;
    higher->edge = new CrossedEdge();
    higher->edge->midpoint.x = corner->point.x;
    higher->edge->midpoint.y = corner->point.y; // à verifier
    higher->edge->d0 = p0->site;
    higher->edge->d1 = p2->site;
    higher->edge->v0 = corner;
    _edges.push_back(higher->edge);

    Parabola * gparent = p1->parent->parent;
    std::cout << "p : " << *p1->parent << "; gp : " << *gparent << std::endl;
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

CrossedEdge    *VoronoiGenerator::createEdge(Site *d0, Site *d1)
{
    CrossedEdge  *edge = new CrossedEdge();
    edge->d0 = d0;
    d0->borders.push_back(edge);
    edge->d1 = d1;
    d1->borders.push_back(edge);

    // temporarely use the edge midpoint until the edge is formed (usefull for first edges)
    edge->midpoint.x = d1->point.x;
    edge->midpoint.y = getY(d0, d1->point.x);

    _edges.push_back(edge);
    return edge;
}

void        VoronoiGenerator::deleteEvent(QedEvent *e)
{
    std::multimap<double, QedEvent *>::iterator it = _events.find(e->y);
    if (it != _events.end())
    {
        _events.erase(it);
        delete e;
    }
}

double      VoronoiGenerator::getXofEdge(Parabola *p, double y)
{
    Site        *sLeft = Parabola::getLeftChild(p)->site;
    Site        *sRight = Parabola::getRightChild(p)->site;

    std::cout << "-\ngetXofEdge(" << *p << ", " << y << ")\n";
    std::cout << "fils gauche : " << *Parabola::getLeftChild(p) << "; fils droite : " << *Parabola::getRightChild(p) << std::endl;
    std::cout << "site fils gauche : " << *sLeft << "; site fils droite : " << *sRight << std::endl;

    // justifier
    double per;

    // 1 = parabole gauche ; 2 = parabole droite ; vide = intersection
    // ax² + bx + c
    double a, a1, a2, b, b1, b2, c, c1, c2;

    // b² - 4ac, resolution d'equation du second defrée
    double   delta, x1, x2;

    double result;

    per = 2.0 * (sLeft->point.y - y);

    a1 = 1.0 / per;
    b1 = -2.0 * sLeft->point.x / per;
    c1 = y + per / 4 + sLeft->point.x * sLeft->point.x / per;

    per = 2.0 * (sRight->point.y - y);
    a2 = 1.0 / per;
    b2 = -2.0 * sRight->point.y / per;
    c2 = _sweepLine + per / 4 + sRight->point.y * sRight->point.y / per; // why _sweepline ?

    a = a1 - a2;
    b = b1 - b2;
    c = c1 - c2;

    delta = b*b - 4 * a * c;
    x1 = (-b + sqrt(delta)) / (2*a);
    x2 = (-b - sqrt(delta)) / (2*a);

    if(sLeft->point.y < sRight->point.y ) // REPASSER PAR ICI
        result = std::max(x1, x2);
    else
        result = std::min(x1, x2);

    std::cout << " x1 : " << x1 << " x2 : " << x2 << " result : " << result << std::endl;
    return result;
}

Parabola    *VoronoiGenerator::getParabolaByX(double nx)
{
    std::cout << "---\ngetParabolaByX(" << nx << ")" << std::endl;
    Parabola *p = _root;
    double x = 0.0;

    while(!p->isLeaf)
    {
        x = getXofEdge(p, _sweepLine);
        std::cout << " left : " << *p->left() << "; right : " << *p->right() << std::endl;
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

    std::cout << "-\ngetY(" << *s << ", " << x << ") : " << result << std::endl;
    return(result);
}

void        VoronoiGenerator::checkCircle(Parabola *b)
{
    std::cout << "---\ncheckCircle with parabola : " << *b << std::endl;
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
    std::cout << std::endl << "leftChild : ";
    if (a) std::cout << *a;
    else std::cout << "Nan";
    std::cout << "; rightChild : ";
    if (c) std::cout << *c;
    else std::cout << "Nan";
    std::cout << std::endl;

    if (!a || !c || a->site == c->site)
        return;

    Point * s = 0;
    s = getEdgeIntersection(leftParent, rightParent);
    if(!s)
        return;

    // Justifier
    /*double dx = a->site->point.x - s->x;
    double dy = a->site->point.y - s->y;

    double d = sqrt( (dx * dx) + (dy * dy) );

    if(s->y - d >= _sweepLine) { return;}*/

    QedEvent * e = new QedEvent(s->y/* - d*/, QedEvent::INTERSECTION);
    b->corner = s;
    b->cEvent = e;
    e->arch = b;

    std::cout << "Added a circle event at y = " << e->y << std::endl;
    _events.insert(std::pair<double, QedEvent *>(e->y, e));
}

Point       *VoronoiGenerator::getEdgeIntersection(Parabola *a, Parabola *b)
{
    std::cout << "-\ngetEdgeIntersection(" << *a << ", " << *b << ")" << std::endl;
    // d0 = top = left; d1 = bot = right
    // f* | g* = coeff directeur de la mediatrice d0/d1 (y = f*x + g)
    // à bouger dans CrossedEdge

    // se rappeler pourquoi -
    double fa = -(a->edge->d1->point.x - a->edge->d0->point.x) /
            (a->edge->d1->point.y - a->edge->d0->point.y);
    double fb = -(b->edge->d1->point.x - b->edge->d0->point.x) /
            (b->edge->d1->point.y - b->edge->d0->point.y);

    double ga = a->edge->midpoint.y - fa * a->edge->midpoint.x;
    double gb = b->edge->midpoint.y - fb * b->edge->midpoint.x;

    std::cout << "Vor edge a {" << *a << "} : y = " << fa << "x + " << ga << std::endl;
    std::cout << "Vor edge b {" << *b << "} : y = " << fb << "x + " << gb << std::endl;

    std::cout << a->direction.x << "|" << b->direction.x << ", " << a->direction.y << "|" << b->direction.y << std::endl;

    double x = (gb-ga) / (fa - fb);
    double y = fa * x + ga;

    std::cout << "x:" << x << "; y:" << y << std::endl;

    if((x - a->edge->midpoint.x)/a->direction.x < 0) return 0;
    if((y - a->edge->midpoint.y)/a->direction.y < 0) return 0;
    if((x - b->edge->midpoint.x)/b->direction.x < 0) return 0;
    if((y - b->edge->midpoint.y)/b->direction.y < 0) return 0;

    std::cout << "result : " << x << "; " << y << std::endl;

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

    _root = NULL;
    Site::indexMax = 0;
    Corner::indexMax = 0;
    CrossedEdge::indexMax = 0;
    Parabola::indexMax = 0;
}
