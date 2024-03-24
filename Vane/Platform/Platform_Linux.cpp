#include <Defines.h>
#include <Platform.h>

#ifdef VPLATFORM_LINUX 

#include <xcb/xcb.h>
// #include <X11/keysyn.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <sys/time.h>

// TODO(wowvain-dev): decide whether to continue with X11 or 
// use SDL2 cross platform

namespace Vane {
    class LinuxPlatform : public Platform {
        Display *display;
        xcb_connection_t *connection;
        xcb_window_t window;
        xcb_screen_t *screen;
    };
}

#endif