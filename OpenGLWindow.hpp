#ifndef OPENGLWINDOW_HPP
#define OPENGLWINDOW_HPP

#include    <QWidget>
#include    <Engine/Core.hpp>

class OpenGLWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OpenGLWindow(QWidget *parent = 0);

    void    run(void);

private:
    Engine::Core    engine;
};

#endif // OPENGLWINDOW_HPP
