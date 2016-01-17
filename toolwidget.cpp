#include "toolwidget.hpp"
#include "ui_toolwidget.h"

ToolWidget::ToolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolWidget)
{
    ui->setupUi(this);
}

ToolWidget::~ToolWidget()
{
    delete ui;
}
