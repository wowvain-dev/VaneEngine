// Copyright (c) 2024 wowvain-dev | Bogdan Stanciu
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#include "Core/Application.hpp"
#include "Core/Logger.hpp"
#include "Core/Asserts.hpp"

extern Vane::Application *Vane::CreateApplication(int argc, char **argv);
bool g_ApplicationRunning = true;

namespace Vane
{
    int Main(int argc, char **argv)
    {
        // Initializing systems;
        Application *app = CreateApplication(argc, argv);

        VASSERT_MSG(app, "Client application is null!");

        app->run();

        app->shutdown();

        delete app;
        // Shutting systems down;
        VERROR("SHAT SYSTEMS DOWN");
        return 0;
    }
}

int main(int argc, char **argv)
{
    return Vane::Main(argc, argv);
}