#include "voronoigenerator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>

#define DRAND(min, max) (min) + ((double)std::rand() / RAND_MAX) * ((max) - (min))

VoronoiGenerator::VoronoiGenerator() :
    _cellNumber(0),
    _xMax(0),
    _yMax(0),
    _sites(),
    _corners(),
    _edges(),
    _events(),
    _deleted(),
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
    LloydRelaxation(); // en gros equilibrer les point et relancer fortune

    std::cout << "FINISH" << std::endl;
}

void    VoronoiGenerator::generateRandomSites()
{
    for (int i = 0; i < _cellNumber; ++i)
    {
        Site    *s = new Site();
        s->point.x = DRAND(0, _xMax);
        s->point.y = DRAND(0, _yMax);

        _sites.insert(std::pair<int, Site*>(s->index, s));

        std::cout << *s;

        QedEvent *e = new QedEvent(s->point.y, QedEvent::POINT);
        e->site = s;
        _events.push(e);
    }
    std::cout << std::endl;
}

void    VoronoiGenerator::generateTestSites()
{
    Site        *s;
    QedEvent    *e;

    s = new Site(100, 50);
    _sites.insert(std::pair<int, Site*>(s->index, s));
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.push(e);

    s = new Site(30, 80);
    _sites.insert(std::pair<int, Site*>(s->index, s));
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.push(e);

    s = new Site(200, 100);
    _sites.insert(std::pair<int, Site*>(s->index, s));
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.push(e);

    s = new Site(120, 150);
    _sites.insert(std::pair<int, Site*>(s->index, s));
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.push(e);

    s = new Site(250, 200);
    _sites.insert(std::pair<int, Site*>(s->index, s));
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.push(e);

    s = new Site(50, 300);
    _sites.insert(std::pair<int, Site*>(s->index, s));
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.push(e);

    s = new Site(400, 300);
    _sites.insert(std::pair<int, Site*>(s->index, s));
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.push(e);

    s = new Site(230, 400);
    _sites.insert(std::pair<int, Site*>(s->index, s));
    e = new QedEvent(s->point.y, QedEvent::POINT);
    e->site = s;
    _events.push(e);
}

void    VoronoiGenerator::fortuneAlgo()
{
    while (!_events.empty())
    {
        QedEvent *event = _events.top();
        _events.pop();

        _sweepLine = event->y;

        if(_deleted.find(event) != _deleted.end())
        {
            delete(event);
            _deleted.erase(event);
            continue;
        }

        std::cout << std::endl << "<event type : " << event->type << "; y = " << event->y << ">" << std::endl;
        if (event->type == QedEvent::POINT)
            addParabola(event->site);
        else
            removeParabola(event);
    }

    finishEdges(_root);
    for (const auto &b: _sites.at(0)->borders)
        std::cout << *b << std::endl;
}

void    VoronoiGenerator::LloydRelaxation()
{

}

void	VoronoiGenerator::finishEdges(Parabola * p)
{
    if(p->isLeaf) {delete p; return;}

    double mx;
    if(p->direction.x > 0.0)
        mx = std::max(_xMax, p->edge->midpoint.x + 10);
    else
        mx = std::min(0.0, p->edge->midpoint.x - 10);

    // Changer quand integration de f/g dans graph
    double f = -(p->edge->d1->point.x - p->edge->d0->point.x) /
            (p->edge->d1->point.y - p->edge->d0->point.y);
    double g = p->edge->midpoint.y - f * p->edge->midpoint.x;

    Corner *corner = new Corner();
    corner->point.x = mx;
    corner->point.y = f * mx + g;

    if (corner->point.y < 0)
    {
        corner->point.y = 0;
        corner->point.x = (-g) / f;
    }
    else if (corner->point.y > _yMax)
    {
        corner->point.y = _yMax;
        corner->point.x = (_yMax - g) / f;
    }

    _corners.insert(std::pair<int, Corner*>(corner->index, corner));
    p->edge->v1 = corner;
    corner->edges.push_back(p->edge);

    std::cout << "corner : " << *corner << std::endl;

    finishEdges(p->left());
    finishEdges(p->right());
    delete p;
}


