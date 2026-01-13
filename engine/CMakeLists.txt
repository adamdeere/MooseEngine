add_library(MooseEngine STATIC
        src/Window.cpp
        include/Engine/Window.h)

# Tell CMake to find the packages
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(MooseEngine
        PUBLIC
        glad::glad
        glfw
)

target_sources(MooseEngine
    PRIVATE
        src/Engine.cpp
)

target_include_directories(MooseEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(MooseEngine
    PRIVATE
        MOOSE_ENGINE_BUILD
)
