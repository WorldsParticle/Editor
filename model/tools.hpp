#ifndef     __TOOLS_HPP__
#define     __TOOLS_HPP__

#include <QString>
#include <QVector3D>
#include <QList>
#include <QMap>
#include <QGraphicsScene>
#include <math.h>

typedef QGraphicsScene              Scene; // c'est la ou il faut mettre la scene du moteur... en attendant je part sur une QScene ou un GLScene
typedef QString                     String; // a changer sans doute si on décide de faire du pur c++ ailleurs que dans l'interface
typedef QVector3D                   Vec3D;
template<typename T>
using List =                        QList<T>;
template<typename Key, typename T>
using Map =                         QMap<Key, T>;

struct Point3D // useless pour le moment, il faudra federer les vec3D sous une seul bannière !
{
    float x;
    float y;
    float z;
};

#endif /* !__TOOLS_HPP__ */
