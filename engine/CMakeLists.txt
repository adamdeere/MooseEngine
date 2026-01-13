add_library(MooseEngine STATIC)

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
