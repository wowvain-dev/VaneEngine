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
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <memory>

namespace Vane{
enum LOG_LEVEL {
    V_FATAL = 0,
    V_ERROR = 1,
    V_WARN = 2,
    V_INFO = 3,
    V_DEBUG = 4,
    V_TRACE = 5
};
};

// BUFFER SIZE TYPE
using v_size    = std::size_t;

// UNSIGNED INT TYPES
using u8        = uint_fast8_t;
using u16       = uint_fast16_t;
using u32       = uint_fast32_t;
using u64       = uint_fast64_t;

// LEAST UNSIGNED INT TYPES
using u_l8      = uint_least8_t;
using u_l16     = uint_least16_t;
using u_l32     = uint_least32_t;
using u_l64     = uint_least64_t;

// SIGNED INT TYPES
using i8        = int_fast8_t;
using i16       = int_fast16_t;
using i32       = int_fast32_t;
using i64       = int_fast64_t;

// LEAST INT TYPES
using i_l8      = int_least8_t;
using i_l16     = int_least16_t;
using i_l32     = int_least32_t;
using i_l64     = int_least64_t;

// FLOATING POINT TYPES
using f32       = float;
using f64       = double;

#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#define VPLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif

#elif defined(__linux__) || defined(__gnu_linux__)
#define VPLATFORM_LINUX 1

#if defined(__ANDROID__)
#define VPLATFORM_ANDROID 1
#endif

#elif defined(__unix__)

#define VPLATFORM_UNIX

#elif defined(_POSIX_VERSION)

#define VPLATFORM_POSIX 1

#elif __APPLE__

#define VPLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS simulator
#define VPLATFORM_IOS 1
#define VPLATFORM_IOS_SIMULATOR 1

#elif TARGET_OS_IPHONE
#define VPLATFORM_IOS 1

#elif TARGET_OS_MAC

#else
#error "Unknown Apple Platform"
#endif

#else
#error "Unknown platform!"
#endif

#ifdef VEXPORT

#ifdef _MSC_VER
#define VAPI __declspec(dllexport)

#else

#define VAPI __attribute__((visibility("default")))
#endif

#else

// Imports

#ifdef _MSC_VER
#define VAPI __declspec(dllimport)
#else
#define VAPI
#endif
#endif


// Utils

// used for bit masking
#define BIT(x) (1u << x)

// remove potential definition of `max` macro
#undef max
