#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>
#include "mainwindow.hpp"

namespace Ui {
class ElementWidget;
}

namespace Editor
{

///
/// \brief The ElementWidget class, it will show the scene graph and will allow the user to change nodes properties (as well as add / delete them)
///
class ElementWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ElementWidgetconstructor
    /// \param mainWindow
    ///
    explicit ElementWidget(MainWindow &mainWindow);

    ///
    /// \brief destructor
    ///
    ~ElementWidget();

public slots:
    ///
    /// \brief importModel import a model to the scene
    ///
    void    importModel();

private:
    ///
    /// \brief m_ui contain base ui elements
    ///
    Ui::ElementWidget *m_ui;

    ///
    /// \brief m_mainWindow
    ///
    MainWindow      &m_mainWindow;
};

}

#endif // MODELWIDGET_H
