#include "keymapper.h"

#include <X11/keysymdef.h>
#include <X11/Intrinsic.h>

KeyMapper::KeyMapper() {
    m_keyMap[ Qt::Key_Escape ] = XK_Escape;
    m_keyMap[ Qt::Key_Tab ] = XK_Tab;
    m_keyMap[ Qt::Key_Backtab ] = XK_ISO_Left_Tab;
    m_keyMap[ Qt::Key_Backspace ] = XK_BackSpace;
    m_keyMap[ Qt::Key_Return ] = XK_Return;
    m_keyMap[ Qt::Key_Insert ] = XK_Insert;
    m_keyMap[ Qt::Key_Delete ] = XK_Delete;
    m_keyMap[ Qt::Key_Pause ] = XK_Pause;
    m_keyMap[ Qt::Key_Print ] = XK_Print;
    m_keyMap[ Qt::Key_SysReq ] = 0x1005FF60;

    m_keyMap[ Qt::Key_Home ] = XK_Home;
    m_keyMap[ Qt::Key_End ] = XK_End;
    m_keyMap[ Qt::Key_Left ] = XK_Left;
    m_keyMap[ Qt::Key_Up ] = XK_Up;
    m_keyMap[ Qt::Key_Right ] = XK_Right;
    m_keyMap[ Qt::Key_Down ] = XK_Down;
    m_keyMap[ Qt::Key_PageUp ] = XK_Prior;
    m_keyMap[ Qt::Key_PageDown ] = XK_Next;

    m_keyMap[ Qt::Key_Shift ] = XK_Shift_L;
    m_keyMap[ Qt::Key_Control ] = XK_Control_L;
    m_keyMap[ Qt::Key_Meta ] = XK_Meta_L;
    m_keyMap[ Qt::Key_Alt ] = XK_Alt_L;
    m_keyMap[ Qt::Key_CapsLock ] = XK_Caps_Lock;
    m_keyMap[ Qt::Key_NumLock ] = XK_Num_Lock;
    m_keyMap[ Qt::Key_ScrollLock ] = XK_Scroll_Lock;
    m_keyMap[ Qt::Key_Super_L ] = XK_Super_L;
    m_keyMap[ Qt::Key_Super_R ] = XK_Super_R;
    m_keyMap[ Qt::Key_Menu ] = XK_Menu;
    m_keyMap[ Qt::Key_Hyper_L ] = XK_Hyper_L;
    m_keyMap[ Qt::Key_Hyper_R ] = XK_Hyper_R;
    m_keyMap[ Qt::Key_Help ] = XK_Help;
    m_keyMap[ Qt::Key_F11 ] = 0x1005FF10;
    m_keyMap[ Qt::Key_F12 ] = 0x1005FF11;

    m_keyMap[ Qt::Key_Space ] = XK_space;
    m_keyMap[ Qt::Key_Enter ] = XK_KP_Enter;
    m_keyMap[ Qt::Key_F1 ] = XK_KP_F1;
    m_keyMap[ Qt::Key_F2 ] = XK_KP_F2;
    m_keyMap[ Qt::Key_F3 ] = XK_KP_F3;
    m_keyMap[ Qt::Key_F4 ] = XK_KP_F4;
    m_keyMap[ Qt::Key_Clear ] = XK_KP_Begin;

    m_keyMap[ Qt::Key_0 ] = XK_0;
    m_keyMap[ Qt::Key_1 ] = XK_1;
    m_keyMap[ Qt::Key_2 ] = XK_2;
    m_keyMap[ Qt::Key_3 ] = XK_3;
    m_keyMap[ Qt::Key_4 ] = XK_4;
    m_keyMap[ Qt::Key_5 ] = XK_5;
    m_keyMap[ Qt::Key_6 ] = XK_6;
    m_keyMap[ Qt::Key_7 ] = XK_7;
    m_keyMap[ Qt::Key_8 ] = XK_8;
    m_keyMap[ Qt::Key_9 ] = XK_9;

    m_keyMap[ Qt::Key_BracketLeft ] = XK_bracketleft;
    m_keyMap[ Qt::Key_BracketRight ] = XK_bracketright;

    m_keyMap[ Qt::Key_A ] = XK_a;
    m_keyMap[ Qt::Key_B ] = XK_b;
    m_keyMap[ Qt::Key_C ] = XK_c;
    m_keyMap[ Qt::Key_D ] = XK_d;
    m_keyMap[ Qt::Key_E ] = XK_e;
    m_keyMap[ Qt::Key_F ] = XK_f;
    m_keyMap[ Qt::Key_G ] = XK_g;
    m_keyMap[ Qt::Key_H ] = XK_h;
    m_keyMap[ Qt::Key_I ] = XK_i;
    m_keyMap[ Qt::Key_J ] = XK_j;
    m_keyMap[ Qt::Key_K ] = XK_k;
    m_keyMap[ Qt::Key_L ] = XK_l;
    m_keyMap[ Qt::Key_M ] = XK_m;
    m_keyMap[ Qt::Key_N ] = XK_n;
    m_keyMap[ Qt::Key_O ] = XK_o;
    m_keyMap[ Qt::Key_P ] = XK_p;
    m_keyMap[ Qt::Key_Q ] = XK_q;
    m_keyMap[ Qt::Key_R ] = XK_r;
    m_keyMap[ Qt::Key_S ] = XK_s;
    m_keyMap[ Qt::Key_T ] = XK_t;
    m_keyMap[ Qt::Key_U ] = XK_u;
    m_keyMap[ Qt::Key_V ] = XK_v;
    m_keyMap[ Qt::Key_W ] = XK_w;
    m_keyMap[ Qt::Key_X ] = XK_x;
    m_keyMap[ Qt::Key_Y ] = XK_y;
    m_keyMap[ Qt::Key_Z ] = XK_z;
}

uint KeyMapper::findNativeVirtualKeyCode( Qt::Key keyCode ) {
    uint code = 0;

    Display* display = XOpenDisplay( nullptr );
    if( display ) {
        if( m_keyMap.contains( keyCode ) ) {
            code = XKeysymToKeycode( display, m_keyMap[ keyCode ] );
        }
        XCloseDisplay( display );
    }

    return code;
}
