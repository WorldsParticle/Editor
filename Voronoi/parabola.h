//
// https://drive.google.com/file/d/0B6oy2F9QV_YGcy1ibUN2R0poWmM/view -> VParabola.h
// transformed for our need
//


#ifndef PARABOLA_H
#define PARABOLA_H

#include "graph.h"

class QedEvent;

///
/// \brief The Parabola class
/// keep in mind that sweepline is going down (horizontal beachline)
class Parabola
{
public:

    /*
        isLeaf		: flag whether the node is Leaf or internal node
        site		: pointer to the focus point of parabola (when it is parabola)
        edge		: pointer to the edge (when it is an edge)
        cEvent		: pointer to the event, when the arch disappears (circle event)
        parent		: pointer to the parent node in tree
    */

    bool		isLeaf;
    Site        *site;
    CrossedEdge *edge;
    QedEvent *cEvent;
    Parabola    *parent;

    /*
        Constructors of the class (empty for edge, with focus parameter for an arch).
    */

    Parabola	();
    Parabola	(Site *s);

    /*
        Access to the children (in tree).
    */

    inline void setLeft (Parabola * p) {_left  = p; p->parent = this;}
    inline void setRight(Parabola * p) {_right = p; p->parent = this;}

    Parabola    *left () { return _left;  }
    Parabola    *right() { return _right; }

    /*
        Some useful tree operations

        GetLeft			: returns the closest left leave of the tree
        GetRight		: returns the closest right leafe of the tree
        GetLeftParent	: returns the closest parent which is on the left
        GetLeftParent	: returns the closest parent which is on the right
        GetLeftChild	: returns the closest leave which is on the left of current node
        GetRightChild	: returns the closest leave which is on the right of current node
    */

    static Parabola * getLeft			(Parabola * p);
    static Parabola * getRight			(Parabola * p);
    static Parabola * getLeftParent     (Parabola * p);
    static Parabola * getRightParent	(Parabola * p);
    static Parabola * getLeftChild		(Parabola * p);
    static Parabola * getRightChild     (Parabola * p);

private:

    Parabola * _left;
    Parabola * _right;
};

#endif // PARABOLA_H
