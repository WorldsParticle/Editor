#include "include/mainwindow.hpp"
#include "include/openglwindow.hpp"
#include "include/menuobject.hpp"
#include "include/tooltabwidget.hpp"
#include "include/generatorwidget.hpp"
#include "include/elementwidget.hpp"
#include "include/climatewidget.hpp"
#include "ui_mainwindow.h"
#include <QPainter>
#include <qdebug.h>
#include <QThread>

namespace Editor
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_glWindow(),
    m_menuObject(NULL),
    m_toolTabWidget(NULL),
    m_generatorWidget(NULL),
    m_elementWidget(NULL),
    m_climateWidget(NULL),
    m_glView(NULL),
    m_centralLayout(),
    m_engine(),
    m_generator(&m_engine),
    m_mapView(NULL),
    m_mapScene()
{
    m_ui->setupUi(this);

    initializeCustomUi();

    makeConnections();

    show();

    m_glWindow.run(&m_engine, &m_generator);
}

MainWindow::~MainWindow()
{
    delete m_glView;
    delete m_ui;
}

void    MainWindow::initializeCustomUi()
{
    setWindowTitle("Editeur");
    m_ui->statusBar->showMessage("Welcome to WorldsParticle editor !", 5000);
    setAttribute(Qt::WA_QuitOnClose, true);

    m_ui->centralWidget->setLayout(&m_centralLayout);

    m_menuObject = new MenuObject(*this);

    m_generatorWidget = new GeneratorWidget(*this);
    m_elementWidget = new ElementWidget(*this);
    m_climateWidget = new ClimateWidget(*this);

    m_toolTabWidget = new ToolTabWidget(*this);
    m_centralLayout.addWidget(m_toolTabWidget, 0);

    m_glView = QWidget::createWindowContainer(&m_glWindow);
    m_centralLayout.addWidget(m_glView, 1);

    m_mapView = new QGraphicsView();
    m_mapView->setScene(&m_mapScene);
    m_centralLayout.addWidget(m_mapView, 1);
    m_mapView->hide();

    m_menuObject->setEngine(&m_engine);
    m_menuObject->setGenerator(&m_generator);
    m_generatorWidget->assignGenerator(&m_generator);
    m_elementWidget->assignGenerator(&m_generator);
}

void    MainWindow::makeConnections()
{
//    connect(m_ui->actionZones, SIGNAL(triggered(bool)), m_glView, SLOT(hide()));
//    connect(m_ui->actionZones, SIGNAL(triggered(bool)), m_mapView, SLOT(show()));

//    connect(m_ui->actionExploration, SIGNAL(triggered(bool)), m_mapView, SLOT(hide()));
//    connect(m_ui->actionExploration, SIGNAL(triggered(bool)), m_glView, SLOT(show()));

    //connect(m_ui->actionGenerer, SIGNAL(triggered(bool)), m_generatorWidget, SLOT(launchGenerator()));
    connect(m_ui->actionNew, SIGNAL(triggered(bool)), m_menuObject, SLOT(newScene()));
    connect(m_ui->actionImportScene, SIGNAL(triggered(bool)), m_menuObject, SLOT(importScene()));
    connect(m_ui->actionExport, SIGNAL(triggered(bool)), m_menuObject, SLOT(exportScene()));
    connect(m_ui->actionClose, SIGNAL(triggered(bool)), m_menuObject, SLOT(closeScene()));
    connect(m_ui->actionQuit, SIGNAL(triggered(bool)), m_menuObject, SLOT(quit()));

    connect(m_ui->actionAddMesh, SIGNAL(triggered(bool)), m_menuObject, SLOT(addMesh()));

    connect(m_ui->actionResolution, SIGNAL(triggered(bool)), m_menuObject, SLOT(setResolution()));
    connect(m_ui->actionVolume, SIGNAL(triggered(bool)), m_menuObject, SLOT(setAmbientVolume()));
    connect(m_ui->actionVolume, SIGNAL(triggered(bool)), m_menuObject, SLOT(setFxVolume()));
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

void    MainWindow::closeEvent(QCloseEvent *)
{
    exit(1); // à remplacer quand on mettra en place les threads
}

}
