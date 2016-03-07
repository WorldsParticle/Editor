//
// https://en.wikipedia.org/wiki/Polygon_mesh
// https://en.wikipedia.org/wiki/Doubly_connected_edge_list
// https://github.com/amitp/mapgen2/tree/master/graph
// http://www.skynet.ie/~sos/masters/VoronoiDiagramGenerator.h
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

typedef std::pair<int, int> Point; // should change to real class
class   Face;
class   Corner;
class   Edge;
class   HalfEdge;
class   Site;

///
/// \brief The Face class
/// Represent the aera shape (polygonal), and the zone biome
///
class Face
{

public:

    explicit Face();

    static int  _indexMax;  // change this
    const int   _index;

    Point       _point;     // location
    bool        _water;     // lake or ocean
    bool        _ocean;     // ocean
    bool        _coast;     // land polygon touching an ocean
    bool        _border;    // at the edge of the map
    float       _elevation; // 0.0-1.0
    float       _moisture;  // 0.0-1.0

    std::string _biome;     // biome type (see article)

    std::vector<Face *>     _neighbors;
    std::vector<Edge *>     _borders;
    std::vector<Corner *>   _corners;
};

///
/// \brief The Corner class (vertex)
/// represent the vertices of zones
///
class Corner
{

public:

    explicit Corner();

    static int  _indexMax;  // change this
    const int   _index;

    Point   _point;     // location
    bool    _ocean;     // ocean
    bool    _water;     // lake or ocean
    bool    _coast;     // touches ocean and land polygons
    bool    _border;    // at the edge of the map
    float   _elevation; // 0.0-1.0
    float   _moisture;  // 0.0-1.0

    std::vector<Face *>     _faces; // touching faces
    std::vector<Edge *>     _edges; // touching edges
    std::vector<Corner *>   _adjacent; // adjacent corners

    int     _river;     // 0 if no river, or volume of water in river
    Corner  *_downslope; // pointer to adjacent corner most downhill
    Corner  *_watershed; // pointer to coastal corner, or null
    int     _watershedSize;
};

///
/// \brief The Edge class
/// represent line between corners which cut zones
///
class Edge
{

public:

    explicit Edge();

    static int  _indexMax;  // change this
    const int   _index;

    Face        *_d0, *_d1;   // Delaunay edge
    Corner      *_v0, *_v1;   // Voronoi edge
    Point       _midpoint;  // halfway between v0, v1
    int         _river;     // Volume of water, not necessary right now
};

///
/// \brief The halfEdge class
/// see the wikipedia link for more details (doubly connected edge list)
/// \todo index as the other ?
///
class HalfEdge
{
    Edge        *_edge;
    Face        *_center;

    Corner      *_origin;
    Corner      *_destination;

    HalfEdge    *_prev;
    HalfEdge    *_next;
    HalfEdge    *_twin;
};


///
/// \brief The Site struct
/// not sure yet of the way to implement this one
/// \todo index as the other ?
///
struct Site
{
    Point	coord;
    int		sitenbr;
    int		refcnt;
};

#endif // GRAPH_H
