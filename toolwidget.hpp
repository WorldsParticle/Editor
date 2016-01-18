#ifndef TOOLWIDGET_HPP
#define TOOLWIDGET_HPP

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class ToolWidget;
}

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
    Ui::ToolWidget *_ui;
};

#endif // TOOLWIDGET_HPP
