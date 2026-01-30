#include "Engine/Engine.h"
#include "Platform/Config.h"

Engine::Engine(const Config& windowConfig) {
    window = std::make_unique<Window>(windowConfig);
    window->SetEventCallback([this](Event& e){ OnEvent(e); });
}

Engine::~Engine() = default;

void Engine::OnEvent(Event& e)
{
    if (e.GetType() == EventType::WindowResize)
    {
        const auto& resize = static_cast<WindowResizeEvent&>(e);

        // Engine camera reacts automatically
        camera.SetAspectRatio(
            static_cast<float>(resize.width) /
            static_cast<float>(resize.height)
        );

        // OpenGL viewport
        glViewport(0, 0, resize.width, resize.height);
    }
}


void Engine::Run() const {

    if (initFunc) initFunc();

    double lastTime = glfwGetTime();
    constexpr double fixedTimeStep = 1.0 / 60.0;
    double accumulator = 0.0;

    while (!window->ShouldClose()) {
        window->PollEvents();

        const double currentTime = glfwGetTime();
        const double frameTime = currentTime - lastTime;
        lastTime = currentTime;

        accumulator += frameTime;

        // FixedUpdate (physics)
        while (accumulator >= fixedTimeStep) {
            if (fixedUpdateFunc) fixedUpdateFunc(fixedTimeStep);
            accumulator -= fixedTimeStep;
        }

        // Variable Update (input, animations, camera)
        if (updateFunc) updateFunc(static_cast<float>(frameTime));

        // Render
        if (renderFunc) renderFunc();
        window->SwapBuffers();
    }
}

