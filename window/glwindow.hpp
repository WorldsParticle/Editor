#ifndef     __GL_WINDOW_HPP__
#define     __GL_WINDOW_HPP__

#include <QWindow>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_2_Core>
#include <QKeyEvent>
#include <QTime>

#include "GameEngine.hpp"
#include "model.hpp"

class GLWindow : public QWindow
{
    Q_OBJECT
    public:
        explicit GLWindow(QWindow *parent = 0);
        ~GLWindow();

public:
    static QOpenGLContext *context;
    static QSurface      *surface;
    static QOpenGLFunctions_4_2_Core *m_funcs;

    void    start(Model *model);

protected:
    virtual void    keyPressEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeWindow();

private:
        QOpenGLContext _context;
        QSurfaceFormat _format;
        ::WorldParticles::Engine::GameEngine    *  _gEngine;
        bool            _mouseTracking;
};

#endif /* !__GL_WINDOW_HPP__ */
