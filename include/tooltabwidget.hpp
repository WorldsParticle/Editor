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

///
/// \brief The ToolTabWidget class is used to regroup the engine and generator tools
///
class ToolTabWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ToolWidget default constructor
    /// \param parent is the top widget
    ///
    explicit ToolTabWidget(MainWindow &mainwindow);

    ///
    /// \brief Destructor
    ///
    ~ToolTabWidget();

public slots:
    ///
    /// \brief switchVisibility is a slot which switch the _ui->tabwidget visibility
    ///
    void    switchVisibility();

protected:
    ///
    /// \brief paintEvent override, used for paint a transparent background
    /// \param e
    ///
    virtual void    paintEvent(QPaintEvent *e);


private:
    ///
    /// \brief _ui contain some ui elements which are defined in toolwidget.ui
    ///
    Ui::ToolWidget      *m_ui;

    ///
    /// \brief _slideAnimation is used for having a smooth animation when switching the _ui->tabwidget visibility
    ///
    QPropertyAnimation  *m_slideAnimation;

    ///
    /// \brief _mainwindow
    ///
    MainWindow          &m_mainWindow;
};

}

#endif // TOOLWIDGET_HPP
