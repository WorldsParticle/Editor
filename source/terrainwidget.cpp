#include "include/terrainwidget.hpp"
#include "ui_terrainwidget.h"
#include <QGraphicsItem>

namespace Editor
{

TerrainWidget::TerrainWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::TerrainWidget),
    m_mainWindow(mainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->launchButton, SIGNAL(pressed()), this, SLOT(launchGenerator()));
}

TerrainWidget::~TerrainWidget()
{
    delete m_ui;
}

void    TerrainWidget::launchGenerator()
{
    map::MapGraph  *map = m_mainWindow.engine().generator().generate(m_ui->XMaxSpin->value(),
                                                                m_ui->YMaxSpin->value(),
                                                                m_ui->ZoneNumberSpin->value());

    addMapTo2DScene(*map);
}

void    TerrainWidget::addMapTo2DScene(map::MapGraph &map)
{
    // insert 2D item in the map scene for easy debug
    // The following is, i concede, awfully long and somehow missplaced (don't think of THAT stuff, you perv)
    // but don't be scared my friend, in a few time it will be removed into a custom graphicScene class

    foreach (QGraphicsItem *item, m_mainWindow.mapScene().items())
        delete item;
    m_mainWindow.mapScene().clear();

    // Bordure
    m_mainWindow.mapScene().addRect(0, 0, m_ui->XMaxSpin->value(), m_ui->YMaxSpin->value(),
                                   QPen());


    for (const auto &c : map.corners())
    {
        m_mainWindow.mapScene().addEllipse(c.second->point.x, c.second->point.y, 5, 5,
                                          c.second->water ? QPen(Qt::blue) : QPen(Qt::green), QBrush(Qt::SolidPattern));
    }

    for (const auto &s : map.zones())
        m_mainWindow.mapScene().addRect(s.second->point.x - 2.5, s.second->point.y - 2.5, 5, 5,
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
        m_mainWindow.mapScene().addPolygon(result, QPen(Qt::red), QBrush(Qt::green, Qt::Dense6Pattern));
    }

}

}
