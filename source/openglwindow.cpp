#include "include/openglwindow.hpp"
#include <Engine/Event/KeyPressed.hpp>
#include <Engine/Event/KeyReleased.hpp>
#include <Engine/Event/Resize.hpp>
#include <Engine/Event/MouseButtonPressed.hpp>
#include <Engine/Event/MouseButtonReleased.hpp>
#include <Engine/Event/MouseMove.hpp>
#include <qdebug.h>
#include <iostream>
#include <qcoreapplication.h>

namespace Editor
{

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

    setTitle("Explorateur");
}


OpenGLWindow::~OpenGLWindow()
{

}

void    OpenGLWindow::run(Engine::Core *engine)
{
    if (!engine)
        return;
    _engine = engine;

    while (isVisible())
    {
        _engine->update();
        _context.makeCurrent(this);
        _engine->render();
        _context.swapBuffers(this);
        _context.doneCurrent();

        QCoreApplication::processEvents();
    }
}

void    OpenGLWindow::keyPressEvent(QKeyEvent *e)
{


    if (e->key() == Qt::Key_Escape)
        exit(1); // à remplacer quand on mettra en place les threads
    else if (e->key() == Qt::Key_Z){
        Engine::Event::KeyPressed  event(Engine::Keyboard::Z);
        _engine->push_event(event);
        e->accept();
    }
    else if (e->key() == Qt::Key_Q){
        Engine::Event::KeyPressed  event(Engine::Keyboard::Q);
        _engine->push_event(event);
        e->accept();
    }
    else if (e->key() == Qt::Key_S){
        Engine::Event::KeyPressed  event(Engine::Keyboard::S);
        _engine->push_event(event);
        e->accept();
    }
    else if (e->key() == Qt::Key_D){
        Engine::Event::KeyPressed  event(Engine::Keyboard::D);
        _engine->push_event(event);
        e->accept();
    }
}

void    OpenGLWindow::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Z){
        Engine::Event::KeyReleased  event(Engine::Keyboard::Z);
        _engine->push_event(event);
        e->accept();
    }
    if (e->key() == Qt::Key_Q){
        Engine::Event::KeyReleased  event(Engine::Keyboard::Q);
        _engine->push_event(event);
        e->accept();
    }
    if (e->key() == Qt::Key_S){
        Engine::Event::KeyReleased  event(Engine::Keyboard::S);
        _engine->push_event(event);
        e->accept();
    }
    if (e->key() == Qt::Key_D){
        Engine::Event::KeyReleased  event(Engine::Keyboard::D);
        _engine->push_event(event);
        e->accept();
    }
}

void    OpenGLWindow::resizeEvent(QResizeEvent* event)
{
    event->accept();
    Engine::Event::Resize  e(glm::vec2(event->size().width(), event->size().height()));
    _engine->push_event(e);
}

void    OpenGLWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Engine::Event::MouseButtonPressed   e(Engine::Mouse::Button::LEFT, glm::vec2(event->pos().x(), event->pos().y()));
        _engine->push_event(e);

        setCursor(Qt::BlankCursor);
        QPoint glob = mapToGlobal(QPoint(width() / 2, height() / 2));
        QCursor::setPos(glob);
        _mouseTracking = true;
    }
    //    else if (event->button() == Qt::RightButton)
    //    {
    //        setCursor(Qt::ArrowCursor);
    //        _mouseTracking = false;
    //    }
}

void    OpenGLWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Engine::Event::MouseButtonReleased  e(Engine::Mouse::Button::LEFT, glm::vec2(event->pos().x(), event->pos().y()));
        _engine->push_event(e);

        setCursor(Qt::ArrowCursor);
        _mouseTracking = false;
    }
}

void    OpenGLWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (_mouseTracking == true)
    {
        qDebug() << "Mouse move";
        Engine::Event::MouseMove  e(Engine::Mouse::Button::LEFT, glm::vec2(event->pos().x(), event->pos().y()));
        _engine->push_event(e);

        QPoint glob = mapToGlobal(QPoint(width() / 2,height() / 2));
        QCursor::setPos(glob);
    }
}

}
