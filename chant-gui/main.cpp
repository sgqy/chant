#include "chant.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chant w;
    w.show();

    return a.exec();
}
