#pragma once

#include "Engine/Window.h"

class Engine
{
public:
    bool Initialise();
    void Run();
    void Shutdown();

private:
    void FixedUpdate(double dt);
    void Update(double dt);
    void RenderPrep();
    void Render();

private:
    Window m_Window;
};
