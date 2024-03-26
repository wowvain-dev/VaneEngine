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

#include "../Platform/Platform.hpp"
#include "Logger.hpp"
#include "Defines.hpp"
#include <memory>
#include <string>

using std::string;

class Game;

namespace Vane {
struct VAPI ApplicationConfig {
    i16 startPosX;
    i16 startPosY;
    i16 windowWidth;
    i16 windowHeight;
    string name = "Vane";
    bool VSync = true;
    bool startMaximized = false;
    bool resizable = true;
};
};

namespace Vane {
class VAPI Application {
    
public:
    Application(const ApplicationConfig& config);
    virtual ~Application();

    void run();
    void shutdown();

    virtual void onInit() {}
    virtual void onShutdown() {}
    virtual void onUpdate(f32 delta) {}

    inline Platform& platform() { return *m_Platform; }
    static inline Application& get() { return *s_Instance; }

    Game* gameInstance;
    i16 width;
    i16 height;
    f64 lastTime;

public:
    bool create(Game* gameInstance);

private:
    static Application* s_Instance;
    ApplicationConfig m_Config;
    std::unique_ptr<Platform> m_Platform;
    int test;
    bool m_Running;
    bool m_Suspended;

};

Application* CreateApplication(int argc, char** argv);

};