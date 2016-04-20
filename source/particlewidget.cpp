#include "include/particlewidget.hpp"
#include "ui_particlewidget.h"

namespace Editor
{

ParticleWidget::ParticleWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::ParticleWidget),
    m_mainWindow(mainWindow)
{
    m_ui->setupUi(this);
}

ParticleWidget::~ParticleWidget()
{
    delete m_ui;
}

}
