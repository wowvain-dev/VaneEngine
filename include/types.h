#pragma once

#include <string>

namespace Vane {
namespace Albita {
    enum BACKEND {
        DX11 = 0,
        DX12 = 1,
        VULKAN = 2,
        OPENGL = 3
    };

    inline std::string STRING_FROM_BACKEND(BACKEND backend) {
        std::string res;
        switch (backend) {
        case DX11:
            res.append("DX11");
            break;
        case DX12:
            res.append("DX12");
            break;
        case VULKAN:
            res.append("VULKAN");
            break;
        case OPENGL:
            res.append("OpenGL");
            break;
        }
        return res;
    }
}
}
