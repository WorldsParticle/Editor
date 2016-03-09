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

typedef std::pair<int, int> Point; // should change to real class
class   Face;
class   Corner;
class   CrossedEdge;
class   HalfEdge;
class   Site;

///
/// \brief The Face class
/// Represent the Delaunay triangulation
/// This is the zone as itself
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
    std::vector<CrossedEdge *>     _borders;
    std::vector<Corner *>   _corners;
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

    static int  _indexMax;  // change this
    const int   _index;

    Point   _point;     // location
    bool    _ocean;     // ocean
    bool    _water;     // lake or ocean
    bool    _coast;     // touches ocean and land polygons
    bool    _border;    // at the edge of the map
    float   _elevation; // 0.0-1.0
    float   _moisture;  // 0.0-1.0

    std::vector<Face *>         _faces; // touching faces
    std::vector<CrossedEdge *>  _edges; // touching edges
    std::vector<Corner *>       _adjacent; // adjacent corners

    int     _river;     // 0 if no river, or volume of water in river
    Corner  *_downslope; // pointer to adjacent corner most downhill
    Corner  *_watershed; // pointer to coastal corner, or null
    int     _watershedSize;
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

    static int  _indexMax;  // change this
    const int   _index;

    Face        *_d0, *_d1;   // Delaunay edge
    Corner      *_v0, *_v1;   // Voronoi edge
    Point       _midpoint;  // cross point, halfway between v0 and v1
    int         _river;     // Volume of water, not necessary right now
};

///
/// \brief The halfEdge class
/// see the wikipedia link for more details (doubly connected edge list)
/// \todo index as the other ?
///
class HalfEdge
{
    CrossedEdge *_edge; // here represent the Voronoi one
    Face        *_center;

    Corner      *_origin;       // maybe use _edge.v0/v1 instead, if able to keep track of direction
    Corner      *_destination;  // maybe use _edge.v1/v0 instead, if able to keep track of direction

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
