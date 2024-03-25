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

#include "Defines.h"
#include <tuple>
#include "../Platform/Platform.h"
#include <cstdio>
#include <string>
#include <format>

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1


#ifdef RELEASE
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

namespace Vane {
enum LOG_LEVEL {
    V_FATAL = 0,
    V_ERROR = 1,
    V_WARN = 2,
    V_INFO = 3,
    V_DEBUG = 4,
    V_TRACE = 5
};


class Logger {
public:

private:
public:
    static bool initializeLogging();

    static void shutdownLogging();

    template <typename... Args>
    static void log_output(LOG_LEVEL level, std::format_string<Args...> message, Args&&... args) {
        std::tuple<const char*, const char*> level_strings[6] = {
            std::make_tuple("[FATAL]: ", "0;41"),
            std::make_tuple("[ERROR]: ", "1;31"),
            std::make_tuple("[WARN]: ", "1;33"),
            std::make_tuple("[INFO]: ", "1;32"),
            std::make_tuple("[DEBUG]: ", "1;34"),
            std::make_tuple("[TRACE]: ", "1:30")
        };
        const bool is_error = level < LOG_LEVEL::V_WARN;

        std::string label = std::format("\033[{}m{} - ", 
               std::get<1>(level_strings[level]),
               std::get<0>(level_strings[level])
        );

        std::string out_message;
        std::string s;

        try {
            out_message = std::format(message, std::forward<Args>(args)...);
            s = std::format("{}{}\n", label, out_message);
        }
        catch (...) {
            Platform::consoleWriteError("Bad string formatting", 1);
            return;
        }

        if (is_error) {
            Platform::consoleWriteError(s.c_str(), level);
        }
        else {
            Platform::consoleWrite(s.c_str(), level);
        }


        // printf("\033[%sm%s - ",
        //        std::get<1>(level_strings[level]),
        //        std::get<0>(level_strings[level]));
        // printf(message, args...);
        // printf("\033[0m\n");
    }
};

#ifndef VFATAL
#define VFATAL(message, ...) Vane::Logger::log_output(Vane::LOG_LEVEL::V_FATAL, message, ##__VA_ARGS__);
#endif

#ifndef VERROR
#define VERROR(message, ...) Vane::Logger::log_output(Vane::LOG_LEVEL::V_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
#define VWARN(message, ...) Vane::Logger::log_output(Vane::LOG_LEVEL::V_WARN, message, ##__VA_ARGS__);
#else
#define VWARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define VINFO(message, ...) Vane::Logger::log_output(Vane::LOG_LEVEL::V_INFO, message, ##__VA_ARGS__);
#else
#define VINFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define VDEBUG(message, ...) Vane::Logger::log_output(Vane::LOG_LEVEL::V_DEBUG, message, ##__VA_ARGS__);
#else
#define VDEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define VTRACE(message, ...) Vane::Logger::log_output(Vane::LOG_LEVEL::V_TRACE, message, ##__VA_ARGS__);
#else
#define VTRACE(message, ...)
#endif
} // Vane
