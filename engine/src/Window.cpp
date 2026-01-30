#include "Core.h"
#include "Platform/Window.h"
#include "Platform/Config.h"

#include <iostream>

// ------------------------------------------------------------
// Constructor / Destructor
// ------------------------------------------------------------

Window::Window(const Config& config)
{
    // 1. Init GLFW
    if (!glfwInit())
    {
        std::cerr << "[Window] Failed to initialise GLFW\n";
        return;
    }

    // (Optional, but good practice)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    // 2. Create window
    m_Window = glfwCreateWindow(
        config.width,
        config.height,
        config.title.c_str(),
        nullptr,
        nullptr
    );

    if (!m_Window)
    {
        std::cerr << "[Window] Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    // 3. Make context current
    glfwMakeContextCurrent(m_Window);

    // 4. Load OpenGL via GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "[Window] Failed to initialise GLAD\n";
        return;
    }

    // 5. Store pointer for callbacks
    glfwSetWindowUserPointer(m_Window, this);

    // 6. Register framebuffer resize callback
    glfwSetFramebufferSizeCallback(
        m_Window,
        FramebufferResizeCallback
    );

    // 7. Initial viewport
    glViewport(0, 0, config.width, config.height);

    // 8. Sensible defaults
    glfwSwapInterval(1); // vsync on
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

// ------------------------------------------------------------
// Public API
// ------------------------------------------------------------

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

// ------------------------------------------------------------
// GLFW callbacks
// ------------------------------------------------------------

void Window::FramebufferResizeCallback(
    GLFWwindow* window,
    const int width,
    const int height
)
{
    // Retrieve our Window instance
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));

    // OpenGL must always be told about the new drawable size
    glViewport(0, 0, width, height);

    // Notify the engine (if anyone is listening)
    if (win->m_EventCallback)
    {
        WindowResizeEvent event(width, height);
        win->m_EventCallback(event);
    }
}
