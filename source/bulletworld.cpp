#include "include/bulletworld.h"

BulletWorld::BulletWorld() :
    _world(NULL),
    _dispatcher(NULL),
    _collisionConfig(NULL),
    _broadphase(NULL),
    _solver(NULL),
    _quad(NULL),
    _rigidBodies()
{
    init();
}

BulletWorld::~BulletWorld()
{
    foreach (btRigidBody *b, _rigidBodies)
    {
        _world->removeCollisionObject(b);
        btMotionState* motionState=b->getMotionState();
        btCollisionShape* shape=b->getCollisionShape();
        delete b;
        delete shape;
        delete motionState;
    }
    delete _dispatcher;
    delete _collisionConfig;
    delete _solver;
    delete _broadphase;
    delete _world;
    gluDeleteQuadric(_quad);
}

void    BulletWorld::init()
{
    _quad = gluNewQuadric();

    _collisionConfig = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collisionConfig);
    _broadphase = new btDbvtBroadphase();
    _solver = new btSequentialImpulseConstraintSolver();
    _world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfig);

    _world->setGravity(btVector3(0, -10, 0));
}

void    BulletWorld::update()
{
    _world->stepSimulation(1/60.);
}

void    BulletWorld::render()
{
    foreach (btRigidBody *b, _rigidBodies)
    {
        if(b->getCollisionShape()->getShapeType()==STATIC_PLANE_PROXYTYPE)
            renderPlan(b);
        else if(b->getCollisionShape()->getShapeType()==SPHERE_SHAPE_PROXYTYPE)
            renderSphere(b);
    }
}

btRigidBody *BulletWorld::addPlan(float size, float x, float y, float z, float mass)
{
    btTransform     t;
    t.setIdentity();
    t.setOrigin(btVector3(0, 0, 0));
    btStaticPlaneShape   *plan = new btStaticPlaneShape(btVector3(x, y, z), size);

    btMotionState   *motion = new btDefaultMotionState(t);
    btRigidBody     *body = new btRigidBody(mass, motion, plan);
    _world->addRigidBody(body);
    _rigidBodies.push_back(body);
    return body;
}

btRigidBody *BulletWorld::addSphere(float rad, float x, float y, float z, float mass)
{
    btTransform     t;
    t.setIdentity();
    t.setOrigin(btVector3(x, y, z));
    btSphereShape   *sphere = new btSphereShape(rad);

    //btVector3       inertia(0, 0, 0);                   //
    //if (mass)                                           // Pas sûr de l'utilitée de cette partie
    //    sphere->calculateLocalInertia(mass, inertia);   //

    btMotionState   *motion = new btDefaultMotionState(t);
    btRigidBody     *body = new btRigidBody(mass, motion, sphere);
    _world->addRigidBody(body);
    _rigidBodies.push_back(body);
    return body;
}

void        BulletWorld::renderSphere(btRigidBody *sphere)
{
    glColor3f(1, 0, 0); // red
    float r = ((btSphereShape*)sphere->getCollisionShape())->getRadius();
    btTransform t;
    sphere->getMotionState()->getWorldTransform(t);
    float m[16];
    t.getOpenGLMatrix(m);

    glPushMatrix();
    glMultMatrixf(m);
    gluSphere(_quad, r, 20, 20);
    glPopMatrix();
}

void        BulletWorld::renderPlan(btRigidBody *plan)
{
    glColor3f(0.8, 0.8, 0.8); // gris clair
    btTransform t;
    plan->getMotionState()->getWorldTransform(t);
    float m[16];
    t.getOpenGLMatrix(m);

    glPushMatrix();
    glMultMatrixf(m);
    glBegin(GL_QUADS);
    glVertex3f(-1000, 0, 1000);
    glVertex3f(-1000, 0, -1000);
    glVertex3f(1000, 0, -1000);
    glVertex3f(1000, 0, 1000);
    glEnd();
    glPopMatrix();
}
