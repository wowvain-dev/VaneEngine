#include "Platform.h"

#ifdef VPLATFORM_LINUX 

#include "../Core/Defines.h"
#include "../Core/Logger.h"

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

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>

namespace Vane {
    class LinuxPlatform : public Platform {
        Display *display;
        xcb_connection_t *connection;
        xcb_window_t window;
        xcb_screen_t *screen;
        xcb_atom_t wm_protocols;
        xcb_atom_t wm_delete_win;
    
        public:
        bool startup(
            const char*,
            i32,
            i32,
            i32,
            i32
        );

        void shutdown();

        bool pumpMessages();

        void* allocate(std::size_t, bool);
        void free(void*, std::size_t);
        void* zeroMemory(void*, std::size_t);
        void* copyMemory(void*, const void*, std::size_t);
        void* setMemory(void*, i32, std::size_t);
        void consoleWrite(const char*, u8);
        void consoleWriteError(const char*, u8);
        f64 getAbsoluteTime();
        void sleep(u64);
    };
};

#endif