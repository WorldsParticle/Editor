#include "include/menuobject.hpp"
#include <qfiledialog.h>

namespace Editor
{

MenuObject::MenuObject(MainWindow &mainWindow) :
    QObject(&mainWindow),
//    m_ui(new Ui::ElementWidget),
    m_mainWindow(mainWindow)
{
}

void    MenuObject::newScene()
{
    std::cout << "MenuObject new scene" << std::endl;
    if (!m_engine)
        return;

    m_engine->load("../Engine/resources/scenes/empty.dae");
}

void    MenuObject::importScene()
{
    std::cout << "MenuObject import scene" << std::endl;
    if (!m_engine)
        return;

    QString path = QFileDialog::getOpenFileName(&m_mainWindow, tr("Import"), "", tr("Scene files (*)"));

    if (!path.isEmpty())
        m_engine->load(path.toStdString());//"../Engine/resources/scenes/altair.dae");
        //QCoreApplication::postEvent(&m_mainWindow.glWindow(), new ModelEvent(path));
}

void    MenuObject::exportScene()
{
    std::cout << "MenuObject export scene" << std::endl;
    if (!m_engine)
        return;

    //TODO
}

void    MenuObject::closeScene()
{
    std::cout << "MenuObject close scene" << std::endl;
    if (!m_engine)
        return;

    //TODO
}

void    MenuObject::quit()
{
    std::cout << "MenuObject quit" << std::endl;

    //TODO
    m_mainWindow.close();
}

void    MenuObject::addMesh()
{
    std::cout << "MenuObject new scene" << std::endl;
    if (!m_engine)
        return;

    //todo qdialog file
//    m_engine->load("../Engine/resources/models/tree.DAE");
    //todo core loadmodel
}

void    MenuObject::setAmbientVolume()
{
    int v = 1;

    std::cout << "MenuObject setAmbientVolume " << v << std::endl;
    if (!m_engine)
        return;
}

void    MenuObject::setFxVolume()
{
    int v = 1;

    std::cout << "MenuObject setFxVolume " << v << std::endl;
    if (!m_engine)
        return;
}

void    MenuObject::setResolution()
{
    int v = 1;

    std::cout << "MenuObject setResolution " << v << std::endl;
    if (!m_engine)
        return;
}

}

