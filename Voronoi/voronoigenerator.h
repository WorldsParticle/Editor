#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include "graph.h"

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
    inline std::vector<Center *>    &centers()
    { return _centers; }
    inline std::vector<Corner *>    &corners()
    { return _corners; }
    inline std::vector<Edge *>      &edges()
    { return _edges; }

private:
    void    generateRandomPoints();
    void    fortuneAlgo();

    void    reset();

    int                     _cellNumber;
    int                     _xMax;
    int                     _yMax;

    std::vector<Point>      _points;  // only during construction
    std::vector<Center *>   _centers;
    std::vector<Corner *>   _corners;
    std::vector<Edge *>     _edges;
};

#endif // VORONOIGENERATOR_H
