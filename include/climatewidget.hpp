#ifndef PARTICLEWIDGET_H
#define PARTICLEWIDGET_H

#include <QWidget>
#include "mainwindow.hpp"

namespace Ui {
class ClimateWidget;
}

namespace Editor
{

///
/// \brief The ClimateWidget class
///
class ClimateWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ClimateWidget constructor
    /// \param mainWindow
    ///
    explicit ClimateWidget(MainWindow &mainWindow);

    ///
    /// \brief assignGenerator
    ///
    void    assignGenerator(gen::Generator *generator);

    ///
    /// \brief destructor
    ///
    ~ClimateWidget();

private:
    ///
    /// \brief m_ui contain base ui elements
    ///
    Ui::ClimateWidget *m_ui;

    ///
    /// \brief m_mainWindow
    ///
    MainWindow         &m_mainWindow;

    ///
    /// \brief Current generator in use
    ///
    gen::Generator      *m_generator;
};

}

#endif // PARTICLEWIDGET_H
