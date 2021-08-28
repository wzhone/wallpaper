#include "tray.h"

Tray* Tray::instance(){
    static Tray* _inst = new Tray;
    return _inst;
}

void Tray::destory(){
    this->_trayIcon->hide();
    this->_trayMenu->hide();
}

void Tray::onTray(QSystemTrayIcon::ActivationReason reason){
    switch(reason){
    case QSystemTrayIcon::Context:
        //右击托盘图标
        break;
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        MainOperate::instance()->show();
        break;
    case QSystemTrayIcon::Trigger:
        //左键单击
        break;
    case QSystemTrayIcon::MiddleClick:
        //中键
        break;
    default:
        break;
    }
}

Tray::Tray() : QObject(0){

    this->_act_exit = new QAction(QStringLiteral("退出"));
    this->_act_hideshow = new QAction(QStringLiteral("隐藏/显示 桌面壁纸"));

    //action
    this->_trayMenu = new QMenu();

    this->_trayMenu->addAction(this->_act_exit);
    this->_trayMenu->addAction(this->_act_hideshow);

    //-

    this->_trayIcon = new QSystemTrayIcon(this);
    this->_trayIcon->setIcon(QIcon(":/logo/resource/img/logo.png"));
    this->_trayIcon->setToolTip("WallPaper");
    this->_trayIcon->setContextMenu(this->_trayMenu);

    //--

    //--
    connect(_trayIcon,&QSystemTrayIcon::activated,this,&Tray::onTray);

    connect(this->_act_exit,&QAction::triggered,[](){
        QApplication::instance()->quit();
    });
    connect(this->_act_hideshow,&QAction::triggered,[](){
        WallaperManager::instance()->triggerVisible();
    });

    //
    this->_trayIcon->show();
}
