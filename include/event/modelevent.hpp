#ifndef MODELADDEVENT_H
#define MODELADDEVENT_H

#include <QEvent>
#include <QString>

namespace Editor
{

///
/// \brief The ModelEvent class
///
class ModelEvent : public QEvent
{
public:
    ///
    /// \brief ModelEvent constructor
    ///
    ModelEvent(const QString &path) : QEvent(Model_add), m_path(path) {}

    ///
    /// \brief path getter
    ///
    inline const QString  &path()
    { return m_path; }

    ///
    /// \brief Model_add, represent the type of the event
    ///
    static const QEvent::Type   Model_add = static_cast<QEvent::Type>(4200);

protected:
    ///
    /// \brief path to the model
    ///
    const QString    m_path;
};

}

#endif // MODELADDEVENT_H
