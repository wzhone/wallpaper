#include "effect.h"

bool Effect::blur(HWND handle,
                  ACCENT_STATE state,
                  uint32_t color,
                  uint32_t show,
                  uint32_t unknow){

    HMODULE hUser = GetModuleHandle(L"user32.dll");
    if (!hUser) return false;

    pfnSetWindowCompositionAttribute
            setWindowCompositionAttribute =
        (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");

    if (!setWindowCompositionAttribute) return false;


    ACCENT_POLICY accent = { state, show,color,unknow };

    WINDOWCOMPOSITIONATTRIBDATA data;
    data.Attrib = WCA_ACCENT_POLICY;
    data.pvData = &accent;
    data.cbData = sizeof(accent);
    setWindowCompositionAttribute(handle, &data);

    return true;
}

