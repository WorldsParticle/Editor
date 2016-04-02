#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "include/generator.hpp"
#include "include/map/map.hpp"

#include <QGraphicsItem>
#include <QDebug>

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
using namespace MAP;

void    MainWindow::generate()
{
    MAP::Map    *map = _generator->generate(_ui->spinXMax->value(),
                                            _ui->spinYMax->value(),
                                            _ui->spinNumber->value());


    addSceneItems(map);

    delete map;
}

void    MainWindow::addSceneItems(MAP::Map *map)
{
    QList<QGraphicsItem *>  items = _scene.items();
    foreach (QGraphicsItem *item, items)
        delete item;
    _scene.clear();

    _scene.addRect(0, 0, _ui->spinXMax->value(), _ui->spinYMax->value(),
                   QPen());

    for (const auto &e : map->edges())
    {
        /*_scene.addLine(e.second->z0->point.x, e.second->z0->point.y,
                           e.second->z1->point.x, e.second->z1->point.y,
                           QPen());*/
        if (e.second->c0 && e.second->c1)
            _scene.addLine(e.second->c0->point.x, e.second->c0->point.y,
                           e.second->c1->point.x, e.second->c1->point.y,
                           QPen(Qt::red));
    }

    for (const auto &c : map->corners())
    {
        _scene.addEllipse(c.second->point.x, c.second->point.y, 5, 5,
                          c.second->water ? QPen(Qt::blue) : QPen(Qt::green), QBrush(Qt::SolidPattern));
    }

    for (const auto &s : map->zones())
        _scene.addRect(s.second->point.x - 2.5, s.second->point.y - 2.5, 5, 5,
                       QPen(), QBrush(Qt::SolidPattern));

    addZonePolygons(map);

    _ui->graphicsView->scale(1, -1);
}

void    MainWindow::addZonePolygons(MAP::Map *map)
{
    for (const auto &pair : map->zones())
    {
        QPolygonF result;
        Zone        *zone = pair.second;
        CrossedEdge *between = zone->borders.front();
        Corner      *from = between->c0;
        Corner      *to = between->c1;

        do
        {
            result << QPointF(from->point.x, from->point.y);
            if (to->edges.size() < 2) // car les corners / edges aux limites ne sont pas encore géré (todo !)
            {
                //result << QPointF(to->point.x, to->point.y);
                break;
            }

            for (std::vector<CrossedEdge *>::iterator it = to->edges.begin(); it != to->edges.end(); ++it)
            {
                if ((*it)->z0->index == zone->index || (*it)->z1->index == zone->index)
                {
                    if ((*it)->c0 != from && (*it)->c1 != from)
                    {
                        if ((*it)->c0 == to)
                        {
                            from = (*it)->c0;
                            to = (*it)->c1;
                        }
                        else
                        {
                            from = (*it)->c1;
                            to = (*it)->c0;
                        }
                        between = (*it);
                        break;
                    }
                }
            }
        } while (between != zone->borders.front());
        _scene.addPolygon(result, QPen(Qt::red), QBrush(Qt::green, Qt::Dense6Pattern));
    }
}
