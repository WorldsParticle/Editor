#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsItem>

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
    QList<QGraphicsItem *>  items = _scene.items();
    foreach (QGraphicsItem *item, items)
        delete item;
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
        _scene.addEllipse(s->point.x, s->point.y, 5, 5,
                          QPen(), QBrush(Qt::SolidPattern));
    for (const auto &e : _generator.edges())
    {
        _scene.addLine(e->d0->point.x, e->d0->point.y,
                       e->d1->point.x, e->d1->point.y,
                       QPen());
        if (e->v0 && e->v1)
            _scene.addLine(e->v0->point.x, e->v0->point.y,
                           e->v1->point.x, e->v1->point.y,
                           QPen(Qt::red));
    }
}
