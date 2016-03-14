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
/// todo : change right/left to prev/next ?
class Parabola
{
public:

    static int  indexMax;  // change this
    const int   index;

    /*
        isLeaf		: flag whether the node is Leaf or internal node
        site		: pointer to the focus point of parabola (when it is parabola)
        corner		: pointer to the corner
        cEvent		: pointer to the event, when the arch disappears (circle event) // rework this
        parent		: pointer to the parent node in tree
    */

    bool		isLeaf;
    Site        *site;

    // when not leaf
    CrossedEdge *edge;
    Point       corner;
    Point       direction;

    QedEvent    *cEvent;
    Parabola    *parent;

    /*
        Constructors of the class (empty for edge, with focus parameter for an arch).
    */

    Parabola	();
    Parabola	(Site *s);
    ~Parabola   ();

    inline friend std::ostream &operator<<(std::ostream &os, const Parabola &p)
    { return os << "isLeaf[" << p.isLeaf << "] index[" << p.index << "]"; }

    /*
        Access to the children (in tree).
    */

    inline void setLeft (Parabola * p) {_left  = p; p->parent = this;}
    inline void setRight(Parabola * p) {_right = p; p->parent = this;}

    Parabola    *left () { return _left;  }
    Parabola    *right() { return _right; }

    /*
        Some useful tree operations  // why static ?

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
