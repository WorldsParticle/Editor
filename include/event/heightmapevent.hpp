#ifndef HEIGHTMAPADDEVENT_H
#define HEIGHTMAPADDEVENT_H

#include <QEvent>

namespace map
{
class HeightMap;
}

namespace Editor
{

class HeightMapEvent : public QEvent
{
public:
    HeightMapEvent(map::HeightMap &map) : QEvent(HeightMap_add), m_map(map) {}

    inline map::HeightMap   &heightMap()
    { return m_map; }

    static const QEvent::Type   HeightMap_add = static_cast<QEvent::Type>(4201);

protected:
    map::HeightMap  &m_map;
};

}

#endif // HEIGHTMAPADDEVENT_H
