#include "chuan.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chuan w;
    w.show();

    return a.exec();
}