void    VoronoiGenerator::addParabola(Site *site)
{
    std::cout << "<===== addParabola(" << *site << ") =====>" << std::endl << std::endl;
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

    Parabola    *topParabola = getParabolaAtX(site->point.x); // get first parabola above the new site
    if (topParabola->cEvent) // Event annulé car bouffé par une nouvelle parabole
    {
        _deleted.insert(topParabola->cEvent);
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

    std::cout << "right non leaf (" << *topParabola<< ") : " << topParabola->direction.x << "left one (" << *topParabola->left() << ") : " << topParabola->left()->direction.x << std::endl;

    topParabola->isLeaf = false;

    if (site->index == 3)
        std::cout << "ATTENTION => " << *edge << std::endl;

    checkCircle(p0);
    checkCircle(p2);

}

void    VoronoiGenerator::removeParabola(QedEvent *e)
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

    Corner  *corner = new Corner();
    _corners.insert(std::pair<int, Corner*>(corner->index, corner));

    std::cout << "pLeft : " << *pLeft << "pRight" << *pRight << std::endl;

    corner->point.x = p1->corner.x;
    corner->point.y = p1->corner.y;

    pLeft->edge->v1 = corner;
    pRight->edge->v0 = corner;
    corner->edges.push_back(pLeft->edge);
    corner->edges.push_back(pRight->edge);

    p0->site->corners.push_back(corner);
    p1->site->corners.push_back(corner);
    p2->site->corners.push_back(corner);
    corner->faces.push_back(p0->site);
    corner->faces.push_back(p1->site);
    corner->faces.push_back(p2->site);

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
    higher->edge = createEdge(p0->site, p2->site, false);
    higher->edge->midpoint.x = corner->point.x;
    higher->edge->midpoint.y = corner->point.y;
    higher->edge->v0 = corner;
    corner->edges.push_back(higher->edge);

    pLeft->direction.x = higher->edge->d1->point.y - higher->edge->d0->point.y;
    pLeft->direction.y = higher->edge->d0->point.x - higher->edge->d1->point.x;
    pRight->direction.x = - pLeft->direction.x;
    pRight->direction.y = - pLeft->direction.y;

    std::cout << "left (" << *pLeft << ") direction : " << pLeft->direction;
    std::cout << "; right (" << *pRight << ") direction : " << pRight->direction;

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

CrossedEdge    *VoronoiGenerator::createEdge(Site *d0, Site *d1, bool computeMidPoint)
{
    CrossedEdge  *edge = new CrossedEdge();
    edge->d0 = d0;
    d0->borders.push_back(edge);
    edge->d1 = d1;
    d1->borders.push_back(edge);

    // temporarely use the edge midpoint until the edge is formed (usefull for first edges)
    if (computeMidPoint)
    {
        edge->midpoint.x = d1->point.x;
        edge->midpoint.y = getY(d0, d1->point.x);
    }

    _edges.insert(std::pair<int, CrossedEdge*>(edge->index, edge));
    return edge;
}

double      VoronoiGenerator::getXofEdge(Parabola *p, double y)
{
    Site        *sLeft = Parabola::getLeftChild(p)->site;
    Site        *sRight = Parabola::getRightChild(p)->site;

    std::cout << "<- getXofEdge(" << *p << ", " << y << ") ->" << std::endl;
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

    // REVERIFIER
    per = 2.0 * (sLeft->point.y - y);
    a1 = 1.0 / per;
    b1 = -2.0 * sLeft->point.x / per;
    c1 = y + per / 4 + sLeft->point.x * sLeft->point.x / per;

    per = 2.0 * (sRight->point.y - y);
    a2 = 1.0 / per;
    b2 = -2.0 * sRight->point.x / per;
    c2 = _sweepLine + per / 4 + sRight->point.x * sRight->point.x / per; // why _sweepline ?

    a = a1 - a2;
    b = b1 - b2;
    c = c1 - c2;

    delta = b*b - 4 * a * c;
    x1 = (-b + sqrt(delta)) / (2*a);
    x2 = (-b - sqrt(delta)) / (2*a);

    std::cout << p->direction.x << "; " << p->direction.y << std::endl;

    if(p->direction.x > 0) // REPASSER PAR ICI
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

double      VoronoiGenerator::getY(Site *s, double x)
{
    // Formule d'intersection, à reviser
    double dp = 2 * (s->point.y - _sweepLine);
    double a1 = 1 / dp;
    double b1 = -2 * s->point.x / dp;
    double c1 = _sweepLine + dp / 4 + s->point.x * s->point.x / dp;

    double result = a1*x*x + b1*x + c1;

    std::cout << "<- getY(" << *s << ", " << x << ") : " << result << " ->" << std::endl;
    return(result);
}

void        VoronoiGenerator::checkCircle(Parabola *b)
{
    std::cout << "<--- checkCircle(" << *b << ") --->" << std::endl;
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

    Point s(0, 0);
    if (!getEdgeIntersection(leftParent, rightParent, s))
        return;

    // REVOIR
    /*double dx = a->site->point.x - s->x;
    double dy = a->site->point.y - s->y;

    double d = sqrt( (dx * dx) + (dy * dy) );

    if(s->y - d >= _sweepLine) { return;}*/

    QedEvent * e = new QedEvent(s.y/* - d*/, QedEvent::INTERSECTION);
    b->corner = s;
    b->cEvent = e;
    e->arch = b;

    std::cout << "Added a circle event at y = " << e->y << std::endl;
    _events.push(e);
}

bool VoronoiGenerator::getEdgeIntersection(Parabola *a, Parabola *b, Point &result)
{
    std::cout << "<- getEdgeIntersection(" << *a << ", " << *b << ") ->" << std::endl;
    // d0 = top = left; d1 = bot = right
    // f* | g* = coeff directeur de la mediatrice d0/d1 (y = f*x + g)
    // à bouger dans CrossedEdge

    // se rappeler pourquoi -, et FACTORISER !!!
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
    std::cout << "amx :" << a->edge->midpoint.x << "; amy :" << a->edge->midpoint.y;
    std::cout << "; adx" << a->direction.x << "; ady :" << a->direction.y << std::endl;
    std::cout << "bmx :" << b->edge->midpoint.x << "; bmy :" << b->edge->midpoint.y;
    std::cout << "; bdx" << b->direction.x << "; bdy :" << b->direction.y << std::endl;

    if((x - a->edge->midpoint.x)/a->direction.x < 0) return false;
    if((y - a->edge->midpoint.y)/a->direction.y < 0) return false;
    if((x - b->edge->midpoint.x)/b->direction.x < 0) return false;
    if((y - b->edge->midpoint.y)/b->direction.y < 0) return false;

    std::cout << "result : " << x << "; " << y << std::endl;
    result.x = x;
    result.y = y;
    return true;
}

void    VoronoiGenerator::reset()
{
    for (std::map<int, Site *>::iterator it = _sites.begin();
         it != _sites.end(); ++it)
        delete (*it).second;

    for (std::map<int, Corner *>::iterator it = _corners.begin();
         it != _corners.end(); ++it)
        delete (*it).second;

    for (std::map<int, CrossedEdge *>::iterator it = _edges.begin();
         it != _edges.end(); ++it)
        delete (*it).second;

    _sites.clear();
    _corners.clear();
    _edges.clear();

    _root = NULL;
    Site::indexMax = 0;
    Corner::indexMax = 0;
    CrossedEdge::indexMax = 0;
    Parabola::indexMax = 0;
}
