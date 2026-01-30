#pragma once
#include "Platform/Window.h"
#include <functional>
#include <memory>

#include "Camera.h"

struct Config;

class Engine {
public:
    using InitFunction = std::function<void()>;
    using RenderFunction = std::function<void()>;
    using UpdateFunction = std::function<void(float dt)>;
    using FixedUpdateFunction = std::function<void(float dt)>;

    explicit Engine(const Config& windowConfig);
    ~Engine();

    void SetInitFunction(const InitFunction &func) { initFunc = func; }
    void SetRenderFunction(const RenderFunction &func) { renderFunc = func; }
    void SetUpdateFunction(const UpdateFunction &func) { updateFunc = func; }
    void SetFixedFunction(const FixedUpdateFunction &func) { fixedUpdateFunc = func; }

    void OnEvent(Event& e);


    void Run() const;

private:
    InitFunction initFunc;
    RenderFunction renderFunc;
    UpdateFunction updateFunc;
    FixedUpdateFunction fixedUpdateFunc;
    std::unique_ptr<Window> window;

    Camera camera; // ✅ Engine owns a default camera
};
