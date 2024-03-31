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

#include <new>
#include <string>
#include <memory>
#include <cstdlib>
#include <algorithm>

using std::string;

#include "Logger.hpp"
#include "Asserts.hpp"
#include "Defines.hpp"
#include "Allocator.hpp"

#include <cstdlib>

namespace Vane {
class VAPI Align {
public: 
    explicit Align(v_size value) : m_value(value) {}

    inline v_size getValue() const { return m_value; }

private:
    v_size m_value;
};
}

void* operator new(v_size size);
void* operator new[](v_size size);
void  operator delete(void* mem) noexcept;
void  operator delete[](void* mem) noexcept;

void* operator new(v_size size, Vane::Align alignment);
void* operator new[](v_size size, Vane::Align alignment);
void  operator delete(void* mem, Vane::Align alignment) noexcept;
void  operator delete[](void* mem, Vane::Align alignment) noexcept;

#ifdef _MSC_VER
#define V_ALIGNED_ALLOC(x, y) _aligned_malloc(x, y)
#else
#define V_ALIGNED_ALLOC(x, y) std::aligned_alloc(x, y) 
#endif
