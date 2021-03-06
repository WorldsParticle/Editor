#include "include/modelwidget.hpp"
#include "ui_modelwidget.h"
#include "include/event/modelevent.hpp"

#include <QFileDialog>

namespace Editor
{

ModelWidget::ModelWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::ModelWidget),
    m_mainWindow(mainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->importButton, SIGNAL(pressed()), this, SLOT(importModel()));
}

ModelWidget::~ModelWidget()
{
    delete m_ui;
}

void    ModelWidget::importModel()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Import"), "", tr("Model files (*)"));

    if (!path.isEmpty())
        QCoreApplication::postEvent(&m_mainWindow.glWindow(), new ModelEvent(path));
}

}
