#ifndef SHAREDDEFS_H
#define SHAREDDEFS_H

#include <QString>

static const char* const FRAME_AVAILABLE_SIG = "FRAME_AVAILABLE_SIG";
static const char* const ENABLE_CURSOR_CAPTURE_SIG = "ENABLE_CURSOR_CAPTURE_SIG";
static const char* const MOUSE_MOVE_SIG = "MOUSE_MOVE_SIG";
static const char* const MOUSE_PRESS_SIG = "MOUSE_PRESS_SIG";
static const char* const MOUSE_RELEASE_SIG = "MOUSE_RELEASE_SIG";
static const char* const MOUSE_WHEEL_SIG = "MOUSE_WHEEL_SIG";
static const char* const KEY_PRESS_SIG = "KEY_PRESS_SIG";
static const char* const KEY_RELEASE_SIG = "KEY_RELEASE_SIG";

static const int PORT = 9900;

#endif // SHAREDDEFS_H
