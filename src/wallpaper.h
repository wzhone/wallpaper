#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QWidget>
#include <Windows.h>
#include <tchar.h>
#include <string>

class UnderExplore;

namespace Ui {
class Wallpaper;
}

//桌面壁纸类
class Wallpaper : public QWidget{
    Q_OBJECT

public:
    explicit Wallpaper(QWidget *parent = 0);
    ~Wallpaper();

    void display(QString path);
    void display(QImage path);

    QRect screen;

public slots:
    void hide();

private:
    Ui::Wallpaper *ui;

};

class WallaperManager: public QWidget{
    Q_OBJECT

public:
    ~WallaperManager(){}
    static WallaperManager* instance();

    void destory();
    Wallpaper** wallpapers(){ return _wallWindow; }
    int countWallpaper(){ return _nWindow; }
    bool init();

    bool getVisible(){return this->show;}
    void setVisible(bool);
    void triggerVisible();

private:

    bool show = true;
    Wallpaper** _wallWindow; //窗口数组
    int _nWindow = 0;    //屏幕数量
    WallaperManager();
};


//这个类主要是把窗口放置到桌面图标底下
class UnderExplorer{
public:

    static bool init();

    //执行窗口放置 动作
    static bool put(std::wstring&& window_name);
    static bool put(WId handle);
    static bool put(HWND app);

    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
    static bool refresh();

private:

    static HWND ProgmanManager;
    static HWND MiddleW; //新生成的WorkerW
    static HWND SHELLDLL;
};

#endif // WALLPAPER_H
