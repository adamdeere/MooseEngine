#pragma once

struct GLFWwindow;

class Window
{
public:
    bool Create(int width, int height, const char* title);
    void Destroy();

    void PollEvents();
    void SwapBuffers();

    bool ShouldClose() const;

    GLFWwindow* GetHandle() const { return m_Window; }

private:
    GLFWwindow* m_Window = nullptr;
};
