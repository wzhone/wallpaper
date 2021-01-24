#ifndef HOTKEY_H
#define HOTKEY_H

#include <Windows.h>
#include <QObject>
#include <algorithm>


enum key{
    win_left   = 91,
    win_righ   = 92,
    insert_k   = 45,
    delete_k   = 46,

    shift_left = 160,
    shift_righ = 161,
    ctrl_left  = 162,
    ctrl_righ  = 163,
    alt_left   = 164,
    alt_righ   = 165,


};

class HotKey : public QObject
{
    Q_OBJECT

public:
    static HotKey *getInstance();

    int init();

    bool use_kb_hotkey = false;

    bool s_shift = false;
    bool s_ctrl = false;
    bool s_alt = false;
    bool s_win = false;


    bool Key(int);
signals:
    int check_macro();

private slots:
    int callback();

private:
    HHOOK kb_hook = 0; //键盘钩子
    bool key[255]={false};


    HotKey();
    static HotKey* HKI;
    static LRESULT CALLBACK kb_proc(int, WPARAM, LPARAM);
};

#endif // HOTKEY_H
