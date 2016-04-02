#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "generator.hpp"
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void generate();

private:
    void    addSceneItems(MAP::Map *map);
    void    addZonePolygons(MAP::Map *map);

    Ui::MainWindow      *_ui;
    GEN::Generator      *_generator;

    QGraphicsScene      _scene;
};

#endif // MAINWINDOW_H
