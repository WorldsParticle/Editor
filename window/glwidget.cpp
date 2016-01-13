#include "glwidget.hpp"
//#include "graphic/fire.h"

#define MS_TICK 30

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    _timer(),
    _point(0, 0, 0),
    _elapsedTime(0)
{
    //Fire::initialize();

    connect(&_timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    _timer.start(MS_TICK);
}

void    GLWidget::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void    GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(_point.x() / 16.0, 1.0, 0.0, 0.0);
    glRotatef(_point.y() / 16.0, 0.0, 1.0, 0.0);
    glRotatef(_point.z() / 16.0, 0.0, 0.0, 1.0);

    draw();
}

void    GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void    GLWidget::draw()
{
    qglColor(Qt::red);
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glVertex3f(-1,-1,0);
    glVertex3f(-1,1,0);
    glVertex3f(1,1,0);
    glVertex3f(1,-1,0);

    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0,-1,0.707);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);
    glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(1,0, 0.707);
    glVertex3f(1,-1,0);
    glVertex3f(1,1,0);
    glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0,1,0.707);
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,0,0.707);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(0,0,1.2);
    glEnd();

    //drawFire();
}

void    GLWidget::updateAnimation()
{
    _point.setX(_point.x() + 20);
    _point.setY(_point.y() + 20);
    _point.setZ(_point.z() + 20);

    _elapsedTime += MS_TICK;

    update();
}
/*
void		GLWidget::drawFire()
{
  Fire::drawAppear(Vec3D(-1, -2, 0),
           Vec3D(1, -2, 0),
           Vec3D(0, 0, 2),
           _elapsedTime / 1000.);
}*/
