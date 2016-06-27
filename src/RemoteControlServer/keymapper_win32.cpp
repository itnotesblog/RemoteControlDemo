#include "keymapper.h"

#include <Windows.h>

KeyMapper::KeyMapper() {
    m_keyMap[ Qt::Key_Cancel ] = VK_CANCEL;
    m_keyMap[ Qt::Key_Backspace ] = VK_BACK;
    m_keyMap[ Qt::Key_Tab ] = VK_TAB;
    m_keyMap[ Qt::Key_Clear ] = VK_CLEAR;
    m_keyMap[ Qt::Key_Return ] = VK_RETURN;
    m_keyMap[ Qt::Key_Shift ] = VK_SHIFT;
    m_keyMap[ Qt::Key_Control ] = VK_CONTROL;
    m_keyMap[ Qt::Key_Alt ] = VK_MENU;
    m_keyMap[ Qt::Key_Pause ] = VK_PAUSE;
    m_keyMap[ Qt::Key_CapsLock ] = VK_CAPITAL;
    m_keyMap[ Qt::Key_Escape ] = VK_ESCAPE;
    m_keyMap[ Qt::Key_Mode_switch ] = VK_MODECHANGE;
    m_keyMap[ Qt::Key_Space ] = VK_SPACE;
    m_keyMap[ Qt::Key_PageUp ] = VK_PRIOR;
    m_keyMap[ Qt::Key_PageDown ] = VK_NEXT;
    m_keyMap[ Qt::Key_End ] = VK_END;
    m_keyMap[ Qt::Key_Home ] = VK_HOME;
    m_keyMap[ Qt::Key_Left ] = VK_LEFT;
    m_keyMap[ Qt::Key_Up ] = VK_UP;
    m_keyMap[ Qt::Key_Right ] = VK_RIGHT;
    m_keyMap[ Qt::Key_Down ] = VK_DOWN;
    m_keyMap[ Qt::Key_Select ] = VK_SELECT;
    m_keyMap[ Qt::Key_Printer ] = VK_PRINT;
    m_keyMap[ Qt::Key_Execute ] = VK_EXECUTE;
    m_keyMap[ Qt::Key_Print ] = VK_SNAPSHOT;
    m_keyMap[ Qt::Key_Insert ] = VK_INSERT;
    m_keyMap[ Qt::Key_Delete ] = VK_DELETE;
    m_keyMap[ Qt::Key_Help ] = VK_HELP;
    m_keyMap[ Qt::Key_0 ] = 0x30; //  (VK_0)              | 0 key
    m_keyMap[ Qt::Key_1 ] = 0x31; //  (VK_1)              | 1 key
    m_keyMap[ Qt::Key_2 ] = 0x32; //  (VK_2)              | 2 key
    m_keyMap[ Qt::Key_3 ] = 0x33; //  (VK_3)              | 3 key
    m_keyMap[ Qt::Key_4 ] = 0x34; //  (VK_4)              | 4 key
    m_keyMap[ Qt::Key_5 ] = 0x35; //  (VK_5)              | 5 key
    m_keyMap[ Qt::Key_6 ] = 0x36; //  (VK_6)              | 6 key
    m_keyMap[ Qt::Key_7 ] = 0x37; //  (VK_7)              | 7 key
    m_keyMap[ Qt::Key_8 ] = 0x38; //  (VK_8)              | 8 key
    m_keyMap[ Qt::Key_9 ] = 0x39; //  (VK_9)              | 9 key
    m_keyMap[ Qt::Key_A ] = 0x41; //  (VK_A)              | A key
    m_keyMap[ Qt::Key_B ] = 0x42; //  (VK_B)              | B key
    m_keyMap[ Qt::Key_C ] = 0x43; //  (VK_C)              | C key
    m_keyMap[ Qt::Key_D ] = 0x44; //  (VK_D)              | D key
    m_keyMap[ Qt::Key_E ] = 0x45; //  (VK_E)              | E key
    m_keyMap[ Qt::Key_F ] = 0x46; //  (VK_F)              | F key
    m_keyMap[ Qt::Key_G ] = 0x47; //  (VK_G)              | G key
    m_keyMap[ Qt::Key_H ] = 0x48; //  (VK_H)              | H key
    m_keyMap[ Qt::Key_I ] = 0x49; //  (VK_I)              | I key
    m_keyMap[ Qt::Key_J ] = 0x4A; //  (VK_J)              | J key
    m_keyMap[ Qt::Key_K ] = 0x4B; //  (VK_K)              | K key
    m_keyMap[ Qt::Key_L ] = 0x4C; //  (VK_L)              | L key
    m_keyMap[ Qt::Key_M ] = 0x4D; //  (VK_M)              | M key
    m_keyMap[ Qt::Key_N ] = 0x4E; //  (VK_N)              | N key
    m_keyMap[ Qt::Key_O ] = 0x4F; //  (VK_O)              | O key
    m_keyMap[ Qt::Key_P ] = 0x50; //  (VK_P)              | P key
    m_keyMap[ Qt::Key_Q ] = 0x51; //  (VK_Q)              | Q key
    m_keyMap[ Qt::Key_R ] = 0x52; //  (VK_R)              | R key
    m_keyMap[ Qt::Key_S ] = 0x53; //  (VK_S)              | S key
    m_keyMap[ Qt::Key_T ] = 0x54; //  (VK_T)              | T key
    m_keyMap[ Qt::Key_U ] = 0x55; //  (VK_U)              | U key
    m_keyMap[ Qt::Key_V ] = 0x56; //  (VK_V)              | V key
    m_keyMap[ Qt::Key_W ] = 0x57; //  (VK_W)              | W key
    m_keyMap[ Qt::Key_X ] = 0x58; //  (VK_X)              | X key
    m_keyMap[ Qt::Key_Y ] = 0x59; //  (VK_Y)              | Y key
    m_keyMap[ Qt::Key_Z ] = 0x5A; //  (VK_Z)              | Z key
    m_keyMap[ Qt::Key_Meta ] = VK_LWIN;
    m_keyMap[ Qt::Key_Menu ] = VK_APPS;
    m_keyMap[ Qt::Key_Sleep ] = VK_SLEEP;
    m_keyMap[ Qt::Key_0 ] = VK_NUMPAD0;
    m_keyMap[ Qt::Key_1 ] = VK_NUMPAD1;
    m_keyMap[ Qt::Key_2 ] = VK_NUMPAD2;
    m_keyMap[ Qt::Key_3 ] = VK_NUMPAD3;
    m_keyMap[ Qt::Key_4 ] = VK_NUMPAD4;
    m_keyMap[ Qt::Key_5 ] = VK_NUMPAD5;
    m_keyMap[ Qt::Key_6 ] = VK_NUMPAD6;
    m_keyMap[ Qt::Key_7 ] = VK_NUMPAD7;
    m_keyMap[ Qt::Key_8 ] = VK_NUMPAD8;
    m_keyMap[ Qt::Key_9 ] = VK_NUMPAD9;
    m_keyMap[ Qt::Key_F1 ] = VK_F1;
    m_keyMap[ Qt::Key_F2 ] = VK_F2;
    m_keyMap[ Qt::Key_F3 ] = VK_F3;
    m_keyMap[ Qt::Key_F4 ] = VK_F4;
    m_keyMap[ Qt::Key_F5 ] = VK_F5;
    m_keyMap[ Qt::Key_F6 ] = VK_F6;
    m_keyMap[ Qt::Key_F7 ] = VK_F7;
    m_keyMap[ Qt::Key_F8 ] = VK_F8;
    m_keyMap[ Qt::Key_F9 ] = VK_F9;
    m_keyMap[ Qt::Key_F10 ] = VK_F10;
    m_keyMap[ Qt::Key_F11 ] = VK_F11;
    m_keyMap[ Qt::Key_F12 ] = VK_F12;
    m_keyMap[ Qt::Key_F13 ] = VK_F13;
    m_keyMap[ Qt::Key_F14 ] = VK_F14;
    m_keyMap[ Qt::Key_F15 ] = VK_F15;
    m_keyMap[ Qt::Key_F16 ] = VK_F16;
    m_keyMap[ Qt::Key_F17 ] = VK_F17;
    m_keyMap[ Qt::Key_F18 ] = VK_F18;
    m_keyMap[ Qt::Key_F19 ] = VK_F19;
    m_keyMap[ Qt::Key_F20 ] = VK_F20;
    m_keyMap[ Qt::Key_F21 ] = VK_F21;
    m_keyMap[ Qt::Key_F22 ] = VK_F22;
    m_keyMap[ Qt::Key_F23 ] = VK_F23;
    m_keyMap[ Qt::Key_F24 ] = VK_F24;
    m_keyMap[ Qt::Key_NumLock ] = VK_NUMLOCK;
    m_keyMap[ Qt::Key_ScrollLock ] = VK_SCROLL;
    m_keyMap[ Qt::Key_Back ] = VK_BROWSER_BACK;
    m_keyMap[ Qt::Key_Forward ] = VK_BROWSER_FORWARD;
    m_keyMap[ Qt::Key_Refresh ] = VK_BROWSER_REFRESH;
    m_keyMap[ Qt::Key_Stop ] = VK_BROWSER_STOP;
    m_keyMap[ Qt::Key_Search ] = VK_BROWSER_SEARCH;
    m_keyMap[ Qt::Key_Favorites ] = VK_BROWSER_FAVORITES;
    m_keyMap[ Qt::Key_HomePage ] = VK_BROWSER_HOME;
    m_keyMap[ Qt::Key_VolumeMute ] = VK_VOLUME_MUTE;
    m_keyMap[ Qt::Key_VolumeDown ] = VK_VOLUME_DOWN;
    m_keyMap[ Qt::Key_VolumeUp ] = VK_VOLUME_UP;
    m_keyMap[ Qt::Key_MediaNext ] = VK_MEDIA_NEXT_TRACK;
    m_keyMap[ Qt::Key_MediaPrevious ] = VK_MEDIA_PREV_TRACK;
    m_keyMap[ Qt::Key_MediaStop ] = VK_MEDIA_STOP;
    m_keyMap[ Qt::Key_MediaPlay ] = VK_MEDIA_PLAY_PAUSE;
    m_keyMap[ Qt::Key_LaunchMail ] = VK_LAUNCH_MAIL;
    m_keyMap[ Qt::Key_LaunchMedia ] = VK_LAUNCH_MEDIA_SELECT;
    m_keyMap[ Qt::Key_Launch0 ] = VK_LAUNCH_APP1;
    m_keyMap[ Qt::Key_Launch1 ] = VK_LAUNCH_APP2;

    m_keyMap[ Qt::Key_Play ] = VK_PLAY;
    m_keyMap[ Qt::Key_Zoom ] = VK_ZOOM;
}

uint KeyMapper::findNativeVirtualKeyCode( Qt::Key keyCode ) {
    uint code = 0;

    if( m_keyMap.contains( keyCode ) ) {
        code = m_keyMap[ keyCode ];
    }

    return code;
}
