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
    explicit ToolWidget(QWidget *parent = 0);
    ~ToolWidget();

public slots:
    void    switchVisibility();

protected:
    virtual void    paintEvent(QPaintEvent *e);


private:
    Ui::ToolWidget      *_ui;
    QPropertyAnimation  *_slideAnimation;
};

}

#endif // TOOLWIDGET_HPP
