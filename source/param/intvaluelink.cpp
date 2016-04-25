#include "include/param/intvaluelink.hpp"

#include <QDebug>

namespace Editor
{

IntValueLink::IntValueLink(gen::IntValue *param) :
    ParamLink(param),
    m_layout(this),
    m_label(this),
    m_spinbox(this)
{
    this->setLayout(&m_layout);
    m_layout.addWidget(&m_label);
    m_layout.addWidget(&m_spinbox);

    m_label.setText(param->name().c_str());

    m_spinbox.setMinimum(param->minValue());
    m_spinbox.setMaximum(param->maxValue());
    m_spinbox.setValue(param->value());

    connect(&m_spinbox, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
}

void    IntValueLink::changeValue(int value)
{
    dynamic_cast<gen::IntValue *>(m_param)->setValue(value);
}

}
