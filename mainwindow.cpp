#include "mainwindow.hpp"
#include "openglwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _glWindow(NULL)
{
    _ui->setupUi(this);
    connect(_ui->runButton, SIGNAL(pressed()), &_glWindow, SLOT(run()));
}

MainWindow::~MainWindow()
{
    delete _ui;
}
