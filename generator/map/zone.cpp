#include "map/zone.h"

namespace MAP
{

int Zone::indexMax = 0;
Zone::Zone(double x, double y) :
    index(indexMax),
    point(x, y),
    neighbors(),
    borders(),
    corners()
{
    ++indexMax;
}

}
