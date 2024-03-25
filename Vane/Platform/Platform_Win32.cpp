#include "Platform_Win32.h"

#ifdef VPLATFORM_WINDOWS

#include "../Core/Logger.h"

using namespace Vane;

f64 Platform_Win32::clock_frequency = 0.;
LARGE_INTEGER Platform_Win32::start_time = {0};

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param,
                                       LPARAM l_param);

bool Platform_Win32::startup(const char* application_name, i32 x, i32 y,
                             i32 width, i32 height) {
    h_instance = GetModuleHandleA(nullptr);

    HICON icon = LoadIcon(h_instance, IDI_APPLICATION);
    WNDCLASSA wc;
    std::memset(&wc, 0, sizeof(wc));

    wc.style = CS_DBLCLKS, wc.lpfnWndProc = static_cast<WNDPROC>(win32_process_message),
            wc.cbClsExtra = 0,
            wc.cbWndExtra = 0,
            wc.hInstance = h_instance,
            wc.hIcon = icon,
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW),
            wc.hbrBackground = nullptr,
            wc.lpszClassName = "vane_window_class";

    if (!RegisterClassA(&wc)) {
        MessageBoxA(0, "Window registration failed", "Error",
                    MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    u32 client_x = x;
    u32 client_y = y;
    u32 client_width = width;
    u32 client_height = height;

    u32 window_x = client_x;
    u32 window_y = client_y;
    u32 window_width = client_width;
    u32 window_height = client_height;

    u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    u32 window_ex_style = WS_EX_APPWINDOW;

    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZE;
    window_style |= WS_THICKFRAME;

    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

    window_x += border_rect.left;
    window_y += border_rect.top;

    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowExA(
        window_ex_style, "vane_window_class", application_name,
        window_style, window_x, window_y, window_width, window_height,
        0, 0, h_instance, 0);

    if (handle == 0) {
        MessageBoxA(nullptr, "Window Creation Failed!", "Error!",
                    MB_ICONEXCLAMATION | MB_OK);

        VFATAL("Window creation failed!");
        return false;
    }
    else {
        hwnd = handle;
    }

    // Show the window
    bool should_activate = 1; // TODO: if the window should not accept input, set it to false
    i32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;

    ShowWindow(hwnd, show_window_command_flags);

    // Clock setup
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (f64)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);

    return true;
}

void Platform_Win32::shutdown() {
    if (hwnd) {
        DestroyWindow(hwnd);
        hwnd = 0;
    }
}

bool Platform_Win32::pumpMessages() {
    MSG message;
    while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }

    return true;
}

void* Platform_Win32::allocate(size_t size, bool aligned) {
    return ::operator new(size);
}

void Platform_Win32::free(void* block, bool aligned) {
    ::operator delete(block);
}

void* Platform_Win32::zeroMemory(void* block, size_t size) {
    return memset(block, 0, size);
}

void* Platform_Win32::copyMemory(void* dest, const void* source, size_t size) {
    return memcpy(dest, source, size);
}

void* Platform_Win32::setMemory(void* dest, i32 value, size_t size) {
    return memset(dest, value, size);
}

void Platform_Win32::consoleWrite(const char* message, u8 color) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);

    OutputDebugStringA(message);
    const u64 length = strlen(message);
    const LPDWORD number_written = nullptr;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, static_cast<DWORD>(length),
                  number_written, nullptr);
}

void Platform_Win32::consoleWriteError(const char* message, u8 color) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);

    OutputDebugStringA(message);
    const u64 length = strlen(message);
    const LPDWORD number_written = nullptr;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, static_cast<DWORD>(length),
                  number_written, nullptr);
}

f64 Platform_Win32::getAbsoluteTime() {
    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return static_cast<f64>(now_time.QuadPart) * clock_frequency;
}

void Platform_Win32::sleep(u64 ms) { Sleep(ms); }

LRESULT win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param) {
    switch (msg) {
    case WM_ERASEBKGND:
        // Notify that we will use a graphics API for erasing the window.
        return 1;
    case WM_CLOSE:
        // TODO: fire an event for the application to quit
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    {
        RECT r;
        GetClientRect(hwnd, &r);
        u32 width = r.right - r.left;
        u32 height = r.bottom - r.top;

        VINFO("WM_SIZE: %d %d %d %d", r.left, r.top, r.right, r.bottom);

        // Fire an event for resize;
    }
    break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
    {
        // input processing
    }
    break;
    case WM_MOUSEMOVE:
    {
        i32 x_pos = GET_X_LPARAM(l_param);
        i32 y_pos = GET_Y_LPARAM(l_param);
    }
    break;
    case WM_MOUSEWHEEL:
    {
        // i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
        // if (z_delta != 0) {
        //   // Flatten the input to an OS independent (-1, 1)
        //   z_delta = (z_delta < 0) ? -1 : 1;
        // }
    }
    break;
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    {
        bool pressed = msg == WM_LBUTTONDOWN || msg == WM_MBUTTONDOWN || msg == WM_RBUTTONDOWN;
    }
    break;
    }
    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

#endif
