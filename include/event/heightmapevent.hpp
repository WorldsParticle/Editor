#ifndef HEIGHTMAPADDEVENT_H
#define HEIGHTMAPADDEVENT_H

#include <QEvent>

namespace map
{
class HeightMap;
}

namespace Editor
{

///
/// \brief The HeightMapEvent class
///
class HeightMapEvent : public QEvent
{
public:
    ///
    /// \brief HeightMapEvent constructor
    ///
    HeightMapEvent(map::HeightMap &heightMap) : QEvent(HeightMap_add), m_heightMap(heightMap) {}

    ///
    /// \brief heightMap getter
    ///
    inline map::HeightMap   &heightMap()
    { return m_heightMap; }

    ///
    /// \brief HeightMap_add, represent the type of the event
    ///
    static const QEvent::Type   HeightMap_add = static_cast<QEvent::Type>(4201);

protected:
    ///
    /// \brief the heightmap
    ///
    map::HeightMap  &m_heightMap;
};

}

#endif // HEIGHTMAPADDEVENT_H
