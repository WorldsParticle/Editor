#ifndef INTVALUELINK_H
#define INTVALUELINK_H

#include "paramlink.hpp"
#include "Generator/param/intvalue.hpp"
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>

namespace Editor
{

class IntValueLink : public ParamLink
{
    Q_OBJECT
public:
    IntValueLink(gen::IntValue *param);

public slots:
    void changeValue(int value);

private:
    QHBoxLayout m_layout;
    QLabel      m_label;
    QSpinBox    m_spinbox;
};

}

#endif // INTVALUELINK_H
