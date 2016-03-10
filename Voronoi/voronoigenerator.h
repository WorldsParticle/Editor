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

    explicit QedEvent(double ny, Type t) : type(t), y(ny), parabola(NULL), site(NULL) {}

    Type        type;

    double      y;
    Parabola    *parabola; // if interesection
    Site        *site;     // if point

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
    void    fortuneAlgo();
    void    LloydRelaxation();

    void    addParabola(Site *s);
    void    removeParabloa(QedEvent *e); // should pass Parabola as argument when implemented

    QedEvent    *popNextEvent();

    void    reset();

    int                     _cellNumber;
    int                     _xMax;
    int                     _yMax;

    std::vector<Site *>     _sites;
    std::vector<Corner *>   _corners;
    std::vector<CrossedEdge *>  _edges;

    ///
    /// \brief _events potential future events wich can modify the beach line
    /// (another point or parabola intersection)
    ///
    std::multimap<double, QedEvent *>   _events;

    int                     _sweepLine;     // sweep line going down
    Parabola                *_root;         // root parabola containing the beach line
};

#endif // VORONOIGENERATOR_H
