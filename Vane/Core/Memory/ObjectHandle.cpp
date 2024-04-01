#include "ObjectHandle.hpp"

using namespace Vane::Memory;

u_ptr HandleEntry::getAddress() const { return reinterpret_cast<u_ptr>(ptr); }

void HandleEntry::set(u32 _uniqueID, void* _ptr, bool _isEmpty, u_size _size) {
    uniqueID = _uniqueID;
    ptr = _ptr;
    isEmpty = _isEmpty;
    size = _size;
}

