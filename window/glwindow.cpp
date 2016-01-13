#include "glwindow.hpp"
#include <QPushButton>
#include <QGridLayout>
#include <QCoreApplication>
#include "GameEngine.hpp"

#include <log4cpp/Category.hh>
#include    <QOpenGLDebugLogger>

QSurface        *GLWindow::surface = NULL;
QOpenGLContext      *GLWindow::context = NULL;
QOpenGLFunctions_4_2_Core *GLWindow::m_funcs = NULL;

GLWindow::GLWindow(QWindow *parent) :
    QWindow(parent),
    _context(this),
    _format()
{
    log4cpp::Category& root = log4cpp::Category::getRoot();
    setSurfaceType(OpenGLSurface);

    _format.setMajorVersion(4);
    _format.setMinorVersion(2);
    _format.setProfile(QSurfaceFormat::CoreProfile); //whatever this is
    _format.setOption(QSurfaceFormat::DebugContext);

    _mouseTracking = false;

    this->setFormat(_format);
    _context.setFormat(_format);

    create();
    _context.create();


    GLWindow::context = &_context;
    GLWindow::surface = this;

    resize(1024, 768);

    if(!_context.isValid())
    {
        root << log4cpp::Priority::ERROR << "OpenGL context invalid !";
    }

    _context.makeCurrent(this);
    m_funcs = (QOpenGLFunctions_4_2_Core *)_context.versionFunctions();

    m_funcs->initializeOpenGLFunctions();

    root << log4cpp::Priority::ERROR
        << "OpenGL version : "
        << this->format().majorVersion() << "." << this->format().minorVersion();

/*    GLuint VertexArrayID;*/
    //m_funcs->glGenVertexArrays(1, &VertexArrayID);
    /*m_funcs->glBindVertexArray(VertexArrayID);*/

}


GLWindow::~GLWindow()
{

}

void    GLWindow::start(Model *model)
{
    ::WorldParticles::Engine::GameEngine     _gameEngine;

    _gEngine = &(_gameEngine);
    _gameEngine.load(RESOURCES_PATH "/scenes/altair/altair.dae");
    //::WorldParticles::Engine::GameClock::start();
    resizeWindow();
    while (isVisible())
    {
        _gameEngine.update();
        //::WorldParticles::Engine::GameClock::restart();
        _context.makeCurrent(this);
        _gameEngine.render();
        _context.swapBuffers(this);
        _context.doneCurrent();

        QCoreApplication::processEvents();
    }
}

void    GLWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat())
        return;
    static bool scr = false; // Miroir, miroir, qui est la plus belle des horreurs dans ce code ?
    e->accept();

    if (e->key() == Qt::Key_Escape)
        exit(1);
    else if (e->key() == Qt::Key_A) {
        if (scr == false) {
            showMaximized();
            scr = true;
        }
        else {
            showNormal();
            scr = false;
        }
        resizeWindow();
    }
    else if (e->key() == Qt::Key_Z){
    }
    else if (e->key() == Qt::Key_Q){
    }
    else if (e->key() == Qt::Key_S){
    }
    else if (e->key() == Qt::Key_D){
    }
}

void    GLWindow::keyReleaseEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat())
        return;
    if (e->key() == Qt::Key_Z){
    }
    if (e->key() == Qt::Key_Q){
    }
    if (e->key() == Qt::Key_S){
    }
    if (e->key() == Qt::Key_D){
    }
}

void GLWindow::resizeEvent(QResizeEvent* event)
{

   // GLWindow::resizeEvent(event);
    resizeWindow();
}

void GLWindow::mousePressEvent(QMouseEvent *event)
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

void GLWindow::mouseMoveEvent(QMouseEvent *event){
    if (_mouseTracking)
    {
        QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
        QCursor::setPos(glob);
    }
}

void GLWindow::resizeWindow()
{
}
