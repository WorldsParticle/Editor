#include "include/param/paramlink.hpp"
#include "include/param/intvaluelink.hpp"

namespace Editor
{

ParamLink::ParamLink(gen::Param *param) :
    m_param(param)
{

}

ParamLink   *ParamLink::createLink(gen::Param *param)
{
    ParamLink *link = nullptr;

    if (param->type() == gen::Param::intvalue)
        link = new IntValueLink(dynamic_cast<gen::IntValue *>(param));

    return link;
}

}
