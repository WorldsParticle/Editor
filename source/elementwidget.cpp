#include "include/elementwidget.hpp"
#include "ui_elementwidget.h"
#include "include/event/modelevent.hpp"
#include "include/param/paramlink.hpp"
#include <QGroupBox>
#include <QVBoxLayout>

//#include <QFileDialog>

namespace Editor
{

ElementWidget::ElementWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::ElementWidget),
    m_mainWindow(mainWindow),
    m_generator(nullptr)
{
    m_ui->setupUi(this);

//    connect(m_ui->importButton, SIGNAL(pressed()), this, SLOT(importModel()));
}

ElementWidget::~ElementWidget()
{
    delete m_ui;
}

//void    ElementWidget::importModel()
//{
//    QString path = QFileDialog::getOpenFileName(this, tr("Import"), "", tr("Model files (*)"));

//    if (!path.isEmpty())
//        QCoreApplication::postEvent(&m_mainWindow.glWindow(), new ModelEvent(path));
//}

void ElementWidget::assignGenerator(gen::Generator *generator)
{
    foreach (GenData::ZoneData *zone, generator->zoneDatas())
    {
//        QGroupBox   *box = new QGroupBox(m_ui->elementScrollArea);

//        QVBoxLayout *layout = new QVBoxLayout(box);
//        box->setLayout(layout);
//        box->setTitle(zone->name().c_str());

        foreach (GenData::ElementData *element, zone->elements())
        {
            QGroupBox   *box = new QGroupBox(m_ui->elementScrollArea);

            QVBoxLayout *layout = new QVBoxLayout(box);
            box->setLayout(layout);
            box->setTitle(element->name.c_str());

            //TODO element box
            foreach (gen::Param *p, element->params())
                layout->addWidget(ParamLink::createLink(p));

            m_ui->elementScrollContent->layout()->addWidget(box);
        }

//        m_ui->elementScrollContent->layout()->addWidget(box);

        break;//TMP to have only one zone
    }
}

}
