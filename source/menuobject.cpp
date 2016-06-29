#include "include/menuobject.hpp"

namespace Editor
{

MenuObject::MenuObject(QObject *parent) :
    QObject(parent)
{
}

void    MenuObject::newScene()
{
    std::cout << "MenuObject new scene" << std::endl;
    if (!m_engine)
        return;

    m_engine->load("../../Engine/resources/scenes/empty.dae");
}


}

