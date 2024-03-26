#pragma once 

#include "Core/Application.hpp"

#include <functional>
#include <memory>   

namespace Vane {

class IGameCallbacks {
public: 
    virtual bool initialize(const ApplicationConfig& config) = 0;
    virtual bool update(const ApplicationConfig& config, float delta) = 0; 
    virtual bool render(const ApplicationConfig& config, float delta) = 0;
    virtual void onResize(const ApplicationConfig& config, u32 w, u32 h) = 0;
    virtual ~IGameCallbacks() = default;
};



class Game {
public:
    ApplicationConfig appConfig;
public:
    void setConfig(const ApplicationConfig& data) {
        appConfig = data;
    }

    void setCallbacks(std::shared_ptr<IGameCallbacks> callbacks) {
        m_Callbacks = callbacks;
    }

    std::shared_ptr<IGameCallbacks> getCallbacks() const {
        return m_Callbacks;
    }

private:
    std::shared_ptr<IGameCallbacks> m_Callbacks;
};

};