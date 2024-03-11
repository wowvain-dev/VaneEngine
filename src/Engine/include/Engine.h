#pragma once
#include "EngineConfig.h"

namespace Vane {

class Engine {
public:
    EngineConfig config;
private:

public:
    Engine();
    ~Engine();

    void initialize();

};

}
