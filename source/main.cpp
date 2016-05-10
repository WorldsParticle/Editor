#include "include/mainwindow.hpp"
#include <QApplication>
#include <stdexcept>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try
    {
        Editor::MainWindow w;
        w.show();
    } catch (std::runtime_error &err)
    {
        std::cout << err.what() << std::endl;
        return EXIT_FAILURE;
    }
    return a.exec();
}
