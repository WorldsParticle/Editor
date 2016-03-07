#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "voronoigenerator.h"
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
    Ui::MainWindow      *_ui;
    VoronoiGenerator    _generator;

    QGraphicsScene      _scene;
};

#endif // MAINWINDOW_H
