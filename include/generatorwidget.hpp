#ifndef TERRAINWIDGET_H
#define TERRAINWIDGET_H

#include <QWidget>
#include "mainwindow.hpp"

namespace Ui {
class GeneratorWidget;
}

namespace Editor
{

class GeneratorWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief terrainWidget constructor
    /// \param mainWindow
    ///
    explicit GeneratorWidget(MainWindow &mainWindow);

    ///
    /// \brief assignGenerator
    ///
    void    assignGenerator(gen::Generator *generator);

    ///
    /// \brief destructor
    ///
    ~GeneratorWidget();

public slots:
    ///
    /// \brief launchGenerator
    ///
    void    launchGenerator();

private:
    ///
    /// \brief addMapTo2DScene will be removed in a custom graphicsScene class
    /// \param map
    ///
    void    addMapTo2DScene(map::MapGraph &map);

    ///
    /// \brief m_ui contain ui base elements
    ///
    Ui::GeneratorWidget *m_ui;

    ///
    /// \brief m_mainWindow, temporaire
    ///
    MainWindow          &m_mainWindow;

    gen::Generator      *m_generator;
};

}

#endif // TERRAINWIDGET_H
