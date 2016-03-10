#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _generator(),
    _scene()
{
    _ui->setupUi(this);
    _ui->graphicsView->setScene(&_scene);

    connect(_ui->buttonGenerate, SIGNAL(pressed()), this, SLOT(generate()));
}

MainWindow::~MainWindow()
{
    _scene.clear();
    delete _ui;
}

void    MainWindow::generate()
{
    _generator.launch(_ui->spinNumber->value(),
                      _ui->spinXMax->value(),
                      _ui->spinYMax->value());

    _scene.clear();
    for (const auto &s : _generator.sites())
        _scene.addEllipse(s->point.first, s->point.second, 5, 5,
                          QPen(), QBrush(Qt::SolidPattern));
}
