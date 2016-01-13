#include "model.hpp"

Model::Model() :
    _WorldConfs()
{

}

Model::~Model()
{

}

Model::WorldConf*   Model::createWorldConf(const String &name, WorldConf *clone)
{
    WorldConf   *conf = NULL;

    if (_WorldConfs.contains(name))
        conf = _WorldConfs.value(name);
    else
    {
        conf = new WorldConf;
        if (clone) // a supprimer pour un constructeur par copie
        {
            conf->name  = clone->name;
            conf->climattype = clone->climattype;
            conf->landtype = clone->landtype;
            conf->windPower = clone->windPower;
            // mods a faire plus tard
        }
        else
        {
            conf->name  = name;
            conf->climattype = DEGAGE;
            conf->landtype = PLAINE;
            conf->windPower = 0;
        }
        _WorldConfs.insert(name, conf);
    }
    return conf;
}

Model::WorldConf*   Model::getWorldConfByName(String &confName) const
{
    return _WorldConfs.value(confName);
}

