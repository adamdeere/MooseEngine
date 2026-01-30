#include "Engine/Engine.h"
#include <iostream>

Engine::Engine(const Window::Config& windowConfig) {
    window = std::make_unique<Window>(windowConfig);
}

Engine::~Engine() = default;

void Engine::run() const {
    if (initFunc) initFunc();

    auto lastTime = static_cast<float>(glfwGetTime());

    while (!window->shouldClose()) {
        const auto currentTime = static_cast<float>(glfwGetTime());
        const float dt = currentTime - lastTime;
        lastTime = currentTime;

        if (updateFunc) updateFunc(dt);

        window->swapBuffers();
        window->pollEvents();
    }
}
