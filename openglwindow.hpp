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
    void            resizeEvent(QResizeEvent* event);
    void            mousePressEvent(QMouseEvent *event);
    void            keyReleaseEvent(QKeyEvent *e);
    void            mouseMoveEvent(QMouseEvent *event);

private:
        QOpenGLContext _context;
        QSurfaceFormat _format;
        Engine::Core   *_engine;

        bool           _mouseTracking;
};

#endif // OPENGLWINDOW_HPP
