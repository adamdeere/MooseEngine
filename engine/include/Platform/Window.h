#pragma once

#include <functional>
#include "WindowEvents.h"
struct Config;

class Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    explicit Window(const Config& config);
    ~Window();

    static void PollEvents();
    void SwapBuffers() const;

    // NEW
    bool ShouldClose() const;

    void SetEventCallback(const EventCallbackFn& callback)
    {
        m_EventCallback = callback;
    }

private:
    static void FramebufferResizeCallback(
        GLFWwindow* window,
        int width,
        int height
    );

private:
    GLFWwindow* m_Window = nullptr;
    EventCallbackFn m_EventCallback;
};
