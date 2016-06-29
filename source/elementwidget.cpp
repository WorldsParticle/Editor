#include "include/elementwidget.hpp"
#include "ui_elementwidget.h"
#include "include/event/modelevent.hpp"

#include <QFileDialog>

namespace Editor
{

ElementWidget::ElementWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::ElementWidget),
    m_mainWindow(mainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->importButton, SIGNAL(pressed()), this, SLOT(importModel()));
}

ElementWidget::~ElementWidget()
{
    delete m_ui;
}

void    ElementWidget::importModel()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Import"), "", tr("Model files (*)"));

    if (!path.isEmpty())
        QCoreApplication::postEvent(&m_mainWindow.glWindow(), new ModelEvent(path));
}

}
