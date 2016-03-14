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


    QList<QGraphicsItem *>  items = _scene.items();
    foreach (QGraphicsItem *item, items)
        delete item;
    _scene.clear();

    _scene.addRect(0, 0, _ui->spinXMax->value(), _ui->spinYMax->value(),
                   QPen());

    for (const auto &s : _generator.sites())
        _scene.addEllipse(s.second->point.x, s.second->point.y, 5, 5,
                          QPen(), QBrush(Qt::SolidPattern));
    for (const auto &e : _generator.edges())
    {
        _scene.addLine(e.second->d0->point.x, e.second->d0->point.y,
                       e.second->d1->point.x, e.second->d1->point.y,
                       QPen());
        _scene.addEllipse(e.second->midpoint.x, e.second->midpoint.y, 5, 5,
                          QPen(Qt::green), QBrush(Qt::SolidPattern));
        if (e.second->v0 && e.second->v1)
            _scene.addLine(e.second->v0->point.x, e.second->v0->point.y,
                           e.second->v1->point.x, e.second->v1->point.y,
                           QPen(Qt::red));
    }
    for (const auto &c : _generator.corners())
    {
        _scene.addEllipse(c.second->point.x, c.second->point.y, 5, 5,
                          QPen(Qt::red), QBrush(Qt::SolidPattern));
    }
}
