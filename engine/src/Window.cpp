#include "Platform/Window.h"
#include <glad/glad.h>
#include <iostream>

Window::Window(const Config& config) {
    if (!glfwInit()) {
        std::cerr << "[Window] Failed to initialize GLFW\n";
        window = nullptr;
        return;
    }

    window = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "[Window] Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "[Window] Failed to initialize GLAD\n";
    }

    // ✅ Set initial viewport
    glViewport(0, 0, config.width, config.height);

    glEnable(GL_DEPTH_TEST); // basic 3D rendering
}

Window::~Window() {
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::swapBuffers() const {
    if (window) glfwSwapBuffers(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return window ? glfwWindowShouldClose(window) : true;
}
