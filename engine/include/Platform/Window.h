#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window {
public:
    struct Config {
        int width = 800;
        int height = 600;
        std::string title = "MooseEngine Window";
    };

    Window(const Config& config);
    ~Window();

    void swapBuffers();
    void pollEvents();
    bool shouldClose() const;

    GLFWwindow* getNativeWindow() const { return window; }

private:
    GLFWwindow* window;
};
