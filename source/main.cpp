#include "include/mainwindow.hpp"
#include <QApplication>
#include <bullet/btBulletCollisionCommon.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Editor::MainWindow w;
    w.show();

    return a.exec();
}
