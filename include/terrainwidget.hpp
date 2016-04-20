#ifndef TERRAINWIDGET_H
#define TERRAINWIDGET_H

#include <QWidget>
#include "mainwindow.hpp"

namespace Ui {
class TerrainWidget;
}

namespace Editor
{

class TerrainWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief terrainWidget constructor
    /// \param mainWindow
    ///
    explicit TerrainWidget(MainWindow &mainWindow);

    ///
    /// \brief destructor
    ///
    ~TerrainWidget();

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
    Ui::TerrainWidget *m_ui;

    ///
    /// \brief m_mainWindow
    ///
    MainWindow        &m_mainWindow;
};

}

#endif // TERRAINWIDGET_H
