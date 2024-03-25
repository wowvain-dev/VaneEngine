#pragma once

#include "../Core/Defines.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>


#ifdef VPLATFORM_LINUX

#include <xcb/xcb.h>
// #include <X11/keysyn.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <sys/time.h>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif

#elif VPLATFORM_WINDOWS

#include <Windows.h>
#include <windowsx.h>

#endif

namespace Vane {
class VAPI Platform {
#ifdef VPLATFORM_WINDOWS
    HINSTANCE h_instance;
    HWND hwnd;
#elif VPLATFORM_LINUX
    Display *display;
    xcb_connection_t *connection;
    xcb_window_t window;
    xcb_screen_t *screen;
    xcb_atom_t wm_protocols;
    xcb_atom_t wm_delete_win;
#endif

private:
#ifdef VPLATFORM_WINDOWS
    static f64 clock_frequency;
    static LARGE_INTEGER start_time;
#elif VPLATFORM_LINUX

#endif

public:
    bool startup(
        const char* applicationName,
        i32 x,
        i32 y,
        i32 width,
        i32 height
    );
    void shutdown();
    bool pumpMessages();

    static void* allocate(size_t size, bool aligned);
    static void free(void*, bool);
    static void* zeroMemory(void* block, size_t size);
    static void* copyMemory(void* dest, const void* source, size_t size);
    static void* setMemory(void* dest, i32 value, size_t size);
    static void consoleWrite(const char* message, u8 color);
    static void consoleWriteError(const char* message, u8 color);
    static f64 getAbsoluteTime();
    static void sleep(u64);
};
};
