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
#include <cstdint>

// UNSIGNED INT TYPES
typedef uint_fast8_t    u8;
typedef uint_fast16_t   u16;
typedef uint_fast32_t   u32;
typedef uint_fast64_t   u64;

// LEAST UNSIGNED INT TYPES
typedef uint_least8_t   u_l8;
typedef uint_least16_t  u_l16;
typedef uint_least32_t  u_l32;
typedef uint_least64_t  u_l64;

// SIGNED INT TYPES
typedef int_fast8_t    i8;
typedef int_fast16_t   i16;
typedef int_fast32_t   i32;
typedef int_fast64_t   i64;

// LEAST INT TYPES
typedef int_least8_t   i_l8;
typedef int_least16_t  i_l16;
typedef int_least32_t  i_l32;
typedef int_least64_t  i_l64;

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

#define KPLATFORM_APPLE 1
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