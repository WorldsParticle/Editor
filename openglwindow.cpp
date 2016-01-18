#include "openglwindow.hpp"
#include <qdebug.h>
#include <iostream>
#include <qcoreapplication.h>

OpenGLWindow::OpenGLWindow(QWindow *parent) :
    QWindow(parent),
    _context(this),
    _format(),
    _engine(NULL),
    _mouseTracking(false)
{
    setSurfaceType(OpenGLSurface);

    _format.setMajorVersion(4);
    _format.setMinorVersion(2);
    _format.setProfile(QSurfaceFormat::CoreProfile); //whatever this is
    _format.setOption(QSurfaceFormat::DebugContext);

    this->setFormat(_format);
    _context.setFormat(_format);

    create();
    _context.create();

    resize(1024, 768);

    if(!_context.isValid())
        qDebug() << "OpenGL context invalid !";

    _context.makeCurrent(this);

    qDebug()    << "OpenGL version : "
                << this->format().majorVersion() << "."
                << this->format().minorVersion();

    _engine = new Engine::Core();

    setTitle("Explorateur");
}


OpenGLWindow::~OpenGLWindow()
{
    delete _engine;
}

void    OpenGLWindow::run(void)
{
    while (isVisible())
    {
        _engine->update();
        _context.makeCurrent(this);
        _engine->render();
        _context.swapBuffers(this);
        _context.doneCurrent();

        QCoreApplication::processEvents();
    }
    qDebug() << "hya";
}

void    OpenGLWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat())
        return;

    e->accept();

    if (e->key() == Qt::Key_Escape)
        exit(1); // à remplacer quand on mettra en place les threads
    else if (e->key() == Qt::Key_Z){
    }
    else if (e->key() == Qt::Key_Q){
    }
    else if (e->key() == Qt::Key_S){
    }
    else if (e->key() == Qt::Key_D){
    }
}

void    OpenGLWindow::keyReleaseEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat())
        return;

    e->accept();

    if (e->key() == Qt::Key_Z){
    }
    if (e->key() == Qt::Key_Q){
    }
    if (e->key() == Qt::Key_S){
    }
    if (e->key() == Qt::Key_D){
    }
}

void    OpenGLWindow::resizeEvent(QResizeEvent* event)
{

   // GLWindow::resizeEvent(event);
}

void    OpenGLWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        setCursor(Qt::BlankCursor);
        QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
        QCursor::setPos(glob);
        _mouseTracking = true;
    }
    else if (event->button() == Qt::RightButton){
    setCursor(Qt::ArrowCursor);
    _mouseTracking = false;
    }
}

void    OpenGLWindow::mouseMoveEvent(QMouseEvent *event){
    if (_mouseTracking)
    {
        QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
        QCursor::setPos(glob);
    }
}
