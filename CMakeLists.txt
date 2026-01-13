cmake_minimum_required(VERSION 4.1)
project(MooseEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# MSVC quality-of-life
if (MSVC)
    add_compile_options(/W4 /permissive-)
endif()

add_subdirectory(engine)
add_subdirectory(sandbox)