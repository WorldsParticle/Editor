#ifndef SKYBOXWIDGET_H
#define SKYBOXWIDGET_H

#include <QWidget>
#include "mainwindow.hpp"

namespace Ui {
class SkyboxWidget;
}

namespace Editor
{

///
/// \brief The SkyboxWidget class
///
class SkyboxWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief SkyboxWidget constructor
    /// \param mainWindow
    ///
    explicit SkyboxWidget(MainWindow &mainWindow);

    ///
    /// \brief destructor
    ///
    ~SkyboxWidget();

private:
    ///
    /// \brief m_ui contain base ui elements
    ///
    Ui::SkyboxWidget *m_ui;

    ///
    /// \brief m_mainWindow
    ///
    MainWindow       &m_mainWindow;
};

}

#endif // SKYBOXWIDGET_H
