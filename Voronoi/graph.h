#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

typedef std::pair<int, int> Point;
class Center;
class Corner;
class Edge;

///
/// \brief The Center class (used as a structure)
///
class Center
{

public:

    explicit Center();

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

    std::vector<Center *>   _neighbors;
    std::vector<Edge *>     _borders;
    std::vector<Corner *>   _corners;
};

///
/// \brief The Corner class (used as a structure)
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

    std::vector<Center *>   _touches;
    std::vector<Edge *>     _protrudes;
    std::vector<Corner *>   _adjacent;

    int     _river;     // 0 if no river, or volume of water in river
    Corner  *_downslope; // pointer to adjacent corner most downhill
    Corner  *_watershed; // pointer to coastal corner, or null
    int     _watershedSize;
};

///
/// \brief The Edge class (used as a structure)
///
class Edge
{

public:

    explicit Edge();

    static int  _indexMax;  // change this
    const int   _index;

    Center  *_d0, *_d1;   // Delaunay edge
    Corner  *_v0, *_v1;   // Voronoi edge
    Point   _midpoint;  // halfway between v0, v1
    int     _river;     // Volume of water, not necessary right now
};
#endif // GRAPH_H
