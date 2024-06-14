#pragma once
#include <Vane/Core/Defines.hpp>

class MemUtils {
public:
    static const u_size CalculatePadding(const u_size baseAddress, const u_size alignment) {
        const u_size multiplier = (baseAddress / alignment) + 1;
        const u_size alignedAddress = multiplier * alignment;
        const u_size padding = alignedAddress - baseAddress;
        return padding;
    }

    static const u_size CalculatePaddingWithHeader(const u_size baseAddress, const u_size alignment, const u_size headerSize) {
        u_size padding = CalculatePadding(baseAddress, alignment);
        u_size neededSpace = headerSize;

        if (padding < neededSpace) {
            neededSpace -= padding;

            // How many alignments I need to fit the header
            if (neededSpace % alignment > 0) {
                padding += alignment * (1 + (neededSpace / alignment));
            } else {
                padding += alignment * (neededSpace / alignment);
            }
        }
        return padding;
    }
};
