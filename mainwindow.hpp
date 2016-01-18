#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPaintEvent>
#include <QDockWidget>
#include <QHBoxLayout>
#include "openglwindow.hpp"
#include "toolwidget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

    virtual void    keyPressEvent(QKeyEvent *e);
    virtual void    paintEvent(QPaintEvent *e);
    virtual void    closeEvent(QCloseEvent *e);

private:
    void            dockGlWindow();

    Ui::MainWindow  *_ui;
    OpenGLWindow    _glWindow;
    ToolWidget      _toolWidget;
    QWidget         *_docker;
    QHBoxLayout     _centralLayout;
};

#endif // MAINWINDOW_HPP
