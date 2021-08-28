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
#include "hotkey.h"

namespace Ui {
class MainOperate;
}


class MainOperate : public QMainWindow
{
    Q_OBJECT

public:

    static MainOperate* instance();



    explicit MainOperate(QWidget *parent = 0);
    ~MainOperate();


private slots:
    void onItemClicked();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void showEvent(QShowEvent *event);

private:
    Ui::MainOperate *ui;

    //拖拽移动
    QPointF mLastMousePosition;
    bool mMoving;



};

#endif // MAINOPERATE_H
