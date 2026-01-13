cmake_minimum_required(VERSION 3.20)
project(MooseSandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MooseSandbox
        src/main.cpp
)



# Link libraries
target_link_libraries(MooseSandbox
        PRIVATE MooseEngine

)
