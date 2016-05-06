#ifndef INTVALUELINK_H
#define INTVALUELINK_H

#include "paramlink.hpp"
#include "Generator/param/intvalue.hpp"
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>

namespace Editor
{

///
/// \brief The IntValueLink class is the link with IntValu generator param
///
class IntValueLink : public ParamLink
{
    Q_OBJECT
public:
    ///
    /// \brief IntValueLink constructor
    ///
    IntValueLink(gen::IntValue *param);

public slots:
    ///
    /// \brief changeValue
    /// \param value
    ///
    void changeValue(int value);

private:
    ///
    /// \brief m_layout
    ///
    QHBoxLayout m_layout;

    ///
    /// \brief m_label
    ///
    QLabel      m_label;

    ///
    /// \brief m_spinbox
    ///
    QSpinBox    m_spinbox;
};

}

#endif // INTVALUELINK_H
