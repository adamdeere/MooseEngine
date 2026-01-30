#pragma once

#include <string>

struct Config
{
    int width  = 800;                       // Initial window width
    int height = 600;                       // Initial window height
    std::string title = "MooseEngine Window"; // Window title

    // Optional: can add more later (vsync, fullscreen, API backend)
};
