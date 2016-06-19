#include "include/openglwindow.hpp"
#include "include/event/heightmapevent.hpp"
#include "include/event/modelevent.hpp"

#include <Engine/Event/KeyPressed.hpp>
#include <Engine/Event/KeyReleased.hpp>
#include <Engine/Event/Resize.hpp>
#include <Engine/Event/MouseButtonPressed.hpp>
#include <Engine/Event/MouseButtonReleased.hpp>
#include <Engine/Event/MouseMove.hpp>
#include <Engine/Core/Terrain.hpp>
#include <Engine/Core/Scene.hpp>

#include <qdebug.h>
#include <iostream>
#include <qcoreapplication.h>


namespace Editor
{

OpenGLWindow::OpenGLWindow(QWindow *parent) :
    QWindow(parent),
    m_context(this),
    m_format(),
    m_engine(NULL),
    m_mouseTracking(false)
{
    setSurfaceType(OpenGLSurface);

    m_format.setMajorVersion(4);
    m_format.setMinorVersion(2);
    m_format.setProfile(QSurfaceFormat::CoreProfile); //whatever this is
    m_format.setOption(QSurfaceFormat::DebugContext);

    this->setFormat(m_format);
    m_context.setFormat(m_format);

    create();
    m_context.create();

    resize(1024, 768);

    if(!m_context.isValid())
        qDebug() << "OpenGL context invalid !";

    m_context.makeCurrent(this);

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
    m_engine = engine;
    //_engine->load("test3.dae");


    //Load scene
    //m_engine->load("/home/marie/project/WorldsParticleMaster/Engine/resources/scenes/empty.dae");
//    m_engine->load("/home/marie/project/WorldsParticleMaster/Engine/resources/models/lowpolytree.obj");
//    m_engine->load("/home/marie/project/WorldsParticleMaster/Engine/resources/scenes/altair.dae");
//    m_engine->load("/home/marie/project/WorldsParticleMaster/Engine/resources/models/tree.DAE");
    m_engine->load("C:/Users/louis/Documents/GitHub/Engine/resources/models/tree.dae");

    //Gen scene
    Engine::Scene * scene = m_engine->scenes().front();
    map::MapGraph *map = new map::MapGraph(500,500);
    gen::Generator m_generator;
    m_generator.run(map);

    //Add terrain
    new Engine::Terrain(map->heightMap(), scene, scene->getShaderPrograms());

    //Add models
//    scene->addModels();
    //TODO: faire un event pour ca

    while (isVisible())
    {
        m_engine->update();
        m_context.makeCurrent(this);
        m_engine->render();
        m_context.swapBuffers(this);
        QCoreApplication::processEvents();
        m_context.doneCurrent();
    }
}

bool    OpenGLWindow::event(QEvent *e)
{
    if (e->type() == ModelEvent::Model_add)
    {
        modelAddEvent(dynamic_cast<ModelEvent *>(e));
        return true;
    }
    else if (e->type() == HeightMapEvent::HeightMap_add)
    {
        heightMapAddEvent(dynamic_cast<HeightMapEvent *>(e));
        return true;
    }
    return QWindow::event(e);
}

void    OpenGLWindow::modelAddEvent(ModelEvent *e)
{
    if (m_engine)
        m_engine->load(e->path().toStdString());
}

void    OpenGLWindow::heightMapAddEvent(HeightMapEvent *e)
{
    if (m_engine && m_engine->scenes().size())
    {
        Engine::Scene   *scene = m_engine->scenes().front();
        scene->add(new Engine::Terrain(e->heightMap(), scene, scene->getShaderPrograms()));
    }
}

void    OpenGLWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        exit(1); // à remplacer quand on mettra en place les threads
    else if (e->key() == Qt::Key_Z){
        Engine::Event::KeyPressed  event(Engine::Keyboard::Z);
        m_engine->push_event(event);
        e->accept();
    }
    else if (e->key() == Qt::Key_W){
        Engine::Event::KeyPressed  event(Engine::Keyboard::Z);
        m_engine->push_event(event);
        e->accept();
    }
    else if (e->key() == Qt::Key_A){
        Engine::Event::KeyPressed  event(Engine::Keyboard::Q);
        m_engine->push_event(event);
        e->accept();
    }
    else if (e->key() == Qt::Key_Q){
        Engine::Event::KeyPressed  event(Engine::Keyboard::Q);
        m_engine->push_event(event);
        e->accept();
    }
    else if (e->key() == Qt::Key_S){
        Engine::Event::KeyPressed  event(Engine::Keyboard::S);
        m_engine->push_event(event);
        e->accept();
    }
    else if (e->key() == Qt::Key_D){
        Engine::Event::KeyPressed  event(Engine::Keyboard::D);
        m_engine->push_event(event);
        e->accept();
    }
}

void    OpenGLWindow::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_W){
        Engine::Event::KeyReleased  event(Engine::Keyboard::Z);
        m_engine->push_event(event);
        e->accept();
    }
    if (e->key() == Qt::Key_Z){
        Engine::Event::KeyReleased  event(Engine::Keyboard::Z);
        m_engine->push_event(event);
        e->accept();
    }
    if (e->key() == Qt::Key_A){
        Engine::Event::KeyReleased  event(Engine::Keyboard::Q);
        m_engine->push_event(event);
        e->accept();
    }
    if (e->key() == Qt::Key_Q){
        Engine::Event::KeyReleased  event(Engine::Keyboard::Q);
        m_engine->push_event(event);
        e->accept();
    }
    if (e->key() == Qt::Key_S){
        Engine::Event::KeyReleased  event(Engine::Keyboard::S);
        m_engine->push_event(event);
        e->accept();
    }
    if (e->key() == Qt::Key_D){
        Engine::Event::KeyReleased  event(Engine::Keyboard::D);
        m_engine->push_event(event);
        e->accept();
    }
}

void    OpenGLWindow::resizeEvent(QResizeEvent* event)
{
    event->accept();
    Engine::Event::Resize  e(glm::vec2(event->size().width(), event->size().height()));
    m_engine->push_event(e);
}

void    OpenGLWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Engine::Event::MouseButtonPressed   e(Engine::Mouse::Button::LEFT, glm::vec2(event->pos().x(), event->pos().y()));
        m_engine->push_event(e);

        setCursor(Qt::BlankCursor);
        QPoint glob = mapToGlobal(QPoint(width() / 2, height() / 2));
        QCursor::setPos(glob);
        m_mouseTracking = true;
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
        m_engine->push_event(e);

        setCursor(Qt::ArrowCursor);
        m_mouseTracking = false;
    }
}

void    OpenGLWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mouseTracking == true)
    {
//        qDebug() << "Mouse move";
        Engine::Event::MouseMove  e(Engine::Mouse::Button::LEFT, glm::vec2(event->pos().x(), event->pos().y()));
        m_engine->push_event(e);

        QPoint glob = mapToGlobal(QPoint(width() / 2,height() / 2));
        QCursor::setPos(glob);
    }
}

}
