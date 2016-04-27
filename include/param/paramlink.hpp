#ifndef PARAMLINK_H
#define PARAMLINK_H

#include <QWidget>
#include "Generator/param/param.hpp"

namespace Editor
{

///
/// \brief The ParamLink class is used to link the custom param from Generator to Qt interactive params
///
class ParamLink : public QWidget
{
public:
    ///
    /// \brief createLink allow user to create a custom param
    /// \param param
    /// \return the new param
    ///
    static  ParamLink   *createLink(gen::Param *param);

protected:
    ///
    /// \brief ParamLink constructor, protected to force the use of createLink
    ///
    ParamLink(gen::Param *param);

    gen::Param  *m_param;
};

}

#endif // PARAMLINK_H
