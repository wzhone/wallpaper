#include "mainoperate.h"
#include <QApplication>
#include <QSharedMemory>
#include "wallpaper.h"
#include "tray.h"
#include "wallpaper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainOperate w;

    //防止多开
    QSharedMemory shared_memory;
    shared_memory.setKey(QString("wallpaper-inst"));//设置固定共享内存段的key值
    if(shared_memory.attach() || !shared_memory.create(1)){
        return 120;
    }

    // 初始化桌面壁纸
    if (!WallaperManager::instance()->init()){
        return 128;
    }

    // 初始化托盘
    Tray::instance();


    // 初始化全局快捷键
    //HotKey::instance()->init();

    //初始化窗口模糊效果已移动到showEvent


    w.show();
    return a.exec();
}
