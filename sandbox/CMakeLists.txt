add_executable(MooseSandbox
    src/main.cpp
)

target_link_libraries(MooseSandbox
    PRIVATE MooseEngine
)
