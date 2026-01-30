add_library(MooseEngine STATIC
            src/Window.cpp
            include/Platform/Window.h
            src/Shader.cpp
            include/Render/Shader.h
            include/Render/OpenGLShader.h
            src/OpenGLShader.cpp
            src/Camera.cpp
            include/Engine/Camera.h
        include/Platform/Events.h
        src/WindowEvents.cpp
        include/Platform/WindowEvents.h
        include/Platform/Config.h)

# Tell CMake to find the packages
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_compile_features(MooseEngine PUBLIC cxx_std_20)

target_link_libraries(MooseEngine
        PUBLIC
        glad::glad
        glfw
        glm::glm
)

target_sources(MooseEngine
    PRIVATE
        src/Engine.cpp
)

# Add precompiled header
target_precompile_headers(MooseEngine PRIVATE src/Core.h)

target_include_directories(MooseEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(MooseEngine
    PRIVATE
        MOOSE_ENGINE_BUILD
)
