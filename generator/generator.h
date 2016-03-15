#ifndef GENERATOR_H
#define GENERATOR_H

namespace MAP
{
class Map;
}

namespace GEN
{

class Generator
{
public:
    Generator();

    MAP::Map    *generate(double xMax, double yMax, unsigned int zoneNumber);

    virtual void    run() = 0;

    inline MAP::Map *map() const
    { return _map; }

protected:
    MAP::Map    *_map;

    unsigned int    _zoneNumber;
    double          _xMax;
    double          _yMax;
};

}

#endif // GENERATOR_H
