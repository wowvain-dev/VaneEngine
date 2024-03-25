#pragma once

#include "../Core/Defines.h"

namespace Vane {
class VAPI Platform {
    void* internalState;

public:
    virtual bool startup(
        const char* applicationName,
        i32 x,
        i32 y,
        i32 width,
        i32 height
    ) = 0;

    virtual void shutdown() = 0;

    virtual bool pumpMessages() = 0;

    virtual void* allocate(size_t size, bool aligned) = 0;
    virtual void free(void*, bool) = 0;
    virtual void* zeroMemory(void* block, size_t size) = 0;
    virtual void* copyMemory(void* dest, const void* source, size_t size) = 0;
    virtual void* setMemory(void* dest, i32 value, size_t size) = 0;
    virtual void consoleWrite(const char* message, u8 color) = 0;
    virtual void consoleWriteError(const char* message, u8 color) = 0;
    virtual f64 getAbsoluteTime() = 0;
    virtual void sleep(u64) = 0;
};
};
