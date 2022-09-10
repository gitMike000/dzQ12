#include "imggui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImgGUI w;
    w.show();
    return a.exec();
}
