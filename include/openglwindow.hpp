#ifndef OPENGLWINDOW_HPP
#define OPENGLWINDOW_HPP

#include    <QWindow>
#include    <QOpenGLContext>
#include    <QKeyEvent>
#include    <QTime>
#include    <Engine/Core.hpp>
#include    <Generator/generator.hpp>

namespace Editor
{

class HeightMapEvent;
class ModelEvent;

///
/// \brief The OpenGLWindow class, handle openGL context as well as the game loop
///
class OpenGLWindow : public QWindow
{
    Q_OBJECT

public:
    ///
    /// \brief OpenGLWindow default constructor
    /// \param parent is the top window. If set to NULL, the openglwindow exist by itself
    ///
    explicit OpenGLWindow(QWindow *parent = 0);

    ///
    /// \brief Destructor
    ///
    ~OpenGLWindow();

public slots:
    ///
    /// \brief run launch the main loop, which remain active while this window is visible
    ///
    void    run(Engine::Core *engine, gen::Generator *generator);

protected:
    ///
    /// \brief event override, for handle custom events
    /// \param e
    ///
    virtual bool    event(QEvent *e);

    ///
    /// \brief loadModelEvent
    ///
    virtual void    modelAddEvent(ModelEvent *e);

    ///
    /// \brief loadHeightmapEvent
    ///
    virtual void    heightMapAddEvent(HeightMapEvent *e);

    ///
    /// \brief keyPressEvent override, for passing events to the engine
    /// \param e
    ///
    virtual void    keyPressEvent(QKeyEvent *e);

    ///
    /// \brief resizeEvent override, not used
    /// \param event
    ///
    virtual void    resizeEvent(QResizeEvent* event);

    ///
    /// \brief mousePressEvent override, for passing events to the engine
    /// \param event
    ///
    virtual void    mousePressEvent(QMouseEvent *event);

    ///
    /// \brief mouseReleaseEvent override, for passing events to the engine
    /// \param event
    ///
    virtual void    mouseReleaseEvent(QMouseEvent *event);

    ///
    /// \brief keyReleaseEvent override, for passing events to the engine
    /// \param e
    ///
    virtual void    keyReleaseEvent(QKeyEvent *e);

    ///
    /// \brief mouseMoveEvent override, for passing events to the engine
    /// \param event
    ///
    virtual void    mouseMoveEvent(QMouseEvent *event);

private:
    ///
    /// \brief _context handle the opengl context
    ///
    QOpenGLContext m_context;

    ///
    /// \brief _format is the drawable surface of the window, where the engine is rendered
    ///
    QSurfaceFormat m_format;

    ///
    /// \brief _engine is the worldsparticle engine, where the magic happen
    ///
    Engine::Core    *m_engine;
    gen::Generator  *m_generator;

    ///
    /// \brief _mouseTracking is used for handle if the mouse should be hide and centered (fps style)
    ///
    bool           m_mouseTracking;
};

}

#endif // OPENGLWINDOW_HPP
