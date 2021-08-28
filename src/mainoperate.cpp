#include "mainoperate.h"
#include "ui_mainoperate.h"
#include "tray.h"

MainOperate* __Inst = nullptr;


MainOperate* MainOperate::instance(){
    return __Inst;
}

MainOperate::MainOperate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainOperate)
{
    ui->setupUi(this);
    __Inst = this;


//    HWND cdn = FindWindowW(NULL,L"此电脑");
//    qDebug()<<cdn;
//    Effect::blur(cdn,TRANS);

    /* bg : Frame
        防止因为透明度的原因导致窗口不能选择*/

    this->setStyleSheet("#centralWidget{background:rgba(255,255,255,0.5)}");
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //
    this->ui->tabWidget->tabBar()->hide();
    connect(this->ui->item1,&QPushButton::clicked,this,&MainOperate::onItemClicked);
    connect(this->ui->item2,&QPushButton::clicked,this,&MainOperate::onItemClicked);
    connect(this->ui->item3,&QPushButton::clicked,this,&MainOperate::onItemClicked);
    connect(this->ui->item4,&QPushButton::clicked,this,&MainOperate::onItemClicked);
    connect(this->ui->item5,&QPushButton::clicked,this,&MainOperate::onItemClicked);

}

MainOperate::~MainOperate(){
    //清理托盘数据
    Tray::instance()->destory();

    //清理壁纸数据
    WallaperManager::instance()->destory();

    delete ui;
}


void MainOperate::onItemClicked()
{
//    QObject* s = sender();
//    QString name =  s->objectName();
//    if (name == "item1"){
//        this->ui->tabWidget->setCurrentIndex(0);
//    }
//    if (name == "item2"){
//        this->ui->tabWidget->setCurrentIndex(1);
//    }

}

//拖拽移动
void MainOperate::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        mMoving = true;
        mLastMousePosition = event->globalPosition();
        //Effect::blur((HWND)this->winId(),BLUR1);
    }
}

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

void MainOperate::showEvent(QShowEvent *event){
    Effect::blur((HWND)this->winId(),BLUR1);
}


