#ifndef PARTICLEWIDGET_H
#define PARTICLEWIDGET_H

#include <QWidget>
#include "mainwindow.hpp"

namespace Ui {
class ParticleWidget;
}

namespace Editor
{

class ParticleWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ParticleWidget constructor
    /// \param mainWindow
    ///
    explicit ParticleWidget(MainWindow &mainWindow);

    ///
    /// \brief destructor
    ///
    ~ParticleWidget();

private:
    ///
    /// \brief m_ui contain base ui elements
    ///
    Ui::ParticleWidget *m_ui;

    ///
    /// \brief m_mainWindow
    ///
    MainWindow         &m_mainWindow;
};

}

#endif // PARTICLEWIDGET_H
