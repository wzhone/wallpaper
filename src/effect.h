#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include <QWidget>

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <tchar.h>
#include <QDebug>
#include <string>
#include <Windows.h>
#include <stdint.h>

using std::wstring;


typedef enum
{
    WCA_UNDEFINED = 0,
    WCA_NCRENDERING_ENABLED = 1,
    WCA_NCRENDERING_POLICY = 2,
    WCA_TRANSITIONS_FORCEDISABLED = 3,
    WCA_ALLOW_NCPAINT = 4,
    WCA_CAPTION_BUTTON_BOUNDS = 5,
    WCA_NONCLIENT_RTL_LAYOUT = 6,
    WCA_FORCE_ICONIC_REPRESENTATION = 7,
    WCA_EXTENDED_FRAME_BOUNDS = 8,
    WCA_HAS_ICONIC_BITMAP = 9,
    WCA_THEME_ATTRIBUTES = 10,
    WCA_NCRENDERING_EXILED = 11,
    WCA_NCADORNMENTINFO = 12,
    WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
    WCA_VIDEO_OVERLAY_ACTIVE = 14,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
    WCA_DISALLOW_PEEK = 16,
    WCA_CLOAK = 17,
    WCA_CLOAKED = 18,
    WCA_ACCENT_POLICY = 19,
    WCA_FREEZE_REPRESENTATION = 20,
    WCA_EVER_UNCLOAKED = 21,
    WCA_VISUAL_OWNER = 22,
    WCA_LAST = 23
} WINDOWCOMPOSITIONATTRIB;

typedef struct
{
    WINDOWCOMPOSITIONATTRIB Attrib;
    PVOID pvData;
    SIZE_T cbData;
} WINDOWCOMPOSITIONATTRIBDATA;

typedef enum
{
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,

    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,  TRANS =2,
    ACCENT_ENABLE_BLURBEHIND = 3,           BLUR1 =3,
    ACCENT_ENABLE_ACRYLICBLURBEHIND  = 4,   BLUR2 =4, //win11有问题

    ACCENT_ENABLE_HOSTBACKDROP = 5,
    ACCENT_INVALID_STATE = 6

} ACCENT_STATE;


typedef struct _ACCENT_POLICY

{
    ACCENT_STATE AccentState;

    /*
        2   使用颜色(参数2)
        32  左边框阴影
        64  上边框阴影
        128 右边框阴影
        256 下边框阴影（单独使用不生效）
    */
    DWORD AccentFlags;


    DWORD GradientColor;
    DWORD AnimationId;
} ACCENT_POLICY;

typedef BOOL(WINAPI*pfnSetWindowCompositionAttribute)(HWND,WINDOWCOMPOSITIONATTRIBDATA*);



class Effect{
public:
    static bool blur(HWND,
         ACCENT_STATE s,
         uint32_t color=0x00000011,
         uint32_t show= 256+128+64+32+2,
         uint32_t unknow=0
    );

};

#endif // EFFECT_H
