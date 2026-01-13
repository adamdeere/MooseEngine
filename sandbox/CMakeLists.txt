cmake_minimum_required(VERSION 3.20)
project(MooseSandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MooseSandbox
        src/main.cpp
)

# Tell CMake to find the packages
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# Link libraries
target_link_libraries(MooseSandbox
        PRIVATE MooseEngine
        PRIVATE glfw
        PRIVATE glad::glad

)
