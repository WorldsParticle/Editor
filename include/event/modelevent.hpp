#ifndef MODELADDEVENT_H
#define MODELADDEVENT_H

#include <QEvent>
#include <QString>

namespace Editor
{

class ModelEvent : public QEvent
{
public:
    ModelEvent(const QString &path) : QEvent(Model_add), m_path(path) {}

    inline const QString  &path()
    { return m_path; }

    static const QEvent::Type   Model_add = static_cast<QEvent::Type>(4200);

protected:
    const QString    m_path;
};

}

#endif // MODELADDEVENT_H
