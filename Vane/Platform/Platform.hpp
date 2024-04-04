// Copyright (c) 2024 wowvain-dev | Bogdan Stanciu
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>

#include <Core/Defines.hpp>

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
class Platform {
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
    ~Platform();
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
