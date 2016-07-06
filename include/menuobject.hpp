#ifndef MENUOBJECT_HPP
#define MENUOBJECT_HPP

#include <QObject>
#include "mainwindow.hpp"
//#include <Engine/Core.hpp>
//#include <Generator/generator.hpp>

namespace Editor
{

class MenuObject : public QObject
{
    Q_OBJECT
public:
    //explicit MenuObject(QObject *parent = 0);
    explicit MenuObject(MainWindow &mainWindow);

    ///
    /// \brief setGenerator
    ///
    inline void    setGenerator(gen::Generator *generator) {
        m_generator = generator;
    }
    ///
    /// \brief setEngine
    ///
    inline void    setEngine(Engine::Core *engine) {
        m_engine = engine;
    }

signals:

public slots:
    ///
    /// \brief newScene
    ///
    void    newScene();
    void    importScene();
    void    exportScene();
    void    closeScene();
    //void    quit();

    void    addMesh();

    void    setResolution();//flag ?
    void    setAmbientVolume();
    void    setFxVolume();

    //void    about();

private:


    ///
    /// \brief m_mainWindow, temporaire
    ///
    MainWindow          &m_mainWindow;

    ///
    /// \brief m_engine is the worldsparticle engine, where the magic happen.
    ///
    Engine::Core   *m_engine;

    ///
    /// \brief m_generator is the generator which will generate the heightmap
    ///
    gen::Generator *m_generator;
};

}

#endif // MENUOBJECT_HPP