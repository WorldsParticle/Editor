//
// http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/
// https://en.wikipedia.org/wiki/Fortune%27s_algorithm
// https://fr.wikipedia.org/wiki/Triangulation_de_Delaunay
// https://en.wikipedia.org/wiki/Voronoi_diagram
// https://github.com/nodename/as3delaunay/blob/master/src/com/nodename/Delaunay/Voronoi.as
//
// TODO : choisir la gestion des semi edges temporaires (pas halfedge)


#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include "graph.h"
#include "parabola.h"
#include <list>
#include <map>
#include <set>
#include <queue>

///
/// \brief The QueuedEvent class
/// represent an event (next point in x coordinate or intersection of three circles)
/// \todo Replace with Site when sure of implementation
///
class QedEvent
{

public:

    enum Type
    {
        POINT = 0,      // Site, add parabola
        INTERSECTION    // Vertex, remove parabola
    };

    explicit QedEvent(double ny, Type t) : type(t), y(ny), arch(NULL), site(NULL) {}

    Type        type;

    double      y;
    Parabola    *arch; // if interesection
    Site        *site; // if point

    // Doit y'avoir moyen rester sur une map ou un set simple, voir une liste
    struct compareEvent : public std::binary_function<QedEvent *, QedEvent *, bool>
    {
        bool    operator()(const QedEvent *l, const QedEvent *r) const { return (l->y > r->y); }
    };

};

///
/// \brief The VoronoiGenerator class
/// Based on the design found in https://github.com/amitp/mapgen2
///
class VoronoiGenerator
{
public:
    VoronoiGenerator();
    ~VoronoiGenerator();

    void    launch(int number, int xMax, int yMax);

    inline std::map<int, Site *>    &sites()
    { return _sites; }
    inline std::map<int, Corner *>    &corners()
    { return _corners; }
    inline std::map<int, CrossedEdge *>      &edges()
    { return _edges; }

private:
    void    generateRandomSites();
    void    generateTestSites();
    void    fortuneAlgo();
    void    LloydRelaxation();
    void    finishEdges(Parabola *p);

    void    addParabola(Site *site);
    void    removeParabola(QedEvent *e); // should pass Parabola as argument when implemented

    CrossedEdge *createEdge(Site *d0, Site *d1, bool computeMidPoint = true);

    // to review
    double       getXofEdge(Parabola *p, double y); // return current x position of an intersection point of left and right parabolas
    Parabola    *getParabolaAtX(double nx); // return leaf parabola at nx position in the current beachline

    ///
    /// \brief getY will retrieve the intersecting y value between a site parabola and an x value
    /// \param s is the site
    /// \param x is the x value
    /// \return
    ///
    double      getY(Site *s, double x);

    ///
    /// \brief checkCircle find if the current parabola will close soon
    /// \param p
    ///
    void        checkCircle(Parabola *b);

    ///
    /// \brief getEdgeIntersection compute the point where two parabola edge will collide.
    /// \param a
    /// \param b
    /// \todo  return bool a feed a reference
    ///
    bool    getEdgeIntersection(Parabola *a, Parabola *b, Point &result); // à refaire en plus propre

    void    reset();

    int                     _cellNumber;
    double                  _xMax;
    double                  _yMax;

    std::map<int, Site *>     _sites;
    std::map<int, Corner *>   _corners;
    std::map<int, CrossedEdge *>  _edges;

    ///
    /// \brief _events potential future events wich can modify the beach line
    /// (another point or parabola intersection)
    ///
    std::priority_queue<QedEvent *, std::vector<QedEvent *>, QedEvent::compareEvent>   _events;
    std::set<QedEvent *>	_deleted; // comme je repasse sur une queue

    double                  _sweepLine;     // sweep line going down
    Parabola                *_root;         // root parabola containing the beach line
};

#endif // VORONOIGENERATOR_H
