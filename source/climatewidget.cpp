#include "include/climatewidget.hpp"
#include "ui_climatewidget.h"

namespace Editor
{

ClimateWidget::ClimateWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::ClimateWidget),
    m_mainWindow(mainWindow)
{
    m_ui->setupUi(this);
}

ClimateWidget::~ClimateWidget()
{
    delete m_ui;
}

}
