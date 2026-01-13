#include "Engine/Engine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr double FixedDelta = 1.0 / 60.0;

bool Engine::Initialise()
{
    return m_Window.Create(1280, 720, "Moose Engine");
}

void Engine::Run()
{
    double lastTime = glfwGetTime();
    double accumulator = 0.0;

    while (!m_Window.ShouldClose())
    {
        double currentTime = glfwGetTime();
        double frameTime = currentTime - lastTime;
        lastTime = currentTime;

        accumulator += frameTime;

        m_Window.PollEvents();

        while (accumulator >= FixedDelta)
        {
            FixedUpdate(FixedDelta);
            accumulator -= FixedDelta;
        }

        Update(frameTime);
        RenderPrep();
        Render();

        m_Window.SwapBuffers();
    }
}

void Engine::Shutdown()
{
    m_Window.Destroy();
}

void Engine::FixedUpdate(double /*dt*/)
{
    // physics / ECS fixed systems later
}

void Engine::Update(double /*dt*/)
{
    // camera, input, animations
}

void Engine::RenderPrep()
{
    // later: command buffers, visibility, etc.
}

void Engine::Render()
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
