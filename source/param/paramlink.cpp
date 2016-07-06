#include "include/param/paramlink.hpp"
#include "include/param/intvaluelink.hpp"
#include "include/param/boolvaluelink.hpp"
#include <iostream>

namespace Editor
{

ParamLink::ParamLink(gen::Param *param) :
    m_param(param)
{

}

ParamLink   *ParamLink::createLink(gen::Param *param)
{
    ParamLink *link = nullptr;

    switch (param->type())
    {
    case gen::Param::INTVALUE:
        link = new IntValueLink(dynamic_cast<gen::IntValue *>(param));
        break;
    case gen::Param::BOOLVALUE:
        link = new BoolValueLink(dynamic_cast<gen::BoolValue *>(param));
        break;
    default:
        std::cout << "WARNING unknown param type " << param->type() << std::endl;
        break;
    }

    return link;
}

}
