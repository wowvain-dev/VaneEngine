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

namespace Vane
{
    class Platform_Linux : public Platform
    {
        Display *display;
        xcb_connection_t *connection;
        xcb_window_t window;
        xcb_screen_t *screen;
        xcb_atom_t wm_protocols;
        xcb_atom_t wm_delete_win;

    public:
        bool startup(
            const char *,
            i32,
            i32,
            i32,
            i32) override;

        void shutdown() override;

        bool pumpMessages() override;

        void *allocate(size_t, bool) override;
        void free(void *, bool) override;
        void *zeroMemory(void *, size_t) override;
        void *copyMemory(void *, const void *, size_t) override;
        void *setMemory(void *, i32, size_t) override;
        void consoleWrite(const char *, u8) override;
        void consoleWriteError(const char *, u8) override;
        f64 getAbsoluteTime() override;
        void sleep(u64) override;
    };
};

#endif
