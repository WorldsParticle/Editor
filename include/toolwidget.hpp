#ifndef TOOLWIDGET_HPP
#define TOOLWIDGET_HPP

#include <QWidget>
#include <QPaintEvent>
#include <QPropertyAnimation>

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
    explicit ToolWidget(QWidget *parent = 0);

    ///
    /// \brief Destructor
    ///
    ~ToolWidget();

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
    Ui::ToolWidget      *_ui;

    ///
    /// \brief _slideAnimation is used for having a smooth animation when switching the _ui->tabwidget visibility
    ///
    QPropertyAnimation  *_slideAnimation;
};

}

#endif // TOOLWIDGET_HPP
