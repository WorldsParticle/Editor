#ifndef TOOLWIDGET_HPP
#define TOOLWIDGET_HPP

#include <QWidget>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <Engine/Core.hpp>

namespace Ui {
class ToolWidget;
}

namespace Editor
{

class ToolWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief ToolWidget default constructor
    /// \param parent is the top widget
    ///
    explicit ToolWidget(QWidget *parent = 0);

    ///
    /// \brief Destructor
    ///
    ~ToolWidget();

    ///
    /// \brief setEngine set the current engine
    /// \param engine is the new one
    ///
    inline void    setEngine(Engine::Core *engine)
    { _engine = engine; }

public slots:
    ///
    /// \brief switchVisibility is a slot which switch the _ui->tabwidget visibility
    ///
    void    switchVisibility();

    ///
    /// \brief importModel import a model to the scene. Maybe have to remove this methode in the mainWindow
    ///
    void    importModel();

    ///
    /// \brief launchGenerator
    ///
    void    launchGenerator();


protected:
    ///
    /// \brief paintEvent override, used for paint a transparent background
    /// \param e
    ///
    virtual void    paintEvent(QPaintEvent *e);


private:
    ///
    /// \brief _ui contain some ui elements which are defined in toolwidget.ui
    ///
    Ui::ToolWidget      *_ui;

    ///
    /// \brief _slideAnimation is used for having a smooth animation when switching the _ui->tabwidget visibility
    ///
    QPropertyAnimation  *_slideAnimation;

    ///
    /// \brief _engine is the worldsparticle engine, where the magic happen
    ///
    Engine::Core        *_engine;
};

}

#endif // TOOLWIDGET_HPP
