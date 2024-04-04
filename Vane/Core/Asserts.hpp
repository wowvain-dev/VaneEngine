//////////////////////////////////////////////////////////////////////////////////////////
// Copyright wowvain-dev | Bogdan Stanciu (c) 2024.
//
// MIT License
// Permission is hereby granted, free of charge, to any person obtaining a copy of this 
// software and associated documentation files (the “Software”), to deal in the Software 
// without restriction, including without limitation the rights to use, copy, modify, merge, 
// publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
// to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

#include <Core/Defines.hpp>

#define VASSERTIONS_ENABLED

#ifdef VASSERTIONS_ENABLED

#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

namespace Vane {
void reportAssertionFailure(const char* expression, const char* message, const char* file, i32 line);

void reportAssertionFailure(std::string expression, std::string* message, std::string* file, i32 line);
}

#define VASSERT(expr) {if (expr) {} else { Vane::reportAssertionFailure(#expr, "", __FILE__, __LINE__); debugBreak();}}
#define VASSERT_MSG(expr, message) { if (expr) {} else { Vane::reportAssertionFailure(#expr, message, __FILE__, __LINE__); debugBreak();}}

#ifdef DEBUG
#define VASSERT_DEBUG(expr) { if (expr) {} else { Vane::reportAssertionFailure(#expr, "", __FILE__, __LINE__); debugBreak();} }
#else
#define VASSERT_DEBUG(expr)
#endif

#else

#define VASSERT(expr)
#define VASSERT_MSG(expr, message)
#define VASSERT_DEBUG(expr)

#endif
