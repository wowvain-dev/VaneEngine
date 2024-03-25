#include "Platform.h"

#ifdef VPLATFORM_LINUX

using namespace Vane;

bool Platform::startup(
    const char *application_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height)
{
    // Connecting to X
    display = XOpenDisplay(NULL);
    // Turn off key repeats
    XAutoRepeatOff(display);

    connection = XGetXCBConnection(display);

    if (xcb_connection_has_error(connection))
    {
        VFATAL("Failed to form connection via XCB.");
        return false;
    }

    const auto setup = xcb_get_setup(connection);
    int screen_p = 0;
    auto it = xcb_setup_roots_iterator(setup);
    for (i32 s = screen_p; s > 0; s--)
    {
        xcb_screen_next(&it);
    }

    screen = it.data;
    window = xcb_generate_id(connection);

    // Register event types.
    // XCB_CW_BACK_PIXEL = filling then window bg with a single color
    // XCB_CW_EVENT_MASK is required.
    u32 event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

    u32 event_values = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
                       XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
                       XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
                       XCB_EVENT_MASK_STRUCTURE_NOTIFY;

    u32 value_list[] = {screen->black_pixel, event_values};

    auto cookie = xcb_create_window(
        connection,
        XCB_COPY_FROM_PARENT,
        window,
        screen->root,
        x,
        y,
        width,
        height,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        screen->root_visual,
        event_mask,
        value_list);

    xcb_change_property(
        connection,
        XCB_PROP_MODE_REPLACE,
        window,
        XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING,
        8,
        std::string_view(application_name).length(),
        application_name);

    auto wm_delete_cookie = xcb_intern_atom(
        connection,
        0,
        std::string_view("WM_DELETE_WINDOW").length(),
        "WM_DELETE_WINDOW");

    auto wm_protocols_cookie = xcb_intern_atom(
        connection,
        0,
        std::string_view("WM_PROTOCOLS").length(),
        "WM_PROTOCOLS");

    auto wm_delete_reply = xcb_intern_atom_reply(
        connection,
        wm_delete_cookie,
        nullptr);

    auto wm_protocols_reply = xcb_intern_atom_reply(
        connection,
        wm_protocols_cookie,
        nullptr);

    wm_delete_win = wm_delete_reply->atom;
    wm_protocols = wm_protocols_reply->atom;

    xcb_change_property(
        connection,
        XCB_PROP_MODE_REPLACE,
        window,
        wm_protocols_reply->atom,
        4,
        32,
        1,
        &wm_delete_reply->atom);

    xcb_map_window(connection, window);

    i32 stream_result = xcb_flush(connection);

    if (stream_result <= 0)
    {
        VFATAL("An error occured when flushing the stream: {}", stream_result);
        return false;
    }

    return true;
}

void Platform::shutdown()
{
    XAutoRepeatOn(display);

    xcb_destroy_window(connection, window);
}

bool Platform::pumpMessages()
{
    xcb_generic_event_t *event;
    xcb_client_message_event_t *cm;

    bool quitFlagged = false;

    while (event != 0)
    {
        event = xcb_poll_for_event(connection);
        if (event == 0)
        {
            break;
        }

        switch (event->response_type & ~0x80)
        {
        case XCB_KEY_PRESS:
        case XCB_KEY_RELEASE:
        {
            // Key presses and releases
        }
        break;

        case XCB_BUTTON_PRESS:
        case XCB_BUTTON_RELEASE:
        {
            // Mouse button presses and releases
        }
        case XCB_MOTION_NOTIFY:
            // mouse movement
            break;

        case XCB_CONFIGURE_NOTIFY:
        {
        }

        case XCB_CLIENT_MESSAGE:
        {
            cm = (xcb_client_message_event_t *)event;

            // Window close
            if (cm->data.data32[0] == wm_delete_win)
            {
                quitFlagged = true;
            }
        }
        break;

        default:
        {
            // Something else
            break;
        }
        }

        delete event;
    }
    return !quitFlagged;
}

void *Platform::allocate(size_t size, bool aligned)
{
    return ::operator new(size);
}

void Platform::free(void *block, bool aligned)
{
    ::operator delete(block);
}

void *Platform::zeroMemory(void *block, size_t size)
{
    return std::memset(block, 0, size);
}

void *Platform::copyMemory(void *dest, const void *source, size_t size)
{
    return std::memcpy(dest, source, size);
}

void *Platform::setMemory(void *dest, i32 value, size_t size)
{
    return std::memset(dest, value, size);
}

void Platform::consoleWrite(const char *message, u8 color)
{
    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    const char *color_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m", color_strings[color], message);
}

void Platform::consoleWriteError(const char *message, u8 color)
{
    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    const char *color_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m", color_strings[color], message);
}

f64 Platform::getAbsoluteTime()
{
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec * 0.000000001;
}

void Platform::sleep(u64 ms)
{
#if _POSIX_C_SOURCE >= 199309L
    timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000 * 1000;
    nanosleep(&ts, 0);
#else
    if (ms >= 1000)
    {
        sleep(ms / 1000);
    }
    usleep((ms % 1000) * 1000);
#endif
}

#endif
