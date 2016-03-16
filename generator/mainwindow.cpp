#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generator.h"
#include "map/map.h"

#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _generator(),
    _scene()
{
    _ui->setupUi(this);
    _ui->graphicsView->setScene(&_scene);

    _generator = new GEN::Generator();

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
    MAP::Map    *map = _generator->generate(_ui->spinXMax->value(),
                                            _ui->spinYMax->value(),
                                            _ui->spinNumber->value());


    QList<QGraphicsItem *>  items = _scene.items();
    foreach (QGraphicsItem *item, items)
        delete item;
    _scene.clear();

    _scene.addRect(0, 0, _ui->spinXMax->value(), _ui->spinYMax->value(),
                   QPen());

    for (const auto &s : map->zones())
        _scene.addEllipse(s.second->point.x, s.second->point.y, 5, 5,
                          QPen(), QBrush(Qt::SolidPattern));
    for (const auto &e : map->edges())
    {
        /*_scene.addLine(e.second->z0->point.x, e.second->z0->point.y,
                       e.second->z1->point.x, e.second->z1->point.y,
                       QPen());*/
        _scene.addEllipse(e.second->midpoint.x, e.second->midpoint.y, 5, 5,
                          QPen(Qt::green), QBrush(Qt::SolidPattern));
        if (e.second->c0 && e.second->c1)
            _scene.addLine(e.second->c0->point.x, e.second->c0->point.y,
                           e.second->c1->point.x, e.second->c1->point.y,
                           QPen(Qt::red));
    }
    for (const auto &c : map->corners())
    {
        _scene.addEllipse(c.second->point.x, c.second->point.y, 5, 5,
                          QPen(Qt::red), QBrush(Qt::SolidPattern));
    }

    _ui->graphicsView->scale(1, -1);

    delete map;
}
