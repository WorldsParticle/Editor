#include "include/mainwindow.hpp"
#include "include/openglwindow.hpp"
#include "ui_mainwindow.h"
#include <QPainter>
#include <qdebug.h>
#include <QThread>

namespace Editor
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _glWindow(),
    _toolWidget(),
    _glView(NULL),
    _centralLayout(),
    _engine(),
    _mapView(NULL),
    _mapScene()
{
    _ui->setupUi(this);
    setWindowTitle("Editeur");
    _ui->statusBar->showMessage("Welcome to WorldsParticle editor !", 5000);
    setAttribute(Qt::WA_QuitOnClose, true);

    _ui->centralWidget->setLayout(&_centralLayout);

    _centralLayout.addWidget(&_toolWidget, 0);
    _toolWidget.setEngine(&_engine);

    _glView = QWidget::createWindowContainer(&_glWindow);
    _centralLayout.addWidget(_glView, 1);

    _mapView = new QGraphicsView();
    _mapView->setScene(&_mapScene);
    _centralLayout.addWidget(_mapView, 1);
    _mapView->hide();

    connect(_ui->actionZones, SIGNAL(triggered(bool)), _glView, SLOT(hide()));
    connect(_ui->actionZones, SIGNAL(triggered(bool)), _mapView, SLOT(show()));

    connect(_ui->actionExploration, SIGNAL(triggered(bool)), _mapView, SLOT(hide()));
    connect(_ui->actionExploration, SIGNAL(triggered(bool)), _glView, SLOT(show()));

    connect(_ui->actionGenerer, SIGNAL(triggered(bool)), &_toolWidget, SLOT(launchGenerator()));

    show();
    _glWindow.run(&_engine);
}

MainWindow::~MainWindow()
{
    delete _glView;
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

}
