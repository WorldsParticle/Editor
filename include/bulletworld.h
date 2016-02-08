#ifndef BULLETWORLD_H
#define BULLETWORLD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <btBulletDynamicsCommon.h>
#include <QVector>

///
/// \brief The BulletWorld class
/// https://www.youtube.com/watch?v=1CEI2pOym1Y  [CTRL-V]
///
class BulletWorld
{
public:
    BulletWorld();
    ~BulletWorld();

    void    init();
    void    update();
    void    render();

    btRigidBody *addPlan(float size, float x, float y, float z, float mass); // origine {0|0|0}
    btRigidBody *addSphere(float rad, float x, float y, float z, float mass);

private:
    void    renderSphere(btRigidBody *sphere); // je re-check pas si c'en est bien une, gaff
    void    renderPlan(btRigidBody *plan); // idem

    btDynamicsWorld             *_world;
    btDispatcher                *_dispatcher;
    btCollisionConfiguration    *_collisionConfig;
    btBroadphaseInterface       *_broadphase;
    btConstraintSolver          *_solver;

    GLUquadricObj               *_quad; // Pas encore saisi l'utilité
    QVector<btRigidBody *>      _rigidBodies;
};

#endif // BULLETWORLD_H
