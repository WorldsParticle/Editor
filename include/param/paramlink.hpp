#ifndef PARAMLINK_H
#define PARAMLINK_H

#include <QWidget>
#include "Generator/param/param.hpp"

namespace Editor
{

class ParamLink : public QWidget
{
public:
    static  ParamLink   *createLink(gen::Param *param);

protected:
    ParamLink(gen::Param *param);

    gen::Param  *m_param;
};

}

#endif // PARAMLINK_H
