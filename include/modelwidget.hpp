#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>
#include "mainwindow.hpp"

namespace Ui {
class ModelWidget;
}

namespace Editor
{

///
/// \brief The ModelWidget class, it will show the scene graph and will allow the user to change nodes properties (as well as add / delete them)
///
class ModelWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ModelWidgetconstructor
    /// \param mainWindow
    ///
    explicit ModelWidget(MainWindow &mainWindow);

    ///
    /// \brief destructor
    ///
    ~ModelWidget();

public slots:
    ///
    /// \brief importModel import a model to the scene
    ///
    void    importModel();

private:
    ///
    /// \brief m_ui contain base ui elements
    ///
    Ui::ModelWidget *m_ui;

    ///
    /// \brief m_mainWindow
    ///
    MainWindow      &m_mainWindow;
};

}

#endif // MODELWIDGET_H
