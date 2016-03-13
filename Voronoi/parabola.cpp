#include "parabola.h"

/*
    Constructors
*/

int Parabola::indexMax = 0;

Parabola::Parabola() :
    index(indexMax)
{
    ++indexMax;

    site	= 0;
    isLeaf	= false;
    cEvent	= 0;
    edge	= 0;
    parent	= 0;

    _left = NULL;
    _right = NULL;
}

Parabola::Parabola(Site * s) :
    index(indexMax)
{
    ++indexMax;

    site	= s;
    isLeaf	= true;
    cEvent	= 0;
    edge	= 0;
    parent	= 0;

    _left = NULL;
    _right = NULL;
}

/*
    Tree operations (described in the header file)
*/

Parabola * Parabola::getLeft			(Parabola * p)
{
    return getLeftChild(getLeftParent(p));
}


Parabola * Parabola::getRight			(Parabola * p)
{
    return getRightChild(getRightParent(p));
}

Parabola * Parabola::getLeftParent	(Parabola * p)
{
    Parabola * par		= p->parent;
    Parabola * pLast	= p;
    while(par->left() == pLast)
    {
        if(!par->parent) return 0;
        pLast = par;
        par = par->parent;
    }
    return par;
}

Parabola * Parabola::getRightParent	(Parabola * p)
{
    Parabola * par		= p->parent;
    Parabola * pLast	= p;
    while(par->right() == pLast)
    {
        if(!par->parent) return 0;
        pLast = par; par = par->parent;
    }
    return par;
}

Parabola * Parabola::getLeftChild		(Parabola * p)
{
    if(!p) return 0;
    Parabola * par = p->left();
    while(par && !par->isLeaf)
        par = par->right();
    return par;
}

Parabola * Parabola::getRightChild	(Parabola * p)
{
    if(!p) return 0;
    Parabola * par = p->right();
    while(par && !par->isLeaf)
        par = par->left();
    return par;
}
