#ifndef     __TABWIDGET_HPP__
#define     __TABWIDGET_HPP__

#include <QTabWidget>
#include "model.hpp"

namespace Ui {
class TabWidget;
}

class ToolWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit ToolWidget(QWidget *parent = 0);
    ~ToolWidget();

    void                setConfiguration(Model::WorldConf *conf);
    Model::WorldConf*   getConfiguration(); // devra être const, si la scene ne le modifie pas

public slots:
    void    setConfName(const String &name);
    void    setLandType(int typeId);
    void    setClimatType(int typeId);
    void    setWindPower(int power);

    void    addModel();
    void    delModel();
    void    setCurrentModel(String name);

private:
    void    makeConnections(); // faux air de binding.. peu mieux faire

    Ui::TabWidget*              _ui;
    Model::WorldConf*           _conf;
};

#endif /* !__TABWIDGET_HPP__ */
