#include "include/skyboxwidget.hpp"
#include "ui_skyboxwidget.h"

namespace Editor
{

SkyboxWidget::SkyboxWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::SkyboxWidget),
    m_mainWindow(mainWindow)
{
    m_ui->setupUi(this);
}

SkyboxWidget::~SkyboxWidget()
{
    delete m_ui;
}

}
