#ifndef HALFEDGE_H
#define HALFEDGE_H

namespace MAP
{

class Zone;
class CrossedEdge;
class Corner;

///
/// \brief The halfEdge class
/// see the wikipedia link for more details (doubly connected edge list)
/// \todo index as the other ?
///
class HalfEdge
{
    CrossedEdge *edge; // here represent the Voronoi one
    Zone        *center;

    Corner      *origin;       // maybe use _edge.v0/v1 instead, if able to keep track of direction
    Corner      *destination;  // maybe use _edge.v1/v0 instead, if able to keep track of direction

    HalfEdge    *prev;
    HalfEdge    *next;
    HalfEdge    *twin;
};

}

#endif // HALFEDGE_H
