#include "include/tooltabwidget.hpp"
#include "ui_tooltabwidget.h"
#include "include/generatorwidget.hpp"
#include "include/elementwidget.hpp"
#include "include/climatewidget.hpp"
#include <qdebug.h>
#include <QPainter>
#include <QFileDialog>
#include <iostream>
#include <QGraphicsItem>

namespace Editor
{

ToolTabWidget::ToolTabWidget(MainWindow &mainWindow) :
    QWidget(&mainWindow),
    m_ui(new Ui::ToolWidget),
    m_slideAnimation(NULL),
    m_mainWindow(mainWindow)
{
    m_ui->setupUi(this);

    m_slideAnimation = new QPropertyAnimation(m_ui->tabWidget, "maximumWidth");
    m_slideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_slideAnimation->setDuration(500);
    m_slideAnimation->setStartValue(this->width());
    m_slideAnimation->setEndValue(0);

    m_ui->tabWidget->addTab(m_mainWindow.terrainWidget(), QIcon(":/ressources/images/mountain.png"), QString());
    m_ui->tabWidget->addTab(m_mainWindow.modelWidget(), QIcon(":/ressources/images/model.png"), QString());
    m_ui->tabWidget->addTab(m_mainWindow.climateWidget(), QIcon(":/ressources/images/particle.png"), QString());
//    m_ui->tabWidget->addTab(m_mainWindow.skyboxWidget(), QIcon(":/ressources/images/sky.png"), QString());

    connect(m_ui->switchButton, SIGNAL(pressed()), this, SLOT(switchVisibility()));
}

ToolTabWidget::~ToolTabWidget()
{
    delete m_ui;
}

void    ToolTabWidget::switchVisibility()
{
    m_slideAnimation->stop();
    if (m_ui->switchButton->text() == "<") //Un peu moche
    {
        m_slideAnimation->setDirection(QAbstractAnimation::Forward);
        m_ui->switchButton->setText(">");
    }
    else
    {
        m_slideAnimation->setDirection(QAbstractAnimation::Backward);
        m_ui->switchButton->setText("<");
    }
    m_slideAnimation->start();
}

void    ToolTabWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 0, 0));
    QWidget::paintEvent(e);
}

}
