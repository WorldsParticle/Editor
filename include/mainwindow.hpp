#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPaintEvent>
#include <QDockWidget>
#include <QHBoxLayout>
#include "openglwindow.hpp"
#include "toolwidget.hpp"
#include <Engine/Core.hpp>

namespace Ui {
class MainWindow;
}

namespace Editor
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief MainWindow default constructor
    /// \param parent is the top widget. If set to NULL, the mainwindow exist by itself
    ///
    explicit MainWindow(QWidget *parent = 0);

    ///
    /// \brief Destructor
    ///
    ~MainWindow();

protected:
    ///
    /// \brief keyPressEvent override, make esc a shortcut
    /// \param e
    ///
    virtual void    keyPressEvent(QKeyEvent *e);

    ///
    /// \brief paintEvent override, paint a background
    /// \param e
    ///
    virtual void    paintEvent(QPaintEvent *e);

    ///
    /// \brief closeEvent override, for an awfull exit(1) : have to fix that
    /// \param e
    ///
    virtual void    closeEvent(QCloseEvent *e);

private:
    ///
    /// \brief dockGlWindow dock the _glWindow to the _centralLayout
    ///
    void            dockGlWindow();

    ///
    /// \brief _ui contain some ui elements wich are defined in mainwindow.ui
    ///
    Ui::MainWindow  *_ui;

    ///
    /// \brief _glWindow is the OpenGLWindow, wich create an openGL context for the engine rendering
    ///
    OpenGLWindow    _glWindow;

    ///
    /// \brief _toolWidget is a widget wich enable user to interact wich the engine
    ///
    ToolWidget      _toolWidget;

    ///
    /// \brief _docker is a widget used for docking the _glWindow
    ///
    QWidget         *_docker;

    ///
    /// \brief _centralLayout is the main layout of the window, linked to the central widget, containing the _docker and _toolWidget.
    ///
    QHBoxLayout     _centralLayout;

    ///
    /// \brief _engine is the worldsparticle engine, where the magic happen.
    /// It must be instaciated after the openglcontext (here _glwindow)
    ///
    Engine::Core   _engine;
};

}

#endif // MAINWINDOW_HPP
