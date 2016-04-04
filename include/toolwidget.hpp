#ifndef TOOLWIDGET_HPP
#define TOOLWIDGET_HPP

#include "mainwindow.hpp"
#include <QWidget>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <Engine/Core.hpp>

namespace Ui {
class ToolWidget;
}

namespace Editor
{

class ToolWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ToolWidget default constructor
    /// \param parent is the top widget
    ///
    explicit ToolWidget(MainWindow &mainwindow);

    ///
    /// \brief Destructor
    ///
    ~ToolWidget();

public slots:
    ///
    /// \brief switchVisibility is a slot which switch the _ui->tabwidget visibility
    ///
    void    switchVisibility();

    ///
    /// \brief importModel import a model to the scene
    ///
    void    importModel();

    ///
    /// \brief launchGenerator
    ///
    void    launchGenerator();


protected:
    ///
    /// \brief paintEvent override, used for paint a transparent background
    /// \param e
    ///
    virtual void    paintEvent(QPaintEvent *e);


private:
    ///
    /// \brief addMapTo2DScene will be removed in a custom graphicsScene class
    /// \param map
    ///
    void    addMapTo2DScene(MAP::Map &map);
    ///
    /// \brief _ui contain some ui elements which are defined in toolwidget.ui
    ///
    Ui::ToolWidget      *_ui;

    ///
    /// \brief _slideAnimation is used for having a smooth animation when switching the _ui->tabwidget visibility
    ///
    QPropertyAnimation  *_slideAnimation;

    MainWindow          &_mainwindow;
};

}

#endif // TOOLWIDGET_HPP
