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
#include <cstdio>

import std.compat;

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#define RESET_COLOR "\x1B[0m"
#define INFO_COLOR "\x1B[1;34m"
#define DEBUG_COLOR "\x1B[1;30m"
#define WARNING_COLOR "\x1B[1;33m"
#define ERROR_COLOR "\x1B[31m"

#ifdef RELEASE
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

namespace Vane {
    class VAPI Logger {
    public:
        enum LOG_LEVEL {
            LOG_LEVEL_FATAL = 0,
            LOG_LEVEL_ERROR = 1,
            LOG_LEVEL_WARN = 2,
            LOG_LEVEL_INFO = 3,
            LOG_LEVEL_DEBUG = 4,
            LOG_LEVEL_TRACE = 5
        };

    private:
    public:
        static bool initializeLogging();

        static void shutdownLogging();

        template<typename... Args>
        static void log_output(LOG_LEVEL level, const char *message, Args... args) {
            std::tuple<const char *, const char *> level_strings[6] = {
                std::make_tuple("[FATAL]: ", ERROR_COLOR),
                std::make_tuple("[ERROR]: ", ERROR_COLOR),
                std::make_tuple("[WARN]: ", WARNING_COLOR),
                std::make_tuple("[INFO]: ", INFO_COLOR),
                std::make_tuple("[DEBUG]: ", DEBUG_COLOR),
                std::make_tuple("[TRACE]: ", DEBUG_COLOR)
            };
            bool is_error = level < 2;
            printf("%s%s - ",
                   std::get<1>(level_strings[level]),
                   std::get<0>(level_strings[level]));
            printf(message, args...);
            printf("%s\n", RESET_COLOR);
        }
    };

#ifndef VFATAL
#define VFATAL(message, ...) Vane::Logger::log_output(Vane::Logger::LOG_LEVEL::LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
#endif

#ifndef VERROR
#define VERROR(message, ...) Vane::Logger::log_output(Vane::Logger::LOG_LEVEL::LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
#define VWARN(message, ...) Vane::Logger::log_output(Vane::Logger::LOG_LEVEL::LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
#define VWARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define VINFO(message, ...) Vane::Logger::log_output(Vane::Logger::LOG_LEVEL::LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
#define VINFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define VDEBUG(message, ...) Vane::Logger::log_output(Vane::Logger::LOG_LEVEL::LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
#define VDEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define VTRACE(message, ...) Vane::Logger::log_output(Vane::Logger::LOG_LEVEL::LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
#define VTRACE(message, ...)
#endif
} // Vane
