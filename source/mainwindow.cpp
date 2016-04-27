#include "include/mainwindow.hpp"
#include "include/openglwindow.hpp"
#include "include/tooltabwidget.hpp"
#include "include/generatorwidget.hpp"
#include "include/modelwidget.hpp"
#include "include/particlewidget.hpp"
#include "include/skyboxwidget.hpp"
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
    m_toolTabWidget(NULL),
    m_generatorWidget(NULL),
    m_modelWidget(NULL),
    m_particleWidget(NULL),
    m_skyboxWidget(NULL),
    m_glView(NULL),
    m_centralLayout(),
    m_engine(),
    m_generator(),
    m_mapView(NULL),
    m_mapScene()
{
    m_ui->setupUi(this);

    initializeCustomUi();

    makeConnections();

    show();

    m_glWindow.run(&m_engine);
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

    m_generatorWidget = new GeneratorWidget(*this);
    m_modelWidget = new ModelWidget(*this);
    m_particleWidget = new ParticleWidget(*this);
    m_skyboxWidget = new SkyboxWidget(*this);

    m_toolTabWidget = new ToolTabWidget(*this);
    m_centralLayout.addWidget(m_toolTabWidget, 0);

    m_glView = QWidget::createWindowContainer(&m_glWindow);
    m_centralLayout.addWidget(m_glView, 1);

    m_mapView = new QGraphicsView();
    m_mapView->setScene(&m_mapScene);
    m_centralLayout.addWidget(m_mapView, 1);
    m_mapView->hide();

    m_generatorWidget->assignGenerator(&m_generator);
}

void    MainWindow::makeConnections()
{
    connect(m_ui->actionZones, SIGNAL(triggered(bool)), m_glView, SLOT(hide()));
    connect(m_ui->actionZones, SIGNAL(triggered(bool)), m_mapView, SLOT(show()));

    connect(m_ui->actionExploration, SIGNAL(triggered(bool)), m_mapView, SLOT(hide()));
    connect(m_ui->actionExploration, SIGNAL(triggered(bool)), m_glView, SLOT(show()));

    connect(m_ui->actionGenerer, SIGNAL(triggered(bool)), m_generatorWidget, SLOT(launchGenerator()));
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
