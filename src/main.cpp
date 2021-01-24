#include "mainoperate.h"
#include <QApplication>
#include "wallpaper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainOperate w;
    w.show();


    return a.exec();
}
