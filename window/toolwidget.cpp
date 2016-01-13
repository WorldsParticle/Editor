#include <qdebug.h>
#include "toolwidget.hpp"
#include "ui_toolwidget.h"

ToolWidget::ToolWidget(QWidget *parent) :
    QTabWidget(parent),
    _ui(new Ui::TabWidget),
    _conf(NULL)
{
    _ui->setupUi(this);
    makeConnections();
}

ToolWidget::~ToolWidget()
{
    delete _ui;
}

void    ToolWidget::makeConnections()
{
    connect(_ui->editWorldName, SIGNAL(textChanged(QString)), this, SLOT(setConfName(String)));
    connect(_ui->groupTerrain, SIGNAL(buttonClicked(int)), this, SLOT(setLandType(int)));
    connect(_ui->groupClimat, SIGNAL(buttonClicked(int)), this, SLOT(setClimatType(int)));
    connect(_ui->sliderWindPower, SIGNAL(valueChanged(int)), this, SLOT(setWindPower(int)));

    connect(_ui->buttonAddModel, SIGNAL(pressed()), this, SLOT(addModel()));
    connect(_ui->buttonDelModel, SIGNAL(pressed()), this, SLOT(delModel()));
}

void    ToolWidget::setConfiguration(Model::WorldConf *conf)
{
    if(!conf)
        return;

    _conf = conf;

    qDebug() << "la" ;
    _ui->editWorldName->setText(conf->name); // A REMOVE
    //_ui->groupClimat->button(static_cast<int>(conf->climattype))->setChecked(true); a faire autrement
    //_ui->groupClimat->button(static_cast<int>(conf->landtype))->setChecked(true); a faire autrement
    _ui->sliderWindPower->setValue(conf->windPower);

    // les mods a faire plus tard

}

void    ToolWidget::setConfName(const String &name) // ATTENTION A REMOVE (clef importante)
{
    if(_conf)
        _conf->name = name;
}

void    ToolWidget::setLandType(int typeId)
{
    //if(_conf) a refaire
    //    _conf->landtype = static_cast<Model::LANDTYPE>(typeId);
}

void    ToolWidget::setClimatType(int typeId)
{
    //if(_conf) a refaire
    //    _conf->climattype = static_cast<Model::CLIMATTYPE>(typeId);
}

void    ToolWidget::setWindPower(int power)
{
    if(_conf)
        _conf->windPower = power;
}

void    ToolWidget::addModel()
{
    //pop up window here
    //ajout d'un bouton, connection de son signal pressed au slot setCurrentModel
}

void    ToolWidget::delModel()
{

}

void    ToolWidget::setCurrentModel(String name)
{
    Model::Mod  *mod = _conf->mods.value(name);
    _ui->editModelName->text() = name;

    _ui->spinboxFreq->setValue(mod->apparitionRate);

    _ui->spinboxRotX->setValue(mod->angle.x());
    _ui->spinboxRotY->setValue(mod->angle.y());
    _ui->spinboxRotZ->setValue(mod->angle.z());

    _ui->spinboxScaleX->setValue(mod->scale.x());
    _ui->spinboxScaleY->setValue(mod->scale.y());
    _ui->spinboxScaleZ->setValue(mod->scale.z());
}
