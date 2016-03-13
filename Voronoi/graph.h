//
// https://en.wikipedia.org/wiki/Polygon_mesh
// https://en.wikipedia.org/wiki/Doubly_connected_edge_list
// https://github.com/amitp/mapgen2/tree/master/graph
// http://www.skynet.ie/~sos/masters/VoronoiDiagramGenerator.h
//
// Keep in mind that Face are corners of Delaunay cells, and center of Voronoi's
// Same for Corner : they are corners of Voronoi's, and centroid of Delaunay's
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>

class   Site;
class   Corner;
class   CrossedEdge;
class   HalfEdge;

class   Point
{
public:
    explicit Point(double nx, double ny) : x(nx), y(ny) {}

    double  x;
    double  y;
};

///
/// \brief The Site class
/// Represent the Delaunay triangulation
/// This is the zone as itself, the face of the polygon
///
class Site
{

public:

    explicit Site();

    inline friend std::ostream &operator<<(std::ostream &os, const Site &s)
    { return os << "[" << s.index << "](" << s.point.x << ", " << s.point.y << ")"; }

    static int  indexMax;  // change this
    const int   index;

    Point       point;     // location
    bool        water;     // lake or ocean
    bool        ocean;     // ocean
    bool        coast;     // land polygon touching an ocean
    bool        border;    // at the edge of the map
    float       elevation; // 0.0-1.0
    float       moisture;  // 0.0-1.0

    std::string biome;     // biome type (see article)

    std::vector<Site *>         neighbors;
    std::vector<CrossedEdge *>  borders;
    std::vector<Corner *>       corners;
};

///
/// \brief The Corner class (vertex)
/// represent the vertices of zones
/// contains the shape of Voronoi polygons
///
class Corner
{

public:

    explicit Corner();

    static int  indexMax;  // change this
    const int   index;

    Point   point;     // location
    bool    ocean;     // ocean
    bool    water;     // lake or ocean
    bool    coast;     // touches ocean and land polygons
    bool    border;    // at the edge of the map
    float   elevation; // 0.0-1.0
    float   moisture;  // 0.0-1.0

    std::vector<Site *>         faces; // touching faces
    std::vector<CrossedEdge *>  edges; // touching edges
    std::vector<Corner *>       adjacent; // adjacent corners

    int     river;     // 0 if no river, or volume of water in river
    Corner  *downslope; // pointer to adjacent corner most downhill
    Corner  *watershed; // pointer to coastal corner, or null
    int     watershedSize;
};

///
/// \brief The CrossedEdge class
/// represent both edge of Voronoi and Delaunay graph
/// allowing to connect them together
/// it is the cross point you can see between black and white segment in http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/voronoi-and-delaunay.png
///
class CrossedEdge
{

public:

    explicit CrossedEdge();

    static int  indexMax;  // change this
    const int   index;

    Site        *d0, *d1;   // Delaunay edge (during computing, d0 will be used as left, d1 as right)
    Corner      *v0, *v1;   // Voronoi edge
    Point       midpoint;  // cross point, halfway between v0 and v1
    int         river;     // Volume of water, not necessary right now
};

///
/// \brief The halfEdge class
/// see the wikipedia link for more details (doubly connected edge list)
/// \todo index as the other ?
///
class HalfEdge
{
    CrossedEdge *edge; // here represent the Voronoi one
    Site        *center;

    Corner      *origin;       // maybe use _edge.v0/v1 instead, if able to keep track of direction
    Corner      *destination;  // maybe use _edge.v1/v0 instead, if able to keep track of direction

    HalfEdge    *prev;
    HalfEdge    *next;
    HalfEdge    *twin;
};

#endif // GRAPH_H
