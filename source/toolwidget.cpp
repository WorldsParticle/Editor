#include "include/toolwidget.hpp"
#include "ui_toolwidget.h"
#include <qdebug.h>
#include <QPainter>
#include <QFileDialog>
#include <iostream>
#include <QGraphicsItem>

namespace Editor
{

ToolWidget::ToolWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    _ui(new Ui::ToolWidget),
    _slideAnimation(NULL),
    _mainwindow(mainWindow)
{
    _ui->setupUi(this);

    _slideAnimation = new QPropertyAnimation(_ui->tabWidget, "maximumWidth");
    _slideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    _slideAnimation->setDuration(500);
    _slideAnimation->setStartValue(this->width());
    _slideAnimation->setEndValue(0);

    connect(_ui->switchButton, SIGNAL(pressed()), this, SLOT(switchVisibility()));
    connect(_ui->buttonImport, SIGNAL(pressed()), this, SLOT(importModel()));
    connect(_ui->buttonGenerator, SIGNAL(pressed()), this, SLOT(launchGenerator()));
}

ToolWidget::~ToolWidget()
{
    delete _ui;
}

void    ToolWidget::switchVisibility()
{
    _slideAnimation->stop();
    if (_ui->switchButton->text() == "<") //Un peu moche
    {
        _slideAnimation->setDirection(QAbstractAnimation::Forward);
        _ui->switchButton->setText(">");
    }
    else
    {
        _slideAnimation->setDirection(QAbstractAnimation::Backward);
        _ui->switchButton->setText("<");
    }
    _slideAnimation->start();
}

void    ToolWidget::importModel()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Import"), "", tr("Model files (*)"));
    if (path.isEmpty())
    {
        _mainwindow.engine().load(path.toStdString());
    }
}

void    ToolWidget::launchGenerator()
{
    map::MapGraph  *map = _mainwindow.engine().generator().generate(_ui->spinXMax->value(),
                                                                _ui->spinYMax->value(),
                                                                _ui->spinZoneNumber->value());

    addMapTo2DScene(*map);
}

void    ToolWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 0, 0));
    QWidget::paintEvent(e);
}

void    ToolWidget::addMapTo2DScene(map::MapGraph &map)
{
    // insert 2D item in the map scene for easy debug
    // The following is, i concede, awfully long and somehow missplaced (don't think of THAT stuff, you perv)
    // but don't be scared my friend, in a few time it will be removed into a custom graphicScene class

    foreach (QGraphicsItem *item, _mainwindow.mapScene().items())
        delete item;
    _mainwindow.mapScene().clear();

    // Bordure
    _mainwindow.mapScene().addRect(0, 0, _ui->spinXMax->value(), _ui->spinYMax->value(),
                                   QPen());


    for (const auto &c : map.corners())
    {
        _mainwindow.mapScene().addEllipse(c.second->point.x, c.second->point.y, 5, 5,
                                          c.second->water ? QPen(Qt::blue) : QPen(Qt::green), QBrush(Qt::SolidPattern));
    }

    for (const auto &s : map.zones())
        _mainwindow.mapScene().addRect(s.second->point.x - 2.5, s.second->point.y - 2.5, 5, 5,
                                       QPen(), QBrush(Qt::SolidPattern));

    for (const auto &pair : map.zones())
    {
        QPolygonF        result;
        map::Zone        *zone = pair.second;
        map::CrossedEdge *between = zone->borders.front();
        map::Corner      *from = between->c0;
        map::Corner      *to = between->c1;

        do
        {
            result << QPointF(from->point.x, from->point.y);
            if (to->edges.size() < 2) // car les corners / edges aux limites ne sont pas encore géré (todo !)
            {
                //result << QPointF(to->point.x, to->point.y);
                break;
            }

            for (std::vector<map::CrossedEdge *>::iterator it = to->edges.begin(); it != to->edges.end(); ++it)
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
        _mainwindow.mapScene().addPolygon(result, QPen(Qt::red), QBrush(Qt::green, Qt::Dense6Pattern));
    }

}

}
