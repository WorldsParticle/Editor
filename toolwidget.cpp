#include "toolwidget.hpp"
#include "ui_toolwidget.h"
#include <qdebug.h>
#include <QPainter>

ToolWidget::ToolWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ToolWidget),
    _slideAnimation(NULL)
{
    _ui->setupUi(this);

    _slideAnimation = new QPropertyAnimation(_ui->tabWidget, "maximumWidth");
    _slideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    _slideAnimation->setDuration(500);
    _slideAnimation->setStartValue(this->width());
    _slideAnimation->setEndValue(0);

    connect(_ui->switchButton, SIGNAL(pressed()), this, SLOT(switchVisibility()));
}

ToolWidget::~ToolWidget()
{
    delete _ui;
}

void    ToolWidget::switchVisibility()
{
    _slideAnimation->stop();
    if (_ui->switchButton->text() == "<") //Un peu moche
    {
        _slideAnimation->setDirection(QAbstractAnimation::Forward);
        _ui->switchButton->setText(">");
    }
    else
    {
        _slideAnimation->setDirection(QAbstractAnimation::Backward);
        _ui->switchButton->setText("<");
    }
    _slideAnimation->start();
}

void    ToolWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 0, 0));
    QWidget::paintEvent(e);
}
