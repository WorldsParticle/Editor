#ifndef TOOLWIDGET_HPP
#define TOOLWIDGET_HPP

#include <QWidget>

namespace Ui {
class ToolWidget;
}

class ToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolWidget(QWidget *parent = 0);
    ~ToolWidget();

private:
    Ui::ToolWidget *ui;
};

#endif // TOOLWIDGET_HPP
