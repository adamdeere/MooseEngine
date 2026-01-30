// EnginePCH.h
#pragma once

// Platform
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

// GLAD must be first for OpenGL function prototypes
#include <glad/glad.h>

// GLFW (for window/context/input)
#include <GLFW/glfw3.h>

// GLM for math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// STL helpers
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>
