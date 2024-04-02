
#include <vector>
#include <stdexcept>

#include "../Asserts.hpp"
#include "../Logger.hpp"

#include "MemoryArena.hpp"
#include "ObjectHandle.hpp"
#include "MemUtil.hpp"

namespace Vane::Memory {
    HandleEntry MemoryArena::entryArr[maxHandleCount];
    
    MemoryArena::MemoryArena(const u_size size) {
        memHead = std::malloc(size);
        leftAddress = reinterpret_cast<u_ptr>(memHead);
        rightAddress = leftAddress + size;
    }

    MemoryArena::~MemoryArena() {
        std::free(memHead);
    }

    // TODO(wowvain-dev): This is only allocating from top
    void* MemoryArena::alloc(const u_size size, u_size& outSize) {
        u_ptr lastAddress;
        u_size lastSize;

        if (addressIndexMap.empty()) {
            lastAddress = leftAddress;
            lastSize = 0;
        } else {
            auto lastPair = --addressIndexMap.end();
            lastAddress = lastPair->first;
            lastSize = entryArr[lastPair->second].size;
        }

        u_ptr rawAddress = lastAddress + lastSize;
        u8 alignment = MemUtil::ALIGNMENT;
        u_ptr misAlignment = rawAddress & (alignment - 1);

        u_ptr_diff adjustment = (alignment - misAlignment) & (alignment - 1);
        u_ptr alignedAddress = rawAddress + adjustment;

        if (alignedAddress + size > rightAddress) {
            throw std::runtime_error(
                "MemoryArena::alloc -> Not enough memory in the arena"
            );
        }

        outSize = size + adjustment;

        return reinterpret_cast<void*>(alignedAddress);
    }

    void MemoryArena::defragment() {
        /// TODO(wowvain-dev): PROFILE 
        if (addressIndexMap.empty()) return;

        for (int i = 0; i < 6; i++) {
            ++curIndex;
            if (curIndex >= addressIndexMap.size()) {
                curIndex = 0;
            }

            moveLeft(curIndex);
        }
    }

    /// TODO(wowvain-dev) move this to math stuff
    u_ptr nextMultiplyOfBase(const u_ptr number, const u32 base) {
        VASSERT(number != 0)
        VASSERT(base >= 2 && (base & (base - 1)) == 0)

        u_ptr diff = number & (base - 1);
        u_ptr_diff adjustment = (base - diff) & (base - 1);
        
        return number + adjustment;
    }

    void MemoryArena::moveLeft(u32 index) {
        VASSERT(index <= addressIndexMap.size() - 1);

        /// TODO(wowvain-dev) to swap with custom container
        std::vector<int> arr;

        arr.reserve(addressIndexMap.size());

        for (const auto& pair : addressIndexMap) {
            arr.push_back(pair.second);
        }

        const auto& entry = entryArr[arr[index]];

        u_ptr lastAvailableAddress;

        if (index == 0) {
            lastAvailableAddress = leftAddress;
        } else {
            const auto& lastEntry = entryArr[arr[index - 1]];
            lastAvailableAddress = lastEntry.getAddress() + lastEntry.size; 
        }

        lastAvailableAddress = nextMultiplyOfBase(lastAvailableAddress, MemUtil::ALIGNMENT);

        if (lastAvailableAddress < entry.getAddress()) {
            void* newAdd = reinterpret_cast<void*>(lastAvailableAddress);

            addressIndexMap.erase(
                addressIndexMap.find(reinterpret_cast<u_ptr>(entry.ptr)));
            addressIndexMap.emplace(reinterpret_cast<u_ptr>(newAdd), arr[index]);

            std::memmove(newAdd, entry.ptr, entry.size);

            entry.ptr = newAdd;
        }
    }


    void MemoryArena::print() const {
        VDEBUG("[MEMORY], [address, index, size]")
        int count(0);

        for (const auto& pair: addressIndexMap) {
            VDEBUG("[MEMORY], {} [{}, {}, {}]",
                count++,
                pair.first,
                pair.second,
                entryArr[pair.second].size
            )
        }
    }

    u_ptr MemoryArena::getUsedSize() const {
        u_ptr lastAddress;
        u_size lastSize;

        if (addressIndexMap.empty()) {
            lastAddress = leftAddress;
            lastSize = 0;
        } else {
            auto lastPair = --addressIndexMap.end();
            lastAddress = lastPair -> first;
            lastSize = entryArr[lastPair->second].size;
        }

        auto lastPair = --addressIndexMap.end();

        return (lastAddress + lastSize) - leftAddress;
    }


}