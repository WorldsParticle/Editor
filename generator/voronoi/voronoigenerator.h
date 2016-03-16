#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include "generator.h"
#include "../map/point.h"
#include "event.h"
#include <list>
#include <map>
#include <queue>
#include <set>

namespace MAP
{
    class Zone;
}

namespace VOR
{

class Parabola;
class Edge;

///
/// \brief The VoronoiGenerator class
/// Based on the design found in https://github.com/amitp/mapgen2
///
class VoronoiGenerator : public GEN::Generator
{
public:
    VoronoiGenerator();
    ~VoronoiGenerator();

    virtual void run();

private:
    void    addSite(double x, double y);
    void    generateRandomSites();
    void    generateTestSites();
    void    fortuneAlgo();
    void    LloydRelaxation();
    void    finishEdge(Parabola *p);

    void    addParabola(MAP::Zone *site);
    void    removeParabola(Event *e); // should pass Parabola as argument when implemented

    // to review
    double       getXofEdge(Parabola *p, double y); // return current x position of an intersection point of left and right parabolas
    Parabola    *getParabolaAtX(double nx); // return leaf parabola at nx position in the current beachline

    ///
    /// \brief getY will retrieve the intersecting y value between a site parabola and an x value
    /// \param s is the site
    /// \param x is the x value
    /// \return
    ///
    double      getY(const Point &s, double x);

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
    bool    getEdgeIntersection(Edge *a, Edge *b, Point &result); // à refaire en plus propre

    std::vector<Edge *>         _tempEdges;

    ///
    /// \brief _events potential future events wich can modify the beach line
    /// (another point or parabola intersection)
    ///
    std::priority_queue<Event *, std::vector<Event *>, Event::compareEvent>   _events;
    std::set<Event *>   _deleted; // comme je repasse sur une queue

    double                  _sweepLine;     // sweep line going down
    Parabola                *_root;         // root parabola containing the beach line
};

}

#endif // VORONOIGENERATOR_H
