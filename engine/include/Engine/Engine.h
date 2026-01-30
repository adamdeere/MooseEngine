#pragma once
#include "Platform/Window.h"
#include <functional>
#include <memory>

class Engine {
public:
    using InitFunc = std::function<void()>;
    using UpdateFunc = std::function<void(float dt)>;

    Engine(const Window::Config& windowConfig);
    ~Engine();

    void setInitFunction(InitFunc func) { initFunc = func; }
    void setUpdateFunction(UpdateFunc func) { updateFunc = func; }

    void run() const;

private:
    InitFunc initFunc;
    UpdateFunc updateFunc;
    std::unique_ptr<Window> window;
};
