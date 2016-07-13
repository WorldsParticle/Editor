#include "include/climatewidget.hpp"
#include "ui_climatewidget.h"
#include "include/param/paramlink.hpp"
#include <QGroupBox>
#include <QVBoxLayout>

namespace Editor
{

ClimateWidget::ClimateWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::ClimateWidget),
    m_mainWindow(mainWindow),
    m_generator(nullptr)
{
    m_ui->setupUi(this);
}

ClimateWidget::~ClimateWidget()
{
    delete m_ui;
}

void ClimateWidget::assignGenerator(gen::Generator *generator)
{
    foreach (GenData::ZoneData *zone, generator->zoneDatas())
    {
        QGroupBox   *box = new QGroupBox(m_ui->climateScrollArea);

        QVBoxLayout *layout = new QVBoxLayout(box);
        box->setLayout(layout);
        box->setTitle(zone->name().c_str());

        GenData::ClimateData *climate = zone->climate();
        foreach (gen::Param *p, climate->params())
            layout->addWidget(ParamLink::createLink(p));
        //TODO slider heure de la journee
        //TODO checkbox posteffect

//        foreach (GenData::ElementData *element, zone->elements())
//        {
//            QGroupBox   *box = new QGroupBox(m_ui->elementScrollArea);

//            QVBoxLayout *layout = new QVBoxLayout(box);
//            box->setLayout(layout);
//            box->setTitle(element->name.c_str());

//            //TODO element box
//            foreach (gen::Param *p, element->params())
//                layout->addWidget(ParamLink::createLink(p));

//            m_ui->elementScrollContent->layout()->addWidget(box);
//        }

        m_ui->climateScrollContent->layout()->addWidget(box);

        break;//TMP to have only one zone
    }
}
}
