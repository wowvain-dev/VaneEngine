#include "FreeListAllocator.hpp"
#include "MemUtil.hpp"
#include "../Logger.hpp"

namespace Vane::Memory {
FreeListAllocator::FreeListAllocator(const u_size size) {
    memHead = std::malloc(size);
    head = new(memHead) Node(size);
#if DEBUG
    totalSize += size;
#endif
}

FreeListAllocator::~FreeListAllocator() {
    if (memHead == nullptr) {
        return;
    }

#if DEBUG
    if (sizeUsed > 0) {
        VWARN(
            "You did {} news and {} deletes; {} newArrs and {} "
            "deleteArrs {} allocs and {} frees.",
            numOfNews, numOfDeletes, numOfArrNews,
            numOfArrDeletes, numOfAllocs, numOfFrees
        );

        VWARN("Memory leak of {} detected on freelist.", sizeUsed);

        VWARN("\u2193\u2193\u2193\u2193\u2193\u2193\u2193\u2193\u2193\u2193 "
            "Dumping Memory Leaks Below "
            "\u2193\u2193\u2193\u2193\u2193\u2193\u2193\u2193\u2193\u2193");

        VWARN("Name \t\t\t Count");

        for (auto& pair : monitor) {
            Allocations allocations = pair.second;
            VWARN("{} \t {}", allocations.first.c_str(), allocations.second);
        }

        VWARN("\u2191\u2191\u2191\u2191\u2191\u2191\u2191\u2191\u2191\u2191 "
            "See Memory Leak Dump Above "
            "\u2191\u2191\u2191\u2191\u2191\u2191\u2191\u2191\u2191\u2191");
    }
    else {
        VINFO("No memory leak! Gj mate");
    }
#endif

    std::free(memHead);

    for (void* memory : additionalMemory) {
        std::free(memory);
    }
}

void* FreeListAllocator::alloc(const u_size size, const u8 alignment) {
    if (head == nullptr) {
        Expand();
        return alloc(size, alignment);
    }

    MemUtil::CheckAlignment(alignment);

    u_size need = headerSize + alignment + size;

    Node* last = nullptr;
    Node* cur = head;
    Node* node = nullptr;

    while (cur != nullptr) {
        if (cur->size >= need) {
            node = cur;
            break;
        }

        last = cur;
        cur = cur->next;
    }

    if (node == nullptr) {
        Expand();
        return alloc(size, alignment);
    }

    u_ptr rawPtr = reinterpret_cast<u_ptr>(node);
    rawPtr += headerSize;
    u_ptr misAlignment = rawPtr & (alignment - 1);
    u64 adjustment = alignment - misAlignment;
    u_ptr alignedAddress = rawPtr + adjustment;
    u_ptr headerAddress = alignedAddress - headerSize;

    u_size occupiedSize = headerSize + adjustment + size;
    u_size allocSize;

    if (node->size >= occupiedSize + nodeSize) {
        Node* newNode = new(reinterpret_cast<void*>(alignedAddress + size))
                Node(node->size - occupiedSize);

        InsertNodeAt(node, newNode);
        allocSize = occupiedSize;
    }
    else {
        allocSize = node->size;
    }

    RemoveNode(last, node);

    new(reinterpret_cast<void*>(headerAddress))
            AllocHeader(allocSize, adjustment);

#if DEBUG
    sizeUsed += allocSize;
    if (monitorPureAlloc) {
        numOfAllocs++;
        auto name = std::format("AllocSize[{}]", allocSize);
        StringId sid = SID(name.c_str());
        auto it = monitor.find(sid);

        if (it != monitor.end()) {
            Allocations allocations = it->second;
            allocations.second++;
            it->second = allocations;
        }
        else {
            monitor.insert({sid, {name, 1}});
        }
    }
#endif

    void* ret = reinterpret_cast<void*>(alignedAddress);
    memset(ret, 0, size);
    return ret;
}

void FreeListAllocator::free(void* memPtr) {
    u_ptr allocHeaderAdd = reinterpret_cast<u_ptr>(memPtr) - headerSize;
    auto* allocHeader = reinterpret_cast<AllocHeader*>(allocHeaderAdd);

#if DEBUG
    sizeUsed -= allocHeader->size;
    if (monitorPureAlloc) {
        numOfFrees++;
        auto name = std::format("AllocSize[{}]", allocHeader->size);
        StringId sid = SID(name.c_str());

        auto it = monitor.find(sid);
        VASSERT(it != monitor.end());
        Allocations allocations = it->second;
        allocations.second--;
        if (allocations.second == 0) {
            monitor.erase(it);
        }
        else {
            it->second = allocations;
        }
    }
#endif

    u_ptr nodeAddress = allocHeaderAdd - allocHeader->adjustment;
    auto* newNode =
            new(reinterpret_cast<void*>(nodeAddress)) Node(allocHeader->size);

    memset(newNode + 1, 0x0, newNode->size - nodeSize);

    InsertNode(newNode);
}

#undef min

void* FreeListAllocator::realloc(void* memPtr, u_size newSize, u8 alignment) {
    u_ptr allocHeaderAdd = reinterpret_cast<u_ptr>(memPtr) - headerSize;
    auto* allocHeader = reinterpret_cast<AllocHeader*>(allocHeaderAdd);

    void* dest = this->alloc(newSize, alignment);

    memcpy(dest, memPtr, std::min(allocHeader->size, newSize));
    this->free(memPtr);
    return dest;
}

// TODO(wowvain-dev): impl from FreeListAllocator::Expand() onward
};
