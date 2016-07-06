#include "include/param/boolvaluelink.hpp"

#include <QDebug>

namespace Editor
{

BoolValueLink::BoolValueLink(gen::BoolValue *param) :
    ParamLink(param),
    m_layout(this),
    m_label(this),
    m_checkbox(this)
{
    this->setLayout(&m_layout);
    m_layout.addWidget(&m_label);
    m_layout.addWidget(&m_checkbox);

    m_label.setText(param->name().c_str());

    m_checkbox.setChecked(param->value());

    connect(&m_checkbox, SIGNAL(toggled(bool)), this, SLOT(changeValue(bool)));
}

void    BoolValueLink::changeValue(bool value)
{
    dynamic_cast<gen::BoolValue *>(m_param)->setValue(value);
}

}

