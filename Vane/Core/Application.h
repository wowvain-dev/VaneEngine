//////////////////////////////////////////////////////////////////////////////////////////
// Copyright wowvain-dev | Bogdan Stanciu (c) 2024.
//
// MIT License
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Platform/Platform.h"
#include "Logger.h"
#include "Defines.h"
#include <string>

// #ifdef VPLATFORM_WINDOWS
// #include "../Platform/Platform_Win32.h"
// #elif VPLATFORM_LINUX
// #include "../Platform/Platform_Linux.h"
// #endif

using std::string;

namespace Vane {
struct VAPI ApplicationConfig {
    i16 startPosX;
    i16 startPosY;
    i16 startWidth;
    i16 startHeight;

    string name;
};

class VAPI Application {
private:
    static bool initialised;
    ApplicationConfig startConfig;

    bool isRunning;
    bool isSuspended;
    Platform* platform;
    i16 width;
    i16 height;
    f64 lastTime;

public:
    bool create(ApplicationConfig* config);
    bool run();
};

};
