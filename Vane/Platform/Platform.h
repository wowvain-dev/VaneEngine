#pragma once 

#include "../Core/Defines.h"

namespace Vane {
class Platform {
    void* internalState;

    public:
    virtual bool startup(
        const char* applicationName,
        i32 x,
        i32 y,
        i32 width,
        i32 height
    );

    virtual void shutdown();

    virtual bool pumpMessages();

    virtual void* allocate(u64 size, bool aligned);
    virtual void  free();
    virtual void* zeroMemory(void* block, u64 size);
    virtual void* copyMemory(void* dest, const void* source, u64 size);
    virtual void* setMemory(void* dest, i32 value, u64 size);

    virtual void* consoleWrite(const char* message, u8 color);
    virtual void* consoleWriteError(const char* message, u8 color);

    virtual f64 getAbsoluteTime();

    virtual void sleep();
};

}

