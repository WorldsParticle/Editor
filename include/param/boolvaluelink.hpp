#ifndef BOOLVALUELINK_H
#define BOOLVALUELINK_H

#include "paramlink.hpp"
#include "Generator/param/boolvalue.hpp"
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>

namespace Editor
{

///
/// \brief The BoolValueLink class is the link with BoolValu generator param
///
class BoolValueLink : public ParamLink
{
    Q_OBJECT
public:
    ///
    /// \brief BoolValueLink constructor
    ///
    BoolValueLink(gen::BoolValue *param);

public slots:
    ///
    /// \brief changeValue
    /// \param value
    ///
    void changeValue(bool value);

private:
    ///
    /// \brief m_layout
    ///
    QHBoxLayout m_layout;

    ///
    /// \brief m_label
    ///
    QLabel      m_label;

    QCheckBox    m_checkbox;
};

}

#endif // BOOLVALUELINK_H
