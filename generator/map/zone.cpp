#include "map/zone.h"

namespace MAP
{

int Zone::indexMax = 0;
Zone::Zone(double x, double y) :
    index(indexMax),
    point(x, y),
    water(false),
    ocean(false),
    coast(false),
    border(false),
    elevation(0.0),
    moisture(0.0),
    neighbors(),
    borders(),
    corners()
{
    ++indexMax;
}

}
