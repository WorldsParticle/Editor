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

    inline std::vector<Site *>    &sites()
    { return _sites; }
    inline std::vector<Corner *>    &corners()
    { return _corners; }
    inline std::vector<CrossedEdge *>      &edges()
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

    void    deleteEvent(QedEvent *e);

    // to review
    double       getXofEdge(Parabola *p, double y); // return current x position of an intersection point of left and right parabolas
    Parabola    *getParabolaByX(double nx); // return  Parabola under nx position in the current beachline

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
    Point *getEdgeIntersection(Parabola *a, Parabola *b); // à refaire en plus propre

    QedEvent    *popNextEvent();

    void    reset();

    int                     _cellNumber;
    double                  _xMax;
    double                  _yMax;

    std::vector<Site *>     _sites;
    std::vector<Corner *>   _corners;
    std::vector<CrossedEdge *>  _edges;

    ///
    /// \brief _events potential future events wich can modify the beach line
    /// (another point or parabola intersection)
    ///
    std::multimap<double, QedEvent *>   _events;

    double                  _sweepLine;     // sweep line going down
    Parabola                *_root;         // root parabola containing the beach line
};

#endif // VORONOIGENERATOR_H
