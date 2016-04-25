#include "include/generatorwidget.hpp"
#include "ui_generatorwidget.h"
#include "Generator/map/map.hpp"
#include "Generator/generator.hpp"
#include "Generator/param/intvalue.hpp"
#include <QGraphicsItem>
#include <QGroupBox>
#include <QVBoxLayout>

namespace Editor
{

GeneratorWidget::GeneratorWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::GeneratorWidget),
    m_mainWindow(mainWindow),
    m_generator(nullptr)
{
    m_ui->setupUi(this);

    connect(m_ui->launchButton, SIGNAL(pressed()), this, SLOT(launchGenerator()));
}

GeneratorWidget::~GeneratorWidget()
{
    delete m_ui;
}

void    GeneratorWidget::assignGenerator(gen::Generator *generator)
{
    // todo : faire une fonction pour clean les anciens widgets
    // Fait à la va vite pour test, à split et clean
    foreach (gen::GenerationStep *step, m_mainWindow.engine().generator().steps())
    {
        QGroupBox   *box = new QGroupBox(m_ui->scrollArea);
        QVBoxLayout *layout = new QVBoxLayout(box);
        box->setLayout(layout);
        box->setTitle(step->name().c_str());
        QPushButton *soloRun = new QPushButton("Launch", box);
        soloRun->setEnabled(false);
        layout->addWidget(soloRun);
        foreach (gen::Param *p, step->params())
        {
            layout->addWidget(new QLabel(p->name().c_str(), box));
            if (p->type() == gen::Param::intvalue)
            {
                QSpinBox    *s = new QSpinBox(box);
                s->setMinimum(((gen::IntValue *)(p))->minValue());
                s->setMaximum(((gen::IntValue *)(p))->maxValue());
                s->setValue(((gen::IntValue *)(p))->value());
                layout->addWidget(s);
            }
        }
        m_ui->scrollContent->layout()->addWidget(box);
    }

    m_generator = generator;
}

void    GeneratorWidget::launchGenerator()
{
    if (!m_generator)
        return;
    // Temporaire
    map::MapGraph  *map = new map::MapGraph(m_ui->xMaxSpin->value(),
                                            m_ui->yMaxSpin->value());

    m_generator->run(map);
    addMapTo2DScene(*map);
}

void    GeneratorWidget::addMapTo2DScene(map::MapGraph &map)
{
    // insert 2D item in the map scene for easy debug
    // The following is, i concede, awfully long and somehow missplaced (don't think of THAT stuff, you perv)
    // but don't be scared my friend, in a few time it will be removed into a custom graphicScene class

    foreach (QGraphicsItem *item, m_mainWindow.mapScene().items())
        delete item;
    m_mainWindow.mapScene().clear();

    // Bordure
    m_mainWindow.mapScene().addRect(0, 0, m_ui->xMaxSpin->value(), m_ui->yMaxSpin->value(),
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
