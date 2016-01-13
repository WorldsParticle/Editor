#ifndef     __MAINWINDOW_HPP__
#define     __MAINWINDOW_HPP__

#include <QMainWindow>
#include "toolwidget.hpp"
#include "model.hpp"
#include "glwindow.hpp"

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
    void newWorld();
    void generate();
    void explore();
    void importConf();
    void exportConf();
    void exit();

private:
    // connection avec les signaux de l'ui. on peut le faire depuis
    // l'ui design, mais c'est moche
    void    makeConnections();

    Ui::MainWindow* _ui;
    Model           _model;
    GLWindow        *_glWindow;

};

#endif /* !__MAINWINDOW_HPP__ */
