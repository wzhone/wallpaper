#include "mainoperate.h"
#include "ui_mainoperate.h"

MainOperate* MainInst = nullptr;


MainOperate::MainOperate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainOperate)
{
    ui->setupUi(this);
    MainInst = this;

    //初始化桌面壁纸
    if (!UnderExplorer::init()){
        QMessageBox::warning(this,"初始化错误","壁纸初始化失败！");
        this->end_process();
        return;
    }else{
        this->_initWallpaper();
        for(int i=0;i<_nWindow;i++){
            (this->_wallWindow[i])->show();
        }
    }

    //初始化主窗口UI
    Effect::blur((HWND)this->winId(),BLUR1);

//    HWND cdn = FindWindowW(NULL,L"此电脑");
//    qDebug()<<cdn;
//    Effect::blur(cdn,TRANS);

    /* bg : Frame
        防止因为透明度的原因导致窗口不能选择*/
    this->setStyleSheet("#centralWidget{background:rgba(0,0,0,0.1)}");
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);


    //初始化系统托盘
    menu=new LowerMenu(this);
    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(":/logo/resource/img/logo.png"));
    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(onTray(QSystemTrayIcon::ActivationReason)));
    tray->show();

    //
    this->ui->tabWidget->tabBar()->hide();
    connect(this->ui->item1,&QPushButton::clicked,this,&MainOperate::onItemClicked);
    connect(this->ui->item2,&QPushButton::clicked,this,&MainOperate::onItemClicked);
    connect(this->ui->item3,&QPushButton::clicked,this,&MainOperate::onItemClicked);
    connect(this->ui->item4,&QPushButton::clicked,this,&MainOperate::onItemClicked);
    connect(this->ui->item5,&QPushButton::clicked,this,&MainOperate::onItemClicked);


//    //hotkey
//    HotKey::getInstance()->init();

}

MainOperate::~MainOperate(){
    delete ui;
}


void MainOperate::end_process(){
    //清理资源
    this->hide();
    for(int i=0;i<_nWindow;i++){
        Wallpaper* window = this->_wallWindow[i];
        if (window!=nullptr)
            window->hide();
    }
    this->tray->hide();
    this->menu->hide();
    this->close();
}

void MainOperate::onTray(QSystemTrayIcon::ActivationReason reason){
    switch(reason){
    case QSystemTrayIcon::Context: //右击托盘图标
        menu->show();
        menu->activateWindow();
        break;
    case QSystemTrayIcon::DoubleClick: //双击托盘图标
        this->show();
        break;
    case QSystemTrayIcon::Trigger:
        //左键单击
    case QSystemTrayIcon::MiddleClick:
        //中建
    default:
        break;
    }
}

void MainOperate::onItemClicked()
{
    QObject* s = sender();
    QString name =  s->objectName();
    if (name == "item1"){
        this->ui->tabWidget->setCurrentIndex(0);
    }
    if (name == "item2"){
        this->ui->tabWidget->setCurrentIndex(1);
    }

}

//拖拽移动
void MainOperate::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        mMoving = true;
        mLastMousePosition = event->globalPosition();
       // Effect::blur((HWND)this->winId(),BLUR1);
    }
}
int i=0;

void MainOperate::mouseMoveEvent(QMouseEvent* event){
    if(mMoving && event->buttons().testFlag(Qt::LeftButton)){

        if (mLastMousePosition != event->globalPosition()){
             //Effect::blur((HWND)this->winId(),BLUR1);
            QPointF re = this->pos() + (event->globalPosition() - mLastMousePosition);
            this->move((int)re.x(),(int)re.y());
            mLastMousePosition = event->globalPosition();
        }


    }
}
void MainOperate::mouseReleaseEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        mMoving = false;
        //Effect::blur((HWND)this->winId(),BLUR2);
    }
}


void MainOperate::_initWallpaper()
{
    //检测显示屏数
    QList<QScreen*> screen_list= QGuiApplication::screens();
    this->_nWindow = screen_list.count();

    //初始化壁纸
    this->_wallWindow=new Wallpaper*[this->_nWindow];

    for(int i=0;i<_nWindow;i++){

        this->_wallWindow[i] = new Wallpaper();
        Wallpaper* window = this->_wallWindow[i];

        window->display(":/inbg/resource/bg-img/bg.jpg");//设置默认图片

        window->setGeometry(screen_list[i]->geometry());//设置位置和大小
        UnderExplorer::put(window->winId());//下潜
    }
}
