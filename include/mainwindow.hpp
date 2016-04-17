#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPaintEvent>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QGraphicsView>  // Will use a heritate class after
#include <QGraphicsScene> // Same
#include "openglwindow.hpp"
#include <Engine/Core.hpp>

namespace Ui {
class MainWindow;
}

namespace Editor
{

class ToolWidget;

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

    ///
    /// \brief engine getter
    /// \return _engine
    ///
    inline Engine::Core     &engine()
    { return _engine; }

    ///
    /// \brief _mapScene getter
    /// \return _mapScene
    ///
    inline QGraphicsScene   &mapScene()
    { return _mapScene; }

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
    /// \brief _ui contain some ui elements which are defined in mainwindow.ui
    ///
    Ui::MainWindow  *_ui;

    ///
    /// \brief _glWindow is the OpenGLWindow, which create an openGL context for the engine rendering
    ///
    OpenGLWindow    _glWindow;

    ///
    /// \brief _toolWidget is a widget which enable user to interact with the engine
    ///
    ToolWidget      *_toolWidget;

    ///
    /// \brief _glView is a widget used for docking the _glWindow
    ///
    QWidget         *_glView;

    ///
    /// \brief _centralLayout is the main layout of the window, linked to the central widget, containing the _docker and _toolWidget.
    ///
    QHBoxLayout     _centralLayout;

    ///
    /// \brief _engine is the worldsparticle engine, where the magic happen.
    /// It must be instaciated after the openglcontext (here _glwindow)
    ///
    Engine::Core   _engine;

    ///
    /// \brief _mapView is the widget which act as a view on the mapScene
    /// Will use a custom class after
    ///
    QGraphicsView  *_mapView;

    ///
    /// \brief _mapScene is a simple scene containing graphics 2D map elements
    /// Will use a custom class after
    ///
    QGraphicsScene _mapScene;
};

}

#endif // MAINWINDOW_HPP
