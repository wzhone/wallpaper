#ifndef TRAY_H
#define TRAY_H

#include <QObject>
#include <QMouseEvent>
#include <QCursor>
#include <QDebug>
#include <QDir>
#include <QListWidgetItem>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QApplication>
#include <QMenu>

#include "mainoperate.h"

class Tray : public QObject
{
    Q_OBJECT
public:

    static Tray* instance();

    //清理打开的资源
    void destory();

signals:

private slots:
    void onTray(QSystemTrayIcon::ActivationReason);

private:

    explicit Tray();
    QSystemTrayIcon* _trayIcon;  //托盘
    QMenu*        _trayMenu;  //点击托盘弹出的窗口

    //Menu Action
    QAction* _act_exit;
    QAction* _act_hideshow;


};

#endif // TRAY_H
