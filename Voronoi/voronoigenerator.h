//
// http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/
// https://en.wikipedia.org/wiki/Fortune%27s_algorithm
// https://fr.wikipedia.org/wiki/Triangulation_de_Delaunay
// https://en.wikipedia.org/wiki/Voronoi_diagram
// https://github.com/nodename/as3delaunay/blob/master/src/com/nodename/Delaunay/Voronoi.as
//


#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include "graph.h"
#include <list>
#include <map>

///
/// \brief The QueuedEvent class
/// represent an event (next point in x coordinate or intersection of three circles)
/// \todo Replace with Site when sure of implementation
///
class QueuedEvent
{

public:

    enum Type
    {
        POINT = 0,      // Site
        INTERSECTION    // Vertex
    };

    explicit QueuedEvent(Point p, Type t = POINT);

    Point   _point;
    Type    _type;
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

    inline const std::vector<Point> &points()
    { return _points; }
    inline std::vector<Face *>    &centers()
    { return _centers; }
    inline std::vector<Corner *>    &corners()
    { return _corners; }
    inline std::vector<Edge *>      &edges()
    { return _edges; }

private:
    void    generateRandomPoints();
    void    fortuneAlgo();

    QueuedEvent    *popNextEvent();

    void    reset();

    int                     _cellNumber;
    int                     _xMax;
    int                     _yMax;

    std::vector<Point>      _points;  // only during construction
    std::vector<Face *>   _centers;
    std::vector<Corner *>   _corners;
    std::vector<Edge *>     _edges;

    ///
    /// \brief _events potential future events wich can modify the beach line
    /// (another point or parabola intersection)
    std::multimap<int, QueuedEvent *>   _events;
};

#endif // VORONOIGENERATOR_H
