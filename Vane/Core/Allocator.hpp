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

#include "Asserts.hpp"
#include "Defines.hpp"

namespace Vane
{

    /// @brief Base allocator interface.
    class Allocator
    {
    public:
        Allocator(u32 size, void *start)
        {
            _start = start;
            _size = size;
            _used_memory = 0;
            _num_allocations = 0;
        }

        virtual ~Allocator()
        {
            VASSERT(_num_allocations == 0 && _used_memory == 0);
            _start = nullptr;
            _size = 0;
        }

        virtual void *allocate(u32 size, u8 alignment = 4) = 0;
        virtual void deallocate(void *p) = 0;
        void *getStart() const { return _start; }
        u32 getSize() const { return _size; }
        u32 getUsedMemory() const { return _used_memory; }
        u32 getNumAllocations() const { return _num_allocations; }

    protected:
        void *_start;
        u32 _size;
        u32 _used_memory;
        u32 _num_allocations;
    };

    namespace allocator
    {
        template <class T>
        T *allocateNew(Allocator &allocator)
        {
            return new (allocator.allocate(sizeof(T), __alignof(T))) T;
        }

        template <class T>
        T *allocateNew(Allocator &allocator, const T &t)
        {
            return new (allocator.allocate(sizeof(T), __alignof(T))) T(t);
        }

        template <class T>
        void deallocateDelete(Allocator &allocator, T &object)
        {
            object.~T();
            allocator.deallocate(&object);
        }

        template <class T>
        T *allocateArray(Allocator &allocator, u32 length)
        {
            VASSERT(length != 0);
            u8 headerSize = sizeof(u32) / sizeof(T);

            if (sizeof(u32) % sizeof(T) > 0)
                headerSize += 1;

            // Allocate extra space to store array length in the bytes before the array
            T *p = ((T *)allocator.allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;
            *(((u32 *)p) - 1) = length;

            for (u32 i = 0; i < length; i++)
                new (&p) T;

            return p;
        }

        template <class T>
        void deallocateArray(Allocator &allocator, T *array)
        {
            VASSERT(array != nullptr);
            u32 length = *(((u32 *)array) - 1);

            for (u32 i = 0; i < length; i++)
                array.~T();

            // Calculate how much extra memory was allocated to store the length before the array
            u8 headerSize = sizeof(u32) / sizeof(T);
            if (sizeof(u32) % sizeof(T) > 0)
                headerSize += 1;
            allocator.deallocate(array - headerSize);
        }
    }

}
