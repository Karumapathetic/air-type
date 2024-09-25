project(GraphicsLib)

add_library(
    Graphics STATIC
    tmp.cpp
)

target_include_directories(
    Graphics PUBLIC
    "include"
)
