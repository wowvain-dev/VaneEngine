#pragma once

#include <stdexcept>

#include <Vane/Core/Memory/MemoryArena.hpp>
#include <Vane/Core/Defines.hpp>
#include <Vane/Core/Asserts.hpp>

namespace Vane::Memory {
/// TODO(wowvain-dev): implement reference counting;
class HandleEntry {
private:
    /// @brief Default constructor that does nothing.
    HandleEntry() = default;

    /// @brief Default destructor that does nothing.
    ~HandleEntry() = default;

    /// @brief A helper function that returns the address of pointed object.
    /// @return Address in type `u_ptr`
    u_ptr getAddress() const;

    /// @brief Just a help function for setting individual fields of the handle entry.
    /// @param uniqueID
    /// @param ptr
    /// @param isEmpty
    /// @param size
    void set(u32 uniqueID, void* ptr, bool isEmpty, u_size size);

    /// @brief Always compare this with the uniqueID of `ObjectHandle` used to manipulate
    /// this entry
    u32 uniqueID{};

    /// @brief Size of the object pointed to by this entry
    u_size size{};

    /// @brief Pointer to the actual object's address. Marked as mutable because its moved
    /// in the defragmentation process.
    mutable void* ptr{};


    bool isEmpty{true};

    template <typename T>
    friend class ObjectHandle;
    friend class MemoryArena;
};

template <typename T>
class ObjectHandle {
public:
    /// @brief Default constructor that does nothing. Exists to support having an array of ObjectHandles.
    ObjectHandle() = default;

    /// @brief Default destructor that does nothing (cause there is nothing to do).
    ~ObjectHandle() = default;

    /// @brief The actual constructor that the `MemoryArena` uses to create new
    /// `ObjectHandles`
    /// @param mem Pointer to the memory
    /// @param uniqueID uniqueID for this handle
    /// @param size Size of the object in bytes
    template <typename... args>
    ObjectHandle(void* mem, u32 uniqueID, u_size size, args...);

    /// @brief Returns a pointer to the actual object
    /// @return A pointer to the actual object
    T* operator->() const;

    /// @brief Returned the dereferanced object
    /// @return A reference to the object
    T& operator*();

    explicit operator bool() const;

private:
    /// @brief Helper function for finding the pointer to the actual object
    /// @return
    T* getObjectPtr() const;

    /// @brief Erase the object. This frees the memory, frees the coresponding handle entry,
    /// and calls destructor on the object.
    void eraseObject() const;

    /// @brief A helper function used to get the memory address of the object pointed to by this handle
    /// @return Memory address of the object pointed to by this handle
    u_ptr getObjAddress() const;

    u32 uniqueID{u32_MAX};
    u32 index{u32_MAX};

    friend class MemoryArena;
};

template <typename T>
T* ObjectHandle<T>::operator->() const {
    return getObjectPtr();
}

template <typename T>
T& ObjectHandle<T>::operator*() {
    return *getObjectPtr();
}

template <typename T>
ObjectHandle<T>::operator bool() const {
    if (index > MemoryArena::maxHandleCount) {
        return false;
    }

    HandleEntry& entry = MemoryArena::entryArr[index];

    return !entry.isEmpty && uniqueID == entry.uniqueID;
}

template <typename T>
template <typename... args>
ObjectHandle<T>::ObjectHandle(void* _mem, u32 _uniqueID, u_size _size, args... argList)
    : uniqueID(_uniqueID) {
    HandleEntry* entry = nullptr;

    for (u32 i = 0; i < MemoryArena::maxHandleCount; ++i) {
        if (MemoryArena::entryArr[i].isEmpty) {
            index = i;
            entry = &MemoryArena::entryArr[index];
            break;
        }
    }

    if (entry == nullptr) {
        throw std::out_of_range{
            "ObjectHandle::ObjectHandle -> No empty slot in handle table."
        };
    }

    T* t = new(_mem) T(argList...);
    entry->set(uniqueID, static_cast<void*>(t), false, _size);
}

template <typename T>
T* ObjectHandle<T>::getObjectPtr() const {
    HandleEntry& entry = MemoryArena::entryArr[index];

    if (entry.isEmpty) {
        throw std::exception{
            "ObjectHandle::getObjectPtr -> Object already deleted"
        };
    }

    if (uniqueID != entry.uniqueID) {
        throw std::exception{
            "ObjectHandle::getObjectPtr -> Object you are trying to access was "
            "replaced by a new object"
        };
    }

    return static_cast<T*>(entry.ptr);
}

template <typename T>
void ObjectHandle<T>::eraseObject() const {
    HandleEntry& entry = MemoryArena::entryArr[index];

    if (entry.isEmpty) {
        throw std::exception{
            "ObjectHandle::eraseObject -> ObjectHandle::deleteObject -> Double "
            "deleting handle!"
        };
    }

    if (uniqueID != entry.uniqueID) {
        throw std::exception{
            "ObjectHandle::eraseObject -> ObjectHandle::deleteObject -> You are "
            "trying to delete an object you don't own!"
        };
    }

    static_cast<T*>(entry.ptr)->~T();
    entry.isEmpty = true;
}

template <typename T>
u_ptr ObjectHandle<T>::getObjAddress() const {
    return reinterpret_cast<u_ptr>(getObjectPtr());
}
}
