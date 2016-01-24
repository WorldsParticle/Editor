#include "mainwindow.hpp"
#include "openglwindow.hpp"
#include "ui_mainwindow.h"
#include <QPainter>
#include <qdebug.h>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _glWindow(),
    _toolWidget(),
    _docker(NULL),
    _centralLayout()
{
    _ui->setupUi(this);
    setWindowTitle("Editeur");
    _ui->statusBar->showMessage("Welcome to WorldsParticle editor !", 5000);

    setAttribute(Qt::WA_QuitOnClose, true);

    _ui->centralWidget->setLayout(&_centralLayout);
    _centralLayout.addWidget(&_toolWidget, 0);

    dockGlWindow();

    show();
    _glWindow.run();
}

MainWindow::~MainWindow()
{
    delete _docker;
    delete _ui;
}

void    MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        this->close();
}

void    MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap("://ressources/images/bg.jpg"));
    QWidget::paintEvent(e);
}

void    MainWindow::closeEvent(QCloseEvent *e)
{
    exit(1); // à remplacer quand on mettra en place les threads
}

void    MainWindow::dockGlWindow()
{
    _docker = QWidget::createWindowContainer(&_glWindow);
    _centralLayout.addWidget(_docker, 1);
}
