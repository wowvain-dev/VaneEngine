#pragma once

#include "Platform.h"

#if VPLATFORM_WINDOWS

#include <Windows.h>
#include <WinBase.h>
#include <windowsx.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Vane {
class Platform_Win32 : public Platform {
    HINSTANCE h_instance;
    HWND hwnd;

private:
    static f64 clock_frequency;
    static LARGE_INTEGER start_time;

public:
    bool startup(const char*, i32, i32, i32, i32) override;
    void shutdown() override;
    bool pumpMessages() override;

    void* allocate(size_t, bool) override;
    void free(void*, bool) override;
    void* zeroMemory(void* block, size_t size) override;
    void* copyMemory(void* dest, const void* source, size_t size) override;
    void* setMemory(void* dest, i32 value, size_t size) override;
    void consoleWrite(const char* message, u8 color) override;
    void consoleWriteError(const char* message, u8 color) override;
    void sleep(u64) override;
    f64 getAbsoluteTime() override;
};
}; // namespace Vane

#endif
