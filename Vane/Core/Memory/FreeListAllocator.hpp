#pragma once

#include <unordered_map>
#include <algorithm>
#include <vector>
#include "../Asserts.hpp"
#include "../Defines.hpp"
#include "MemUtil.hpp"
#include "../../Utils/sid.hpp"

namespace Vane::Memory {
class FreeListAllocator {
public:
    FreeListAllocator() = delete;
    explicit FreeListAllocator(u_size size);
    ~FreeListAllocator();

    void* alloc(u_size size, u8 alignment);
    void free(void* memPtr);
    void* realloc(void* memPtr, u_size newSize, u8 alignment);

    template <typename T, typename... Args>
    T* New(Args... args);
    template <typename T>
    void Delete(T* t);
    template <typename T>
    T* NewArr(u_size length, u8 alignment);
    template <typename T>
    void DeleteArr(u_size length, T* ptrToDelete);

private:
    struct Node {
        u_size size;
        Node* next;
        explicit Node(const u_size size) : size(size), next(nullptr) {}
    };

    struct AllocHeader {
        u_size size;
        u64 adjustment;

        AllocHeader(const u_size size, const u64 adjustment)
            : size(size), adjustment(adjustment) {}
    };

    void Expand();
    void RemoveNode(Node* last, Node* nodeToRemove);
    void InsertNode(Node* newNode);

    static void InsertNodeAt(Node* pos, Node* newNode);
    static void TryMergeWithNext(Node* node);

    Node* head = nullptr;
    void* memHead = nullptr;
    std::vector<void*> additionalMemory;

    static constexpr u_size nodeSize = sizeof(Node);
    static constexpr u_size headerSize = sizeof(AllocHeader);

#if DEBUG
    u_size totalSize{0};
    u_size sizeUsed{0};
    u_size numOfNews{0};
    u_size numOfDeletes{0};
    u_size numOfArrNews{0};
    u_size numOfArrDeletes{0};
    u_size numOfAllocs{0};
    u_size numOfFrees{0};

    using Allocations = std::pair<std::string, u16>;

    std::unordered_map<StringId, Allocations> monitor;
    std::unordered_map<u64, std::string> vTableToNameMap;
    bool monitorPureAlloc = true;
    void Print() const;
#endif

    friend class MemoryManager;
};

template <typename T, typename... Args>
T* FreeListAllocator::New(Args... args) {
#if DEBUG
    numOfNews++;
    monitorPureAlloc = false;
    T* ret = new(alloc(sizeof(T), MemUtil::ALIGNMENT)) T(args...);
    monitorPureAlloc = true;
    std::string name = MemUtil::getNameForType<T>();

    if (std::is_base_of<class Component, T>::value) {
        u64 vPointer = *reinterpret_cast<u64*>(ret);
        vTableToNameMap.insert({vPointer, name});
    }

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

    return ret;

#else
    return new (Alloc(sizeof(T), MemUtil::ALIGNMENT)) T(args...);
#endif
}

template <typename T>
void FreeListAllocator::Delete(T* t) {
#if DEBUG
    numOfDeletes++;
    std::string name;

    if (std::is_base_of<class Component, T>::value) {
        u64 vPointer = *reinterpret_cast<u64*>(t);
        name = vTableToNameMap.find(vPointer)->second;
    }
    else {
        name = MemUtil::getNameForType<T>();
    }

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

    t->~T();

    monitorPureAlloc = false;
    this->free(static_cast<void*>(t));
    monitorPureAlloc = true;
#else
    t->~T();
    this->free(static_cast< void * >(t));
#endif
}

template <typename T>
T* FreeListAllocator::NewArr(u_size length, u8 alignment) {
    VASSERT(length != 0);
#if DEBUG
    monitorPureAlloc = false;
    void* alloc = this->alloc(sizeof(T) * length, alignment);
    monitorPureAlloc = true;

    numOfArrNews++;
    std::string name = MemUtil::getNameForType<T>();
    if (std::is_base_of<class Component, T>::value) {
        u64 vPointer = *reinterpret_cast<u64*>(alloc);
        vTableToNameMap.insert({vPointer, name});
    }

    name += "Array[";
    name += std::to_string(length);
    name += "]";

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
#else
    void *alloc = this->alloc(sizeof(T) * length, alignment);
#endif

    char* allocAddress = static_cast<char*>(alloc);
    for (u_size i = 0; i < length; ++i) new(allocAddress + i * sizeof(T)) T;

    return static_cast<T*>(alloc);
}

template <typename T>
void FreeListAllocator::DeleteArr(u_size length, T* ptrToDelete) {
#if DEBUG
    numOfArrDeletes++;
    std::string name;

    if (std::is_base_of<class Component, T>::value) {
        u64 vPointer = *reinterpret_cast<u64*>(ptrToDelete);
        name = vTableToNameMap.find(vPointer)->second;
    }
    else {
        name = MemUtil::getNameForType<T>();
    }

    name += "Array[";
    name += std::to_string(length);
    name += "]";

    StringId sid = SID(name.c_str());
    auto it = monitor.find(sid);

    if (it != monitor.end()) {
        Allocations allocations = it->second;
        allocations.second--;
        VASSERT(allocations.second >= 0);
        if (allocations.second == 0) {
            monitor.erase(it);
        }
        else {
            it->second = allocations;
        }
    }

    for (u_size i = 0; i < length; ++i) ptrToDelete[i].~T();
    monitorPureAlloc = false;
    this->free(static_cast<void*>(ptrToDelete));
    monitorPureAlloc = true;
#else
    for (u_size i = 0; i < length; ++i) ptrToDelete[i].~T();
    this->free(static_cast< void * >(ptrToDelete));
#endif
}
};
