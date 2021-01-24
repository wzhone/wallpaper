#include "lowermenu.h"
#include "ui_lowermenu.h"
#include "mainoperate.h"

#include <QMouseEvent>
#include <QCursor>
#include <QDebug>
#include <QDir>
#include <QMessageBox>


const char* button_qss = "QPushButton{\
        border:0px;\
        background:#eee;\
        color:#555;\
        font-family:'Microsoft Yahei';\
        font-size:13px;\
        text-align:left;\
        padding-left:30px;\
       }\
       QPushButton:hover{\
        background:#ddd;\
       }";

LowerMenu::LowerMenu(MainOperate *_main) :
    QWidget(0),
    main(_main),
    ui(new Ui::LowerMenu)
{
    ui->setupUi(this);

    //界面初始化
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ui->exit->setStyleSheet(button_qss);
    ui->rand_change->setStyleSheet(button_qss);

    //窗口适应frame大小
    this->setFixedSize(ui->frame->size());
    this->ui->frame->move(QPoint(0,0));
    setAttribute(Qt::WA_TranslucentBackground, true);      //设置为透明背景
}

void LowerMenu::showEvent(QShowEvent *event){
    QPoint p = QCursor::pos();
    QPoint pos(p.x() - this->size().width(),
               p.y() - this->size().height());
    this->move(pos);
    this->setFocus();
}
void LowerMenu::changeEvent(QEvent * event){
    QWidget::changeEvent(event);
    if (event->type()==QEvent::ActivationChange){
        qDebug()<<this->hasFocus();
        if (this->hasFocus())
            this->hide();

//        QObjectList list = children();
//        foreach (QObject *obj, list) {
//            QPushButton * b = qobject_cast<QPushButton*>(obj);
//            if(b){
//                qDebug() << b->hasFocus();
//            }
//        }


    }

}

LowerMenu::~LowerMenu()
{
    delete ui;
}

void LowerMenu::on_exit_clicked()
{
    main->end_process();
}
