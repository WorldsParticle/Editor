#ifndef OPENGLWINDOW_HPP
#define OPENGLWINDOW_HPP

#include    <QWindow>
#include    <GL/glew.h>
#include    <QOpenGLContext>
#include    <QKeyEvent>
#include    <QTime>
#include    <Engine/Core.hpp>

class OpenGLWindow : public QWindow
{
    Q_OBJECT
public:
        explicit OpenGLWindow(QWindow *parent = 0);
        ~OpenGLWindow();

public slots:
    void    run();

protected:
    virtual void    keyPressEvent(QKeyEvent *e);
    virtual void    resizeEvent(QResizeEvent* event);
    virtual void    mousePressEvent(QMouseEvent *event);
    virtual void    keyReleaseEvent(QKeyEvent *e);
    virtual void    mouseMoveEvent(QMouseEvent *event);

private:
        QOpenGLContext _context;
        QSurfaceFormat _format;
        Engine::Core   *_engine;

        bool           _mouseTracking;
};

#endif // OPENGLWINDOW_HPP
