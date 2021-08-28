#include "hotkey.h"
#include "mainoperate.h"

HotKey* HotKey::HKI = nullptr;

HotKey::HotKey(){}

HotKey* HotKey::instance(){
    if (HKI==nullptr)
        HKI = new HotKey();
    return HKI;
}

LRESULT CALLBACK HotKey::kb_proc(int code, WPARAM w, LPARAM l){
    HotKey* that = HotKey::instance();
    PKBDLLHOOKSTRUCT p = reinterpret_cast<PKBDLLHOOKSTRUCT>(l);

    /*
     * 按键
     * WM_KEYDOWN WM_KEYUP
     * WM_SYSKEYDOWN WM_SYSKEYUP
        up 二进制位最后一位是 1
        down            是 0
    */

    DWORD v = p->vkCode;
    qDebug() << v;


    //shift alt ctrl
    switch(v){
        case win_left:
        case win_righ:
            that->s_win = !(w&0x01);
        break;
        case shift_left:
        case shift_righ:
            that->s_shift = !(w&0x01);
            break;
        case ctrl_left:
        case ctrl_righ:
            that->s_ctrl = !(w&0x01);
        break;
        case alt_left:
        case alt_righ:
            that->s_alt = !(w&0x01);
        break;
        default:
        break;
    }

    emit that->check_macro();
    return CallNextHookEx(that->kb_hook, code, w, l);
}


int HotKey::init(){

    //设置键盘钩子
    kb_hook = SetWindowsHookEx(
            WH_KEYBOARD_LL,
            static_cast<HOOKPROC>(kb_proc),
            GetModuleHandle(nullptr), //　不能为NULL，否则失败
            0);
    if (kb_hook == nullptr){
        qDebug()<<"Register Keyboard Fail error:"<<GetLastError();
        return false;
    }else{
        QObject::connect(this,SIGNAL(check_macro()),
                this,SLOT(callback()),
                Qt::QueuedConnection);
        return true;
    }
}

int HotKey::callback(){

//    if (s_ctrl && s_alt){
//        if (MainInst->isVisible()) {
//            MainInst->hide();
//        }else{
//            MainInst->show();
//        }
//    }

    return 0;
}

bool HotKey::Key(int v){
//    //数字按键
//    if (v > 47 && v < 58) {
//        return key[v];
//    }
//    //小键盘
//    if (v >95 && v < 106) {
//        return key[v-48];
//    }
//    //字母按键
//    if (v >64 && v < 91) {
//        short capslock = GetKeyState(VK_CAPITAL);
//        short shift = GetKeyState(VK_SHIFT);
//        if ((capslock == 0 || capslock == -128) && shift != -128)
//            var = 32;
//        return key[v + var];
//    }
return true;


}

