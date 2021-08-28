#include "wallpaper.h"
#include "ui_wallpaper.h"
#include <QMessageBox>
#include <QScreen>

Wallpaper::Wallpaper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wallpaper)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); //无边框

    //设置Label
    ui->show->setScaledContents(true); //控件自适应
}

Wallpaper::~Wallpaper()
{
    delete ui;
}
void Wallpaper::hide(){
    QWidget::hide();
    UnderExplorer::refresh();
}

void Wallpaper::display(QString path){
    QImage image;
    image.load(path);
    this->display(image);
}

void Wallpaper::display(QImage img){
    ui->show->clear();
    ui->show->setPixmap(QPixmap::fromImage(img));
}


//=========================================================================

HWND UnderExplorer::ProgmanManager=nullptr;
HWND UnderExplorer::MiddleW=nullptr;
HWND UnderExplorer::SHELLDLL=nullptr;

bool UnderExplorer::put(std::wstring&& window_name){
    HWND w = ::FindWindow(nullptr, window_name.c_str());
    if (w == nullptr){
        qDebug()<<"The window '" << window_name.c_str() << "' was not found";
        return false;
    }
    return put(w);
}
bool UnderExplorer::put(WId handle){
    return put(reinterpret_cast<HWND>(handle));
}
bool UnderExplorer::put(HWND app){
    //方案1 ： 最底层方案(放在管理器中) win+tab会导致失效
    //SendMessage(MiddleW, 16, 0, 0); //关闭生成的WorkerW
    //SetParent(app, Progman);//将窗口放在最底层

    //方案2：中间WorkerW层方案
    //窗口不可交互，强行关闭程序不能马上消失
    SetParent(app, MiddleW);//将窗口放在中间新生成的那个workerw层

    //方案3：shelldll方案,会导致桌面不能用（或许可以当锁屏）
    //SetParent(app,UnderExplorer::SHELLDLL);
    return true;
}
bool UnderExplorer::init(){
    UnderExplorer::ProgmanManager = ::FindWindow(_T("Progman"), _T("Program Manager"));
    if (UnderExplorer::ProgmanManager == nullptr){
        qDebug()<<"Program Manager was NOT FOUND";
        return false;
    }
    //SendMessageW(UnderExplorer::Progman, 0x052c, 1, 0); //关闭WorkerW
    SendMessageW(UnderExplorer::ProgmanManager, 0x052c, 0, 0); //生成WorkerW
    EnumWindows(&UnderExplorer::EnumWindowsProc,0);
    return true;
}
BOOL CALLBACK UnderExplorer::EnumWindowsProc(HWND hwnd,LPARAM){

    char window_class_name[256]={0};
    GetClassNameA(hwnd, window_class_name, sizeof(window_class_name));//获取窗口类名

    //筛选所有WorkerW
    if (strcmp(window_class_name,"WorkerW")!=0)
        return TRUE;

    if (IsWindowVisible(hwnd)){ //有多个workerw
        HWND window_hwnd = FindWindowExA(hwnd, 0, "SHELLDLL_DefView", nullptr);
        if (window_hwnd != nullptr){
            UnderExplorer::SHELLDLL = FindWindowExA(window_hwnd, 0, "SysListView32", nullptr);
            return TRUE;
        }else{
            //筛选出 可见的WorkerW 并且没有 shelldll子窗口的WorkerW
            UnderExplorer::MiddleW = hwnd;
            if (UnderExplorer::SHELLDLL==nullptr)
                //找不到SHELLDLL就继续遍历
                return TRUE;
            else
                return FALSE;
        }
    }
    return TRUE;
}
bool UnderExplorer::refresh(){
    ShowWindow(UnderExplorer::MiddleW,SW_HIDE);
    ShowWindow(UnderExplorer::MiddleW,SW_SHOW);
    return true;
}

//=========================================================================

WallaperManager *WallaperManager::instance(){
    static WallaperManager* _inst = new WallaperManager;
    return _inst;
}

void WallaperManager::destory(){
    for(int i=0;i<_nWindow;i++){
        Wallpaper* window = this->_wallWindow[i];
        if (window!=nullptr){
            window->hide();
        }
    }
}

bool WallaperManager::init(){
    if (!UnderExplorer::init()){
        QMessageBox::warning(0,"初始化错误","桌面壁纸初始化失败！");
        return false;
    }

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

    for(int i=0;i<_nWindow;i++){
        this->_wallWindow[i]->show();
    }
    return true;
}

void WallaperManager::setVisible(bool v){
    this->show = v;
    for(int i=0;i<_nWindow;i++){
        if (show){
            this->_wallWindow[i]->show();
        }else{
            this->_wallWindow[i]->hide();
        }
    }
}

void WallaperManager::triggerVisible(){
    this->setVisible(!show);
}

WallaperManager::WallaperManager(){}
