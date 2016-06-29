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
#include <Generator/generator.hpp>

namespace Ui {
class MainWindow;
}

namespace Editor
{

class ToolTabWidget;
class GeneratorWidget;
class ModelWidget;
class ClimateWidget;

///
/// \brief The MainWindow class, contains the model and some basic ui
///
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
    ///
    inline Engine::Core     &engine()
    { return m_engine; }

    inline gen::Generator   &generator()
    { return m_generator; }

    ///
    /// \brief mapScene getter
    ///
    inline QGraphicsScene   &mapScene()
    { return m_mapScene; }

    ///
    /// \brief terrainWidget getter
    ///
    inline GeneratorWidget    *terrainWidget()
    { return m_generatorWidget; }

    ///
    /// \brief modelWidget getter
    ///
    inline ModelWidget      *modelWidget()
    { return m_modelWidget; }

    ///
    /// \brief climateWidget getter
    ///
    inline ClimateWidget   *climateWidget()
    { return m_climateWidget; }

    inline OpenGLWindow     &glWindow()
    { return m_glWindow; }

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
    /// \brief initializeCustomUi instanciate custom ui class, and construct the final interface
    /// should be called only during construction
    ///
    void    initializeCustomUi();

    ///
    /// \brief makeConnections open the signal / slots connections
    ///
    void    makeConnections();
    ///
    /// \brief m_ui contain some ui elements which are defined in mainwindow.ui
    ///
    Ui::MainWindow  *m_ui;

    ///
    /// \brief m_glWindow is the OpenGLWindow, which create an openGL context for the engine rendering
    ///
    OpenGLWindow    m_glWindow;

    ///
    /// \brief m_toolWidget is a widget which regroup user tools (don't instanciate it before user tools)
    ///
    ToolTabWidget      *m_toolTabWidget;

    ///
    /// \brief m_terrainWidget allow user to interact with the terrain generation
    ///
    GeneratorWidget       *m_generatorWidget;

    ///
    /// \brief m_modelWidget allow user to interact with the scene graph
    ///
    ModelWidget         *m_modelWidget;

    ///
    /// \brief m_climateWidget allow user to interact with the particle generator
    ///
    ClimateWidget      *m_climateWidget;


    ///
    /// \brief m_glView is a widget used for docking the _glWindow
    ///
    QWidget         *m_glView;

    ///
    /// \brief m_centralLayout is the main layout of the window, linked to the central widget, containing the _docker and _toolWidget.
    ///
    QHBoxLayout     m_centralLayout;

    ///
    /// \brief m_engine is the worldsparticle engine, where the magic happen.
    /// It must be instaciated after the openglcontext (here _glwindow)
    ///
    Engine::Core   m_engine;

    ///
    /// \brief m_generator is the generator which will generate the heightmap
    ///
    gen::Generator m_generator;

    ///
    /// \brief m_mapView is the widget which act as a view on the mapScene
    /// Will use a custom class after
    ///
    QGraphicsView  *m_mapView;

    ///
    /// \brief m_mapScene is a simple scene containing graphics 2D map elements
    /// Will use a custom class after
    ///
    QGraphicsScene m_mapScene;
};

}

#endif // MAINWINDOW_HPP
