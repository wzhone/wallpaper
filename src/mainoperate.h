#ifndef MAINOPERATE_H
#define MAINOPERATE_H

#include <QMainWindow>
#include <QDebug>
#include <Windows.h>
#include <tchar.h>
#include <QMouseEvent>
#include <QGraphicsEffect>
#include <QPainter>
#include <QtMath>
#include <QDialog>
#include <QFileInfoList>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSystemTrayIcon>
#include <QDir>
#include <random>
#include <algorithm>

#include "effect.h"
#include "wallpaper.h"
#include "lowermenu.h"
#include "hotkey.h"
#include "lowermenu.h"

namespace Ui {
class MainOperate;
}

extern MainOperate* MainInst; //主窗口实例

class MainOperate : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainOperate(QWidget *parent = 0);
    ~MainOperate();

    void end_process();//关闭窗口,清理资源

    //getter & setter
    Wallpaper** wallpapers(){ return _wallWindow; }
    int countWallpaper(){ return _nWindow; }


private slots:
    void onTray(QSystemTrayIcon::ActivationReason);
    void onItemClicked();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


private:
    Ui::MainOperate *ui;

    //拖拽移动
    QPointF mLastMousePosition;
    bool mMoving;

    //壁纸
    Wallpaper** _wallWindow; //窗口数组
    int _nWindow = 0;    //屏幕数量

    //托盘
    QSystemTrayIcon* tray;
    LowerMenu* menu;

    void _initWallpaper();


};

#endif // MAINOPERATE_H
