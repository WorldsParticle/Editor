#include "toolwidget.hpp"
#include "ui_toolwidget.h"
#include <qdebug.h>
#include <QPainter>

ToolWidget::ToolWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ToolWidget)
{
    _ui->setupUi(this);

    connect(_ui->switchButton, SIGNAL(pressed()), this, SLOT(switchVisibility()));
}

ToolWidget::~ToolWidget()
{
    delete _ui;
}

void    ToolWidget::switchVisibility()
{
    if (_ui->switchButton->text() == "<") //Un peu moche
    {
        _ui->tabWidget->hide();
        _ui->switchButton->setText(">");
    }
    else
    {
        _ui->tabWidget->show();
        _ui->switchButton->setText("<");
    }
}

void    ToolWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 0, 0));
    QWidget::paintEvent(e);
}
